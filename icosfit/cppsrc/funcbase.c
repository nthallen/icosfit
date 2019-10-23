#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "ICOSfit.h"
#include "global.h"

/**
  func_base_svdx is a func_evaluator that uses a canonical
  baseline shape derived from zero air for the baseline.
  The baseline data is written in my ICOS-standard binary
  file format, which uses two 32-bit unsigned ints at
  the start to specify rows and columns, and then records
  the remaining data as floats. For the baseline, the first
  element of each column is the parameter initialization.
 */
func_base_svdx::func_base_svdx( const char *filename ) :
    func_base( "func_base_svdx" ) {
  uses_nu_F0 = 0;
  FILE *fp = fopen( filename, "r" );
  if ( fp == 0 )
    nl_error( 3, "Unable to open baseline file %s", filename );
  icos_hdr_t header[2];
  if ( fread_swap32( &header, sizeof(icos_hdr_t), 2, fp ) != 2 )
    nl_error( 3, "%s: Error reading header: %s", filename,
      strerror(errno) );
  if ( header[0] <= 1 || header[1] <= 0 )
    nl_error( 3, "%s: Invalid header: %ld, %ld", filename,
              header[0], header[1] );
  // n_params = header[1];
  // params = new parameter[n_params];
  n_pts = header[0]-1;
  baseline = new ICOS_Float *[header[1]+1];
  if (baseline == 0) nl_error(3, "Out of memory in func_base" );
  unsigned int i;
  for ( i = 0; i < header[1]; i++ ) {
    /* The first element of each column is the initial parameter */
    baseline[i] = new ICOS_Float[header[0]];
    if ( baseline[i] == 0 )
      nl_error(3, "Out of memory in func_base");
    if ( fread_swap32( baseline[i], sizeof(float), header[0], fp )
          != header[0] ) {
      nl_error( 3, "%s: Error reading baseline: %s", filename,
        strerror(errno) );
    } else {
#if RESIZE_INPUT
      float *raw = (float*)baseline[i];
      ICOS_Float *tgt = baseline[i];
      for (int ix = header[0]-1; ix >= 0; --ix) {
        tgt[ix] = (ICOS_Float)raw[ix];
      }
#endif
      append_func(new func_parameter("basesvdx",
        (ICOS_Float)baseline[i][0], true, i));
      // params[i].init = baseline[i][0];
    }
  }
  fclose(fp);
}

void func_base_svdx::evaluate(ICOS_Float x, ICOS_Float *pv) {
  unsigned int i;
  int ix = (int)x;
  if (ix < 1 || ix > n_pts)
    nl_error( 3,
      "x out of range in func_base_svdx::evaluate: %d", ix );
  value = 0.;
  for (i = 0; i < args.size(); ++i) {
    ICOS_Float ai = get_arg(i);
    ICOS_Float bix = baseline[i][ix];
    value += ai * bix;
    args[i].dyda = bix;
  }
}

func_base_ptbnu::func_base_ptbnu(const char *filename, func_evaluator *nu_F0) :
    func_base( "func_base_ptbnu" ) {
  // uses_nu_F0 = 0;
  // The file format is specified in funceval.h
  FILE *fp = fopen( filename, "r" );
  icos_hdr_t header[2];
  if ( fread_swap32( &header, sizeof(icos_hdr_t), 2, fp ) != 2 )
    nl_error( 3, "%s: Error reading header: %s", filename,
      strerror(errno) );
  if (header[0]!=0 || header[1]!=1)
    nl_error(3,"Input file is not in ptbnu format: '%s'", filename );
  if ( sizeof(cfg) != 32 )
    nl_error(4, "ASSERT FAILURE: func_base_ptbnu sizeof(cfg) != 32 (%d)", sizeof(cfg) );
  if (fread(&cfg, sizeof(cfg), 1, fp) != 1)
    nl_error(3, "%s: Error reading cfg header: %s", filename,
      strerror(errno));
  #ifdef USE_BIG_ENDIAN
    cfg.poly_scale = bswap_64(cfg.poly_scale);
    cfg.nu0 = bswap_64(cfg.nu0);
    cfg.dnu = bswap_64(cfg.dnu);
    cfg.n_vectors = bswap_16(cfg.n_vectors);
    cfg.n_pts = bswap_16(cfg.n_pts);
    cfg.poly_coeffs = bswap_16(cfg.poly_coeffs);
    cfg.poly_of_nu = bswap_16(cfg.poly_of_nu);
  #endif
  if ( cfg.n_vectors > 0 && cfg.n_pts < 2 )
    nl_error(3, "%s: n_pts too small: %d", filename, cfg.n_pts );
  uses_nu_F0 = (cfg.n_vectors || cfg.poly_of_nu) ? 1 : 0;
  if (uses_nu_F0) {
    append_func(nu_F0);
  }
  // Read in initial parameter values
  int i;
  for ( i = 0; i < cfg.n_vectors; i++) {
    float pval;
    if ( fread_swap32( &pval, sizeof(float), 1, fp ) != 1 )
      nl_error( 3, "%s: Error reading vector param init: %s", filename,
        strerror(errno));
    append_func(new func_parameter("basevec", (ICOS_Float)pval, true, i));
  }
  for ( i = 0; i < cfg.poly_coeffs; i++ ) {
    float pval;
    if ( fread_swap32( &pval, sizeof(float), 1, fp )
            != 1 )
      nl_error( 3, "%s: Error reading polynomial param init: %s", filename,
        strerror(errno));
    append_func(new func_parameter("basepoly", (ICOS_Float)pval, true, i));
  }
  if ( cfg.n_vectors ) {
    vectors = new ICOS_Float *[cfg.n_vectors];
    if (vectors == 0) nl_error(3, "Out of memory in func_base_ptbnu" );
    for ( i = 0; i < cfg.n_vectors; i++ ) {
      vectors[i] = new ICOS_Float[cfg.n_pts];
      if ( fread_swap32(vectors[i], sizeof(float), cfg.n_pts, fp) != cfg.n_pts ) {
        nl_error( 3, "%s: Error reading ptb vector: %s", filename,
          strerror(errno));
#if RESIZE_INPUT
      } else {
        float *raw = (float*)vectors[i];
        ICOS_Float *tgt = vectors[i];
        for (int ix = cfg.n_pts-1; ix >= 0; --ix) {
          tgt[ix] = (ICOS_Float)raw[ix];
        }
#endif
      }
    }
  }
  fclose(fp);
  if ( cfg.n_vectors ) {
    dvdnu = new ICOS_Float *[cfg.n_vectors];
    if ( dvdnu == 0) nl_error(3, "Out of memory allocating dvdnu" );
    for ( i = 0; i < cfg.n_vectors; i++ ) {
      ICOS_Float *vi, *di;
      di = dvdnu[i] = new ICOS_Float[cfg.n_pts];
      vi = vectors[i];
      for (int j = 0; j < cfg.n_pts-1; j++ )
        di[j] = (vi[j+1]-vi[j])/cfg.dnu;
      di[cfg.n_pts-1] = di[cfg.n_pts-2];
    }
    if ( GlobalData.Verbosity & 4 ) {
      fprintf( stderr, "Baseline Nu0 = %.4lf  dnu = %.5lf\n", cfg.nu0, cfg.dnu );
      fprintf( stderr, "Baseline Vectors = [\n" );
      for ( int j = 0; j < cfg.n_pts; j++ ) {
        for ( i = 0; i < cfg.n_vectors; i++ ) {
          fprintf(stderr, "  %.5" FMT_E, vectors[i][j] );
        }
        fprintf( stderr, "\n" );
      }
      fprintf( stderr, "];\n" );
      fprintf( stderr, "Baseline dVdnu = [\n" );
      for ( int j = 0; j < cfg.n_pts; j++ ) {
        for ( i = 0; i < cfg.n_vectors; i++ ) {
          fprintf(stderr, "  %.5" FMT_E, dvdnu[i][j] );
        }
        fprintf( stderr, "\n" );
      }
      fprintf( stderr, "];\n" );
    }
  }
  // Now setup polynomial stuff
  // ### Why is this in init().
  // ### Could it not be in the constructor?
  cfg.nu0 -= func_line::nu0;
  if ( cfg.poly_coeffs > 0 && ! cfg.poly_of_nu ) {
    int nx = GlobalData.SignalRegion[1]+1;
    polyvecs = new ICOS_Float *[cfg.poly_coeffs-1]; // don't bother with constant
    if ( polyvecs == 0 ) nl_error(3, "Out of memory in func_base_ptbnu::init" );
    for ( int i = 0; i < cfg.poly_coeffs-1; i++ ) {
      polyvecs[i] = new ICOS_Float[nx];
      if ( polyvecs[i] == 0 )
        nl_error( 3, "Out of memory in func_base_ptbnu::init" );
    }
    for ( int j = 0; j < nx; j++ ) {
      ICOS_Float x = (j+MLBASE)/cfg.poly_scale;
      ICOS_Float power = x;
      for ( int i = 0; i < cfg.poly_coeffs-1; i++ ) {
        polyvecs[i][j] = power;
        power *= x;
      }
    }
  }
}

void func_base_ptbnu::init( ICOS_Float *p) {
  func_evaluator::init(p);
  if (uses_nu_F0)
    fix_param(0);
}

void func_base_ptbnu::evaluate(ICOS_Float x, ICOS_Float *p) {
  int ix = int(x);
  ICOS_Float nu = 0.;

  value = 0;
  if ( uses_nu_F0 ) {
    ICOS_Float nu_F0 = get_arg(0);
    nu = ICOSfile::wndata->data[ix] + nu_F0;
    args[0].dyda = 0;
  }
  if ( cfg.n_vectors ) {
    ICOS_Float bins = (nu-cfg.nu0)/cfg.dnu;
    if ( bins < 0. || bins >= cfg.n_pts )
      nl_error( 3, "Input nu (%.2" FMT_F
        ") out of range in func_base_ptbnu::evaluate", nu );
    int nui = (int) floor(bins);
    ICOS_Float fbin = bins - nui; // fraction of a bin
    for ( int i = 0; i < cfg.n_vectors; i++ ) {
      ICOS_Float ai = get_arg(i+uses_nu_F0);
      ICOS_Float dvdnui = dvdnu[i][nui];
      ICOS_Float vnui = vectors[i][nui] + fbin * cfg.dnu * dvdnui;
      value += ai * vnui;
      args[0].dyda += ai * dvdnui;
      args[i+uses_nu_F0].dyda = vnui;
    }
  }
  // Now for the polynomials
  if ( cfg.poly_of_nu ) {
    ICOS_Float nupower = 1;
    ICOS_Float prevpower = 1;
    for ( int i = 0; i <= cfg.poly_coeffs; i++ ) {
      int pi = i + uses_nu_F0 + cfg.n_vectors;
      ICOS_Float ai = get_arg(pi);
      value += ai * nupower;
      args[pi].dyda = nupower;
      args[0].dyda += i*ai*prevpower;
      prevpower = nupower;
      nupower *= nu;
    }
  } else {
    value += get_arg(cfg.n_vectors+uses_nu_F0); // Constant
    args[cfg.n_vectors+uses_nu_F0].dyda = 1;
    for ( int i = 0; i < cfg.poly_coeffs-1; i++ ) {
      int pi = uses_nu_F0 + cfg.n_vectors + 1 + i;
      ICOS_Float xpower = polyvecs[i][ix];
      value += get_arg(pi) * xpower;
      args[pi].dyda = xpower;
    }
  }
}

func_base_input::func_base_input( func_base *base ) :
            func_base("func_base_input") {
  append_func(new func_parameter("k_input",1.0));
  append_func(base);
  // n_params = base->n_params + 1;
  // uses_nu_F0 = base->uses_nu_F0;
}

void func_base_input::init(ICOS_Float *a) {
  func_evaluator::init(a);
  assert(args.size() == 2);
  // This could be is_parameter()
  assert(args[0].arg->args.size() == 0 &&
         args[0].arg->params.size() == 1);
  for (unsigned int i = 1; i < params.size(); ++i) {
    assert(params[i].refs.size() == 1);
    assert(params[i].refs[0].arg_num == 1);
  }
}

void func_base_input::evaluate( ICOS_Float x, ICOS_Float *a ) {
  int ix = int(x);
  value = args[0].arg->value * ICOSfile::bdata->data[ix] +
    args[1].arg->value;
  args[0].dyda = ICOSfile::bdata->data[ix];
  args[1].dyda = 1;
}

func_base *pick_base_type(const char *filename, func_evaluator *nu_F0) {
  func_base *base;
  FILE *fp = fopen( filename, "r" );
  if ( fp == 0 )
    nl_error( 3, "Unable to open baseline file %s", filename );
  icos_hdr_t header[2];
  if ( fread_swap32( &header, sizeof(icos_hdr_t), 2, fp ) != 2 )
    nl_error( 3, "%s: Error reading header: %s", filename,
      strerror(errno) );
  fclose(fp);
  if (header[0]) {
    base = new func_base_svdx(filename);
  } else if (header[1] == 1) {
    base = new func_base_ptbnu(filename, nu_F0);
  } else {
    nl_error( 3, "Unrecognized baseline file format: %s", filename );
    return 0; // Can't happen
  }
  if ( GlobalData.BaselineInput )
    base = new func_base_input(base);
  return base;
}
