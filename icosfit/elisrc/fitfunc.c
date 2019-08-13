#include "ICOSfit.h"
#include <setjmp.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cfloat>
#include "global.h"
#include "clp.h"
#include "levmar.h"
#include "misc.h" // from levmar library
#include "vector.h"
#include "nl_assert.h"

jmp_buf Fit_buf;

fitdata::fitdata( PTfile *ptf, ICOSfile *IF,
    func_evaluator *f, func_evaluator *baseline, func_abs *abs )
    : func(f),
      base(baseline),
      absorb(abs),
      PTf(ptf),
      IFile(IF)
{
  int i;
  
  verbose = GlobalData.Verbosity;
  vfp = 0;
  vmlf = 0;
  if ( verbose & 8 ) {
    vmlf = mlf_init( 3, 60, 1, GlobalData.OutputDir, "dir", NULL );
  }
  BaseStart = GlobalData.BackgroundRegion[0];
  BaseEnd = GlobalData.BackgroundRegion[1];
  SignalStart = GlobalData.SignalRegion[0] + func->skew_samples();
  SignalEnd = GlobalData.SignalRegion[1];
  
  Start = End = 0;
  npts = 0;
  npts_vec = SignalEnd-SignalStart+1; // Max possible
  x = vector(npts_vec);
  y = 0;
  mp = func_parameter::n_parameters;
  p    = vector(mp);
  p_save = vector(mp);
  ub = vector(mp);
  lb = vector(mp);
  dscl = vector(mp);
  is_floating = (bool *)new_memory(mp*sizeof(bool));
  jacerr = (verbose & V_CHKJAC) ? vector(SignalEnd-SignalStart+1) : 0;
  difjac = (verbose & V_CHKDER) ? vector(mp*npts_vec) : 0;
  hxjac = (verbose & V_CHKDER) ? vector(npts_vec) : 0;
  hxxjac = (verbose & V_CHKDER) ? vector(npts_vec) : 0;
  if ( p == 0 || ub == 0 || lb == 0 || is_floating == 0)
    nl_error( 3, "Out of memory in fitdata::fitdata" );
  for ( i = 0; i < mp; i++ ) {
    ub[i] = DBL_MAX;
    lb[i] = -DBL_MAX;
    is_floating[i] = true;
    dscl[i] = 1.0;
  }
  adata.fit = this;
  adata.func = func;
  lm_work = (double *)new_memory(LM_BC_DER_WORKSZ(mp,SignalEnd-SignalStart+1)*sizeof(double));
  info = (double *)new_memory(LM_INFO_SZ*sizeof(double));
  func_evaluator::global_evaluation_order.set(f);
  func_evaluator::dump_evaluation_order.set_pre_order(f);
  f->init(p, lb, ub, is_floating, dscl);
  nl_assert((unsigned)mp == func->params.size());
}

#define RESTART_BUFSIZE 4096

/**
  Resets internal parameters to match a specific start condition
  based on a previous run.
 */
void fitdata::handle_restart( const char *ofname ) {
  // unsigned int prev_ScanNum = 0;
  if ( RestartAt != NoKey)
    GlobalData.RestartAt = GetClpValue(RestartAt, 0);;
  if ( GlobalData.RestartAt > 0 ) {
    char bakname[PATH_MAX];
    FILE *ifp = fopen( ofname, "r" );
    if ( ifp == 0 )
      nl_error( 3, "Unable to read output file %s for restart", ofname );

    for (;;) {
      if ( PTf->readline() ) {
        if (PTf->ScanNum == GlobalData.RestartAt) {
          PTf->backup();
          break;
        // } else {
          // prev_ScanNum = PTf->ScanNum;
        }
      } else {
        nl_error( 3, "Did not find ScanNum %d in PTE file", GlobalData.RestartAt );
      }
    }
    
    if ( GlobalData.PreserveOutput == 1 ) {
      snprintf( bakname, PATH_MAX-1, "%s.%d", ofname, GlobalData.RestartAt );
      bakname[PATH_MAX-1] = '\0';
      IFile->ofp = fopen( bakname, "w" );
      if ( IFile->ofp == 0 )
        nl_error( 3, "Unable to open output file %s", bakname );
    } else {
      snprintf( bakname, PATH_MAX-1, "%s.bak", ofname );
      bakname[PATH_MAX-1] = '\0';
      unlink( bakname );
      rename( ofname, bakname );
      IFile->ofp = fopen( ofname, "w" );
      if ( IFile->ofp == 0 )
        nl_error( 3, "Unable to reopen output file %s", ofname );
    }

    { char buf[RESTART_BUFSIZE];
      unsigned int ScanNum = 0;
      while ( fgets( buf, RESTART_BUFSIZE, ifp ) != 0 ) {
        int col;
        char *bp = buf;
        while ( isspace( *bp ) ) bp++;
        for ( col = 1; col < ScanNum_col; col++ ) {
          while ( ! isspace(*bp) && *bp != '\0' ) bp++;
          while ( isspace(*bp) ) bp++;
        }
        if ( *bp == '\0' ) break;
        ScanNum = strtoul( bp, &bp, 10 );
        if (ScanNum == GlobalData.RestartAt) { // What if ScanNum is decreasing?
          break;
        } else {
          int n_skip_params = n_base_input_params;
          if (verbose & V_INFO) n_skip_params += 9;
          for ( ++col; col <= n_skip_params; ++col ) {
            while ( isspace(*bp) ) bp++;
            while ( ! isspace(*bp) && *bp != '\0' ) bp++;
          }
          { std::vector<argref>::iterator arg;
            for (arg = absorb->args.begin(); arg != absorb->args.end(); ++arg) {
              func_line *line = arg->arg->is_line();
              if ( line ) {
                // read floating
                while (isspace(*bp)) ++bp;
                if (*bp == '0') {
                  line->line_fix();
                } else if (*bp == '1') {
                  line->line_float();
                } else nl_error(3, "Restart Expected 0 or 1 for float of line[%d]", line->line_number);
                ++bp;
                if (!isspace(*bp)) break;
                // read threshold
                char *eos;
                line->S_thresh = strtod(bp, &eos);
                bp = eos;
                if (!isspace(*bp)) break;
              }
            }
          }
          func->input_params(bp, func_evaluator::op_value);
          func->input_params(bp, func_evaluator::op_float);
          // I think we can ignore anything past op_float:
          // if (verbose & 0x20)
            // func->input_params(bp, func_evaluator::op_dscl);
          fprintf( IFile->ofp, "%s", buf );
        }
      }
      fclose( ifp );
      IFile->read( ScanNum ); // To initialize wndata
      { std::vector<argref>::iterator arg;
        for (arg = absorb->args.begin(); arg != absorb->args.end(); ++arg) {
          func_line *line = arg->arg->is_line();
          if ( line && line->param_fixed( line->dnu_idx ) ) {
            line->fixed = 1;
            if ( line->param_fixed( line->n_idx ) )
              nl_error( 0, "Line at %.4" FMT_F " is off", line->nu );
            else
              nl_error( 0, "Line at %.4" FMT_F " is fixed", line->nu );
          }
        }
      }
      return;
    }
    nl_error( 3, "Unexpected loop exit in handle_restart");
  } else {
    IFile->ofp = fopen( ofname, "a" );
    if ( IFile->ofp == 0 )
      nl_error( 3, "Unable to open output file %s", ofname );
  }
}

FILE *fitdata::pathopen( const char *path, const char *format, int fileno ) {
  static const int POBUFSIZE = 256;
  char buf[POBUFSIZE];
  int n = snprintf( buf, POBUFSIZE-1, "%s/", path );
  if ( n < 0 || n >= POBUFSIZE-1 ) return 0;
  n = snprintf( buf+n, POBUFSIZE-n-1, format, fileno );
  if ( n < 0 || n >= POBUFSIZE-1 ) return 0;
  FILE *fp = fopen( buf, "w" );
  return fp;
}

int fitdata::adjust_params(adjust_event when) {
  return func_evaluator::global_evaluation_order.adjust_params(when,
    PTf->P, PTf->T);
}

/**
  Handles the complete fit for one raw scan file.
 */
int fitdata::fit( ) {
  ICOS_Float *yin = IFile->sdata->data;
  int i;

  while (adjust_params(scan_init)) ;

  // Evaluation of range of the input over which we should
  // fit. This should not be limited to the absorb func.
  // It should be a virtual function of func_evaluator
  Start = End = -1;
  {
    // Note: Wavenumber decreases with sample number
    ICOS_Float nu_F0 = absorb->get_arg(func_abs::nu_F0_idx );
    ICOS_Float wnStart = IFile->wndata->data[SignalEnd] + nu_F0;
    ICOS_Float wnEnd = IFile->wndata->data[SignalStart] + nu_F0;
    while ( func->line_check( 0, wnStart, wnEnd, PTf->P, PTf->T) != 0 );
    func->line_check( 1, wnStart, wnEnd, PTf->P, PTf->T);
    ICOS_Float EwnStart = 0., EwnEnd = 0.;
    func->line_check( 2, EwnStart, EwnEnd, PTf->P, PTf->T);
    if ( EwnStart != 0. && EwnEnd != 0. ) {
      if ( EwnStart > wnStart ) wnStart = EwnStart;
      if ( EwnEnd < wnEnd ) wnEnd = EwnEnd;
      Start = IFile->wn_sample( wnEnd - nu_F0 );
      End = IFile->wn_sample( wnStart - nu_F0 );
    }
  }
  if ( End == -1 && Start == -1) {
    // nl_error( 3, "All lines have been excluded!" );
    End = SignalEnd;
    Start = SignalStart;
  }
  nl_assert( End > Start );
  npts = End - Start + 1;
  nl_assert(npts <= npts_vec);

  for ( i = 0; i < npts; i++ ) x[i] = i + Start;
  y = yin + Start;

  for ( i = 0; i < mp; i++ ) p_save[i] = p[i];


  /* This block provides setup for the per-iteration verbose output */
  vctr = 0;
  if (verbose & 8) {
    if ( vfp != 0 ) fclose( vfp );
    vfp = 0;
    mlf_set_index( vmlf, IFile->mlf->index );
    if ( mlf_next_dir( vmlf ) ) {
      vfp = pathopen( vmlf->fpath, "ICOSsum.out", 0 );
    }
  }

  // And this should be done with exceptions:
  // int counter = 0;
  int err_val = setjmp(Fit_buf);
  if ( err_val == 0 ) {
    adata.x = x;
    for (;;) {
      while (adjust_params(scan_init)) ;
      // returns # of iterations or LM_ERROR (-1)
      // Defaulting opts and covar
      if (dlevmar_bc_der(levmar_func, levmar_jacf, p, y, mp, npts, lb, ub, dscl,
            GlobalData.MaxIterations, 0, info, lm_work, 0, &adata) == LM_ERROR) {
        nl_error(1, "LM_ERROR: reason %.0lf", info[6]);
        func_evaluator::dump_evaluation_order.dump();
        return 0;
      }
      if (adjust_params(scan_finalize)) {
        for ( i = 0; i < mp; ++i ) p[i] = p_save[i];
        nl_error( 0,
          "Parameters rolled back, Retrying after updating line constraints");
      } else {
        chisq = info[1]/(End-Start+1); // population variance
        return 1;
      }
    }
  } else {
    nl_error(1, "LongJmp return");
    func_evaluator::dump_evaluation_order.dump();
    return 0;
  }
}

int fitdata::n_input_params = fitdata::n_base_input_params;

/**
  @param ofp Output FILE pointer for ICOSsum.dat
  @param vofp Output FILE pointer for verbose scan data if requested
  @param fileno The scan number
  Write the fit results. This function is used for the final fit
  as well as intermediate results (verbose & 8). It writes a single
  line to the ICOSsum.dat file and, if verbose & 1,
  also generates a separate verbose scan fit file.
 */
void fitdata::lwrite(FILE *ofp, FILE *vofp, int fileno, ICOS_Float *pv) {
  int i;
  if ( vofp != 0 ) {
    // Write verbose output file
    jmp_buf Fit_buf_save;
    memcpy( Fit_buf_save, Fit_buf, sizeof(Fit_buf) );
    if ( setjmp(Fit_buf) == 0 ) {
      if (verbose & V_CHKJAC) {
        func_parameter::checking_jacobian = true;
        dlevmar_chkjac(levmar_func, levmar_jacf, pv, mp, npts, &adata, jacerr);
        func_parameter::checking_jacobian = false;
      }
      if (verbose & V_CHKDER) {
        ICOS_Float delta = 1E-6;
        levmar_func(pv, hxjac, mp, npts, &adata);
        dlevmar_fdif_forw_jac_approx(levmar_func, pv, hxjac, hxxjac,
          delta, difjac, mp, npts, &adata);
        func_parameter::checking_jacobian = true;
      }
      func_evaluator::pre_evaluation_order.pre_eval(x[1], pv);
      for (i = 0; i < npts; ++i) {
        ICOS_Float yfit;
        func_evaluator::global_evaluation_order.evaluate_partials(x[i], pv);
        yfit = func->value;
        fprintf( vofp, "%12.6" FMT_E " %14.8" FMT_E " %12.6" FMT_E
          " %12.6" FMT_E " %12.6" FMT_E " %12.6" FMT_E,
          x[i], ICOSfile::wndata->data[i+Start],
          y[i], yfit, base->value, absorb->value );
        if (verbose & V_VOIGT)
          absorb->print_intermediates(vofp);
        if (verbose & V_DERIVATIVES) {
          for (unsigned j = 0; j < func->params.size(); j++ ) {
            fprintf( vofp, " %12.6" FMT_E, func->params[j].dyda );
          }
        }
        if (verbose & V_CHKDER) {
          for (unsigned j = 0; j < func_parameter::n_parameters; ++j) {
            fprintf(vofp, " %12.6" FMT_E, difjac[i*mp+j]);
          }
        }
        if (verbose & V_CHKJAC) {
          fprintf(vofp, " %12.6" FMT_E, jacerr[i]);
        }
        fprintf( vofp, "\n" );
      }
      if (verbose & V_CHKDER)
        func_parameter::checking_jacobian = false;
    } else {
      nl_error( 3, "unexpected longjmp during re-evaluation" );
    }
    memcpy( Fit_buf, Fit_buf_save, sizeof(Fit_buf_save) );
    fclose(vofp);
  }
  if ( ofp != 0 ) {
    // Write line of output to ICOSsum.dat
    int n_i_p = 6;
    nl_assert( ScanNum_col == 1 );
    fprintf( ofp, "%6d %6.2lf %6.2lf %12.5le %d %d",
      fileno, PTf->P, PTf->T, chisq, Start, End);
    if (verbose & V_INFO) {
      n_i_p += 9;
      fprintf(ofp,
        " %9.4" FMT_E " %9.4" FMT_E " %9.4" FMT_E
        " %9.4" FMT_E " %5.0" FMT_F " %5.0" FMT_F
        " %5.0" FMT_F " %5.0" FMT_F " %5.0" FMT_F,
        info[1], info[2], info[3],
        info[4], info[5], info[6],
        info[7], info[8], info[9]);
    }
    { std::vector<argref>::iterator child;
      for (child = absorb->args.begin(); child != absorb->args.end(); ++child) {
        func_line *line = child->arg->is_line();
        if (line) {
          fprintf( ofp, " %d %12.5" FMT_E, line->fixed, line->S_thresh );
          n_i_p += 2;
        }
      }
    }
    nl_assert(n_i_p == n_input_params);
    // This is not a simple recursive dump of parameters, as
    // that could be unnecessarily dependent on function build
    // order and structure. Instead, specific subclasses will
    // impose order as necessary.
    func->output_params(ofp, func_evaluator::op_value);
    func->output_params(ofp, func_evaluator::op_float);
    if (verbose & V_SCALE) {
      func->output_params(ofp, func_evaluator::op_dscl);
    }
    if (verbose & V_VOIGT) {
      std::vector<argref>::iterator child;
      for (child = absorb->args.begin(); child != absorb->args.end(); ++child) {
        func_line *line = child->arg->is_line();
        if (line) {
          fprintf(ofp, " %13.7le %13.7le", line->Corr_Tref, line->Ks);
        }
      }
    }
    fprintf( ofp, "\n" );
    fflush( ofp );
  }
}

void fitdata::write() {
  FILE *fp = (verbose&1) ? IFile->writefp() : 0;
  this->lwrite(IFile->ofp, fp, PTf->ScanNum, p);
}

void fitdata::vwrite(ICOS_Float *pv, ICOS_Float *J) {
  if (verbose & 8) {
    FILE *vvfp = pathopen( vmlf->fpath, "%04d.dat", vctr );
    lwrite(vfp, vvfp, vctr, pv);
    if ( verbose & 0x10 ) {
      FILE *vvfp = pathopen( vmlf->fpath, "%04d.jac", vctr );
      int i, j;
      for (i = 0; i < npts; ++i) {
        for (j = 0; j < mp; ++j) {
          fprintf(vvfp, " %13.7le", (double)*J);
          ++J;
        }
        fprintf(vvfp, "\n");
      }
      fclose(vvfp);
    }
    ++vctr;
  }
}
