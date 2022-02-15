#ifndef ICOSfit_H_INCLUDED
#define ICOSfit_H_INCLUDED

#include "config.h"
#include "nl.h"
#include "funceval.h"
#include "levmar_func.h"
#include "ptread.h"

#define ICOSFIT_VERSION "4.2.8" FLOAT_STYLE
#define ICOSFIT_VERSION_DATE "2/8/2022"

class fitdata {
  public:
    fitdata( PTfile *ptf, ICOSfile *IF,
       func_evaluator *f, func_evaluator *baseline, func_abs *abs );
    void handle_restart( const char *ofname );
    int fit();
    void write();
    void lwrite(FILE *ofp, FILE *vofp, int fileno, ICOS_Float *pv);
    void vwrite(ICOS_Float *pv, ICOS_Float *J);
    FILE *pathopen( const char *path, const char *format, int fileno );
    int adjust_params(adjust_event when);

    // int BaseStart;
    // int BaseEnd;
    /** The 0-based index of the first sample of the SignalRegion adjusted backwards
        to account for the number of samples in the ICOS skew calculation
        (if any). */
    int SignalStart;
    /** The 0-based index of the last sample of the SignalRegion */
    int SignalEnd;
    /** The index of the first sample in the range of the raw scan data we will fit */
    int Start;
    /** The index of the last sample in the range of the raw scan data we will fit */
    int End;
    /** The number of samples of the raw scan data we will fit */
    int npts;
    /** The allocated length of the x vector. npts_vec >= npts */
    int npts_vec;
    /** Total number of parameters in p */
    int mp;
    /** Upper bound vector of length mp. Use DBL_MAX for unbounded. */
    ICOS_Float *ub;
    /** Lower bound vector of length mp. Use -DBL_MAX for unbounded. */
    ICOS_Float *lb;
    /** Vector of fit parameters of length mp. */
    ICOS_Float *p;
    /** A copy of the p vector for use when rolling back */
    ICOS_Float *p_save;
    /** Scale value for parameters in p */
    ICOS_Float *dscl;
    /** boolean vector indicating whether parameters are floating */
    bool *is_floating;
    /** Result vector for checking Jacobian when verbose&V_CHKJAC */
    ICOS_Float *jacerr;
    /** Jacobian diagnostic buffer used when verbose&V_CHKDER */
    ICOS_Float *difjac;
    /** func output buffer used when verbose&V_CHKDER */
    ICOS_Float *hxjac;
    ICOS_Float *hxxjac;
    /** Vector of length npts_vec, npts of which are initialized to
        the sample numbers we will fit. */
    ICOS_Float *x;
    /** Pointer into the raw scan data at the starting sample (Start)
        that we will fit */
    ICOS_Float *y;
    ICOS_Float chisq;
    /** The function we will be fitting. */
    func_evaluator *func;
    /** The portion of func that defines the baseline. */
    func_evaluator *base;
    /** The portion of func that defines absorbption. */
    func_abs *absorb;
    PTfile *PTf;
    ICOSfile *IFile;
    int verbose;
    int vctr;
    FILE *vfp;
    mlf_def_t *vmlf;
    levmar_adata_t adata;
    double *lm_work;
    double *info;
    static const int n_base_input_params = 6;
    static int n_input_params;
    static const int ScanNum_col = 1;
  private:
    // int mfit, mf_size;
    // ICOS_Float *atry,*beta,*da,**oneda, *dyda;
    ICOS_Float opts[5];
};

// Located in build.cc
extern fitdata *build_func();

#endif
