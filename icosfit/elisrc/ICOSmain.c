#include "ICOSfit.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "clp.h"
#include "mlf.h"
#include "global.h"

/**
   verbose & 1 => V_CURVES output verbose files with fit curves for each scan
   verbose & 2 => V_INFO include info[1:9] in output
   verbose & 4 => V_CHKJAC check Jacobian and report in standard output file
   verbose & 8 => V_ITERATIONS output verbose files with fit curves for each iteration
   verbose & 0x10 16 => V_DERIVATIVES Include analytic derivatives in verbose output files
   verbose & 0x20 32 => V_SCALE Include dscl with parameters in output files
   verbose & 0x40 64 => V_CHKDER Estimate derivatives via finite differences and include in fit curves files
   verbose & 0x80 128 => V_VOIGT Output X and K values for each voigt line in verbose(1) fits
*/

void ICOS_init() {
  if (ShowVersion) {
    printf("icosfit version %s, %s\n", ICOSFIT_VERSION, ICOSFIT_VERSION_DATE);
    exit(0);
  }
  #if HAVE_LIBMALLOC_G
    mallopt(MALLOC_CKACCESS, 1);
    mallopt(MALLOC_FILLAREA, 1);
  #endif
}

static const char *output_filename( const char *name ) {
  static char fname[PATH_MAX];

  if ( name[0] == '/' ) return name;
  snprintf( fname, PATH_MAX-1, "%s/%s", GlobalData.OutputDir, name );
  fname[PATH_MAX-1] = '\0';
  return fname;
}

void ICOS_main() {
  fitdata *fitspecs;

  { struct stat buf;
    if ( stat(GlobalData.OutputDir, &buf) || ! S_ISDIR(buf.st_mode) ) {
      if (mkdir(GlobalData.OutputDir,0775)!=0)
        nl_error(3, "Unable to create OutputDir %s: %d %s",
          GlobalData.OutputDir, errno, strerror(errno));
    }
  }
  if ( GlobalData.LogFile != 0 ) {
    const char *fname;
    char pipename[PATH_MAX+14];
    FILE *fp;

    fname = output_filename( GlobalData.LogFile );
    if (GlobalData.NoTee) {
      fp = fopen(fname, "a");
      if (fp == 0) nl_error( 3, "Unable to write to log file %s", fname);
    } else {
      snprintf( pipename, PATH_MAX+13, "/usr/bin/tee -a %s", fname );
      pipename[PATH_MAX+13] = '\0';
      fp = popen( pipename, "w" );
      if ( fp == 0 ) nl_error( 3, "Unable to create pipe to %s", pipename );
    }
    if ( dup2( fileno(fp), 1 ) == -1 )
       nl_error( 3, "Unable to dup2: %s", strerror(errno) );
    if ( dup2( fileno(fp), 2 ) == -1 )
      nl_error( 3, "Unable to dup stderr to stderr: %s", strerror(errno) );
    // fclose(fp);
  }
  if ( GlobalData.RestartAt <= 0 )
    fprintf( stderr, "ICOSfit Version %s (%s) Start\n",
      ICOSFIT_VERSION, ICOSFIT_VERSION_DATE );
  else fprintf( stderr, "\nICOSfit Version %s (%s) Restart at %d\n",
     ICOSFIT_VERSION, ICOSFIT_VERSION_DATE,
     GlobalData.RestartAt );

  if (GlobalData.ConvergenceStep <= 0 ||
      GlobalData.ConvergenceStep >= 1) {
    nl_error(3, "ConvergenceStep must be between 0 and 1");
  }
  if (GlobalData.ConvergenceCount <= 0)
    nl_error(3, "ConvergenceCount must be greater than zero");
  if (GlobalData.MaxIterations <= 0)
    nl_error(3, "MaxIterations must be greater than zero");

  fitspecs = build_func();
  while ( fitspecs->PTf->readline() != 0 ) {
    if ( ( GlobalData.ScanNumRange[0] == 0 ||
           fitspecs->PTf->ScanNum >= GlobalData.ScanNumRange[0] ) &&
         ( GlobalData.ScanNumRange[1] == 0 ||
           fitspecs->PTf->ScanNum <= GlobalData.ScanNumRange[1] ) ) {
      if ( fitspecs->IFile->read( fitspecs->PTf->ScanNum ) ) {
        if ( GlobalData.PTformat == 2 ) fitspecs->PTf->calc_wndata();
        if ( fitspecs->fit() != 0 ) {
          fitspecs->write();
          fprintf(stderr, "Successfully fit %lu: chisq = %" FMT_G "\n",
                   fitspecs->IFile->mlf->index,
                   fitspecs->chisq );
        } else {
          fprintf( stderr, "Failed to fit %lu\n", fitspecs->IFile->mlf->index );
          exit(1);
        }
      }
    }
  }
  #if HAVE_LIBMALLOC_G
    fprintf( stderr, "Checking Heap\n" );
    malloc_dump_unreferenced( 2, 1 );
  #endif
}

fitdata *build_func() {
  PTfile *ptf = new PTfile( GlobalData.PTFile );
  ICOSfile *IF = new ICOSfile( GlobalData.ICOSdir,
     GlobalData.OutputDir, GlobalData.binary );

  func_evaluator *func;
  func_base *base;
  if ( GlobalData.BaselineFile == 0 )
    nl_error(3, "BaselineFile is now required" );
  func_abs *abs = GlobalData.absorb;
  base = pick_base_type(GlobalData.BaselineFile, abs->args[0].arg);
  if ( GlobalData.N_Passes > 0 ) {
    func = new func_noskew( base, abs );
    nl_error( 0, "Using func_noskew()" );
  } else {
    if ( GlobalData.SampleRate == 0 )
      nl_error(3, "SampleRate required for skew calculation" );
    func_beta *beta = new func_beta(abs);
    func_gamma *gamma = new func_gamma(beta);
    func_epsilon *eps = new func_epsilon(gamma);
    func = new func_skew(
        new func_g(base, beta, new func_delta(eps, gamma)), eps);
    nl_error( 0, "Using func_skew()" );
  }
  fitdata::n_input_params = fitdata::n_base_input_params;
  if (GlobalData.Verbosity & V_INFO)
    fitdata::n_input_params += 9;
  std::vector<argref>::iterator child;
  for (child = abs->args.begin(); child != abs->args.end(); ++child) {
    func_line *line = child->arg->is_line();
    if (line) {
      fitdata::n_input_params += 2;
    }
  }
  fitdata *fd = new fitdata( ptf, IF, func, base, abs );
  
  // This disables the func_quad code in fitdata::fit
  // This is kluge and will be eliminated soon.
  // fd->FitBaseline = ( GlobalData.BaselineFile == 0 );

  fd->handle_restart( output_filename( GlobalData.OutputFile ) );

  { const char *fnamep;
    FILE *fp;

    assert( GlobalData.MFile != 0 );
    fnamep = output_filename( GlobalData.MFile );
    fp = fopen( fnamep, "w" );
    if ( fp == 0 ) nl_error( 3, "Unable to open MFile '%s'", fnamep );
    assert( abs != 0 && abs->args.size() != 0 && abs->args[0].arg->params.size() != 0 );
    fprintf( fp,
      "%% ICOS configuration data\n"
      "ICOSfit_format_ver = 4;\n"
      "n_input_params = %d;\n"
      "n_base_params = %ld;\n"
      "binary = %d;\n"
      "nu0 = %.0" FMT_F ";\n"
      "Verbosity = %d;\n",
      fd->n_input_params,
      base->params.size(),
      GlobalData.binary,
      func_line::nu0,
      GlobalData.Verbosity);
    fprintf(fp, "BaselineFile = '%s';\n",
      GlobalData.BaselineFile ? GlobalData.BaselineFile : "" );
    fprintf(fp, "PTEfile = '%s';\n",
      (GlobalData.PTformat == 2 && GlobalData.PTFile) ?
        GlobalData.PTFile : "" );
    fprintf(fp, "EtalonFSR = %.6" FMT_F ";\n", GlobalData.EtalonFSR);
    if (GlobalData.EtalonFeedback != 0)
      fprintf(fp, "EtalonFeedback = %.6" FMT_F ";\n",
          GlobalData.EtalonFeedback);
    fprintf(fp, "MirrorLoss = %.5" FMT_E ";\n", GlobalData.MirrorLoss);
    fprintf(fp, "N_Passes = %d;\n", GlobalData.N_Passes);
    fprintf(fp, "SampleRate = %" FMT_F ";\n", GlobalData.SampleRate);
    fprintf(fp, "SkewTolerance = %.5" FMT_E ";\n", GlobalData.SkewTolerance);
    fprintf(fp, "BackgroundRegion = [ %d %d ];\n",
      GlobalData.BackgroundRegion[0], GlobalData.BackgroundRegion[1]);
    abs->print_config( fp );
    int output_col = 7;
    fprintf(fp,
      "\n"
      "%% Output file column definitions\n"
      "output_cols = {\n"
      "  'ScanNum' %% col 1\n"
      "  'Pressure Torr' %% col 2\n"
      "  'Temperature K' %% col 3\n"
      "  'chisq (or something like it)' %% col 4\n"
      "  'Starting sample for fit region' %% col 5\n"
      "  'Ending sample for fit region' %% col 6\n");
    if (fd->verbose & V_INFO) {
      fprintf(fp,
        "  'info[1]: ||e||_2' %% col %d\n"
        "  'info[2]: ||J^T e||_inf' %% col %d\n"
        "  'info[3]: ||Dp||_2' %% col %d\n"
        "  'info[4]: mu/max[J^T J]_ii' %% col %d\n"
        "  'info[5]: # of iterations' %% col %d\n"
        "  'info[6]: reason for terminating' %% col %d\n"
        "  'info[7]: # of function evaluations' %% col %d\n"
        "  'info[8]: # of Jacobian evaluations' %% col %d\n"
        "  'info[9]: # of linear systems solved' %% col %d\n",
        output_col, output_col+1, output_col+2, output_col+3,
        output_col+4, output_col+5, output_col+6, output_col+7,
        output_col+8);
      output_col += 9;
    }
    { std::vector<argref>::iterator child;
      for (child = fd->absorb->args.begin();
           child != fd->absorb->args.end();
           ++child) {
        func_line *line = child->arg->is_line();
        if (line) {
          fprintf(fp, "  'Line[%d] Floating' %% col %d\n", line->line_number, output_col++);
          fprintf(fp, "  'Line[%d] Threshold' %% col %d\n", line->line_number, output_col++);
        }
      }
    }
    fd->func->output_params(fp, func_evaluator::op_desc, output_col);
    fd->func->output_params(fp, func_evaluator::op_desc_float, output_col);
    if (fd->verbose & 0x20) {
      fd->func->output_params(fp, func_evaluator::op_desc_dscl, output_col);
    }
    fprintf(fp, "};\n");
    if (fd->verbose & V_INFO) {
      fprintf(fp,
        "%%\n"
        "%% info[6] reasons for termination:\n"
        "%%   1: stopped by small gradient J^T e\n"
        "%%   2: stopped by small Dp\n"
        "%%   3: stopped by MaxIterations\n"
        "%%   4: singular matrix: Restart with increased mu\n"
        "%%   5: no further error reduction is possible. Restat with increased mu\n"
        "%%   6: stopped by small ||e||_2\n"
        "%%   7: stopped by invalid (i.e. NaN or Inf) func values\n"
        "%%   NOTE: info values in per-iteration output files are likely meaningless\n"
      );
    }
    fprintf(fp,
      "\n"
      "%% Floating values are 1 if the parameter is floating, 0 if fixed\n"
    );
    
    
    fprintf(fp,
      "\n"
      "%% p_cols is a list of parameter columns in the icosfit output file in the order\n"
      "%% of the icosfit internal parameter array. Hence p_cols[i] is the 1-based\n"
      "%% output column for the 0-based icosfit internal parameter p[i-1]\n"
      "p_cols = ["
    );
    std::vector<func_parameter *>::iterator fpi;
    const char *semicolon = "";
    for (fpi = func_parameter::parameters.begin();
         fpi != func_parameter::parameters.end();
         ++fpi) {
      fprintf(fp, "%s%d", semicolon, (*fpi)->param_col);
      semicolon = ";";
    }
    fprintf(fp, "];\n\n");

    fprintf(fp,
      "%% col_params maps parameter columns in the icosfit output file to internal\n"
      "%% 0-based icosfit parameter indices. The first 1-based column index of parameter\n"
      "%% values in the icosfit output is min(p_cols). That output column corresponds\n"
      "%% to the 0-based internal icosfit parameter col_params[1].\n"
      "col_params = ["
    );
    output_col = 0;
    fd->func->output_params(fp, func_evaluator::op_desc_col_params, output_col);
    fprintf(fp, "];\n");
    
    fprintf(fp,
      "\n"
      "%% float_cols are the 1-based column indices for the values that indicate\n"
      "%% whether the corresponding column's parameter value was fixed or floating\n"
      "%% during the fit.\n"
      "float_cols = ["
    );
    semicolon = "";
    for (fpi = func_parameter::parameters.begin();
         fpi != func_parameter::parameters.end();
         ++fpi) {
      fprintf(fp, "%s%d", semicolon, (*fpi)->float_col);
      semicolon = ";";
    }
    fprintf(fp, "];\n");

    
    fprintf(fp,
      "\n"
      "%% scale_cols are the 1-based column indices for the scale values for the\n"
      "%% corresponding column's parameter value during the fit. scale_cols will\n"
      "%% be empty unless the appropriate Verbosity bit is set.\n"
      "scale_cols = ["
    );
    if (fd->verbose & V_SCALE) {
      semicolon = "";
      for (fpi = func_parameter::parameters.begin();
           fpi != func_parameter::parameters.end();
           ++fpi) {
        fprintf(fp, "%s%d", semicolon, (*fpi)->scale_col);
        semicolon = ";";
      }
    }
    fprintf(fp, "];\n");
    fclose(fp);
  }
  return fd;
}
