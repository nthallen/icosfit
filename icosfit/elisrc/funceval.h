#ifndef FUNCEVAL_H_INCLUDED
#define FUNCEVAL_H_INCLUDED

#include <stdio.h>
#include <vector>
#include <stdint.h>
#include "config.h"

/**
 * Argument for adjust_params() to identify at what stage we are operating.
 * Global one-time initialization should be handled in init(p) rather than
 * adjust_params.
 */
enum adjust_event {scan_init, scan_finalize};

class paramref {
  public:
    inline paramref(int arg_i, int param_i) {
      arg_num = arg_i;
      param_num = param_i;
    }
    int arg_num;
    int param_num;
};

/**
 * parameter is used to keep track of the parameters referenced by
 * a func_evaluator. There is not a 1:1 relationship between actual
 * parameters and parameter objects, since a func_evaluator references
 * all the parameters that its children do. The parameters themselves
 * are characterized by the p, ul and ub vectors. If we want to
 * mark a parameter as fixed or floating, we probably need to restore
 * the ia vector.
 */
class parameter {
  public:
    inline parameter(int idx, const char *iname = 0)
      : index(idx), name(iname) {}
    int index;
    const char *name;
    ICOS_Float dyda;
    std::vector<paramref> refs;
};

class func_evaluator;
class func_line;

class argref {
  public:
    inline argref(func_evaluator *arg_in, unsigned int rn) :
      arg(arg_in), refnum(rn), dyda(0) {}
    func_evaluator *arg;
    unsigned int refnum;
    ICOS_Float dyda; ///< Partial with respect to this argument
};

class evaluation_order {
  public:
    std::vector<func_evaluator*> order;
    void set(func_evaluator *func, bool top = true, bool clear = false);
    void set_pre_order(func_evaluator *func, bool top = true, bool clear = false);
    void set_children(func_evaluator *func);
    void add(func_evaluator *func);
    void evaluate(ICOS_Float x, ICOS_Float *p);
    void evaluate_partials(ICOS_Float x, ICOS_Float *p);
    void pre_eval(ICOS_Float x, ICOS_Float *p);
    void init(ICOS_Float *p);
    void dump();
    int adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T);
};

class func_evaluator {
  public:
    func_evaluator(const char *name, bool indexed = false, int index = 0); 
    /**
     * @param x The x value (sample) at which to evaluate the function.
     * @param p The parameter vector
     * Evaluates the function at x given the parameter values p and
     * assuming all the input arguments have already been evaluated,
     * as guaranteed by the global_evaluation_order.
     */
    virtual void evaluate(ICOS_Float x, ICOS_Float *p);
    /**
     * @param x The x value (sample) at which to evaluate the function.
     * @param p The parameter vector
     * Called once before the evaluation of a scan (so once on each
     * iteration of the LM algorithm.) The default does nothing. This
     * is overridden in funcskew to initialize the skew calculation
     * for earlier samples.
     */
    virtual void pre_eval(ICOS_Float x, ICOS_Float *p);
    /**
     * Evaluates the partial derivatives with respect to
     * all relevant parameters. func_evaluator::evaluate()
     * is responsible for calculating partials with respect
     * to the arguments, which may be functions of other
     * arguments and parameters. This finishes the calculation
     * with respect to the underlying parameters.
     */
    virtual void evaluate_partials();
    /**
      @param p vector of paramter values
      @param ub vector of parameter upper bounds
      @param lb vector of parameter lower bounds
      @param is_floating vector of floating status
      @param dscl vector of scale values
      
      p, ub, lb and dscl are the 0-based vectors whose length is
      the number of parameters (fitdata's mp attribute. The
      func_evaluators don't actually need to know mp as long as
      their parameter indexes don't exceed it.)
      init is called once when the fitdata object is
      created, and it invokes init(p) on the global_evaluation_order.
      The entire function structure has
      been assembled at this point, so the init(p)
      methods are a good place to do initializations
      that need to assume that.
     */
    void init(ICOS_Float *p, ICOS_Float *lb, ICOS_Float *ub, bool *is_floating,
      ICOS_Float *dscl);
    /**
     * @param p The initial parameter value vector
     * Invoked via global_evaluation_order once at startup.
     * Used to initialize parameter values, limits and/or
     * scaling.
     */
    virtual void init(ICOS_Float *p);
    void append_func(func_evaluator *newfunc);
    virtual unsigned int adopted(func_evaluator *new_parent);
    virtual void fix_float_param(bool float_it, unsigned int refnum);
    virtual bool param_fixed();
    inline bool param_fixed(int i) {
      return args[i].arg->param_fixed(); }
    inline void fix_param(int i) {
      args[i].arg->fix_float_param(false,args[i].refnum); }
    inline void float_param(int i) {
      args[i].arg->fix_float_param(true,args[i].refnum); }
    inline ICOS_Float get_arg(int idx) {
      return args[idx].arg->value;
    }
    /** Only legal for func_parameter */
    virtual ICOS_Float set_param(ICOS_Float value);
    /** Only legal for func_parameter */
    virtual void set_param_limits(ICOS_Float lb, ICOS_Float ub);
    /** Only legal for func_parameter */
    virtual void set_param_scale(ICOS_Float scl);
    /** Only legal when arg[idx] is a func_parameter */
    inline ICOS_Float set_param(int idx, ICOS_Float value) {
      return args[idx].arg->set_param(value);
    }
    /** Only legal when arg[idx] is a func_parameter */
    inline void set_param_limits(int idx, ICOS_Float lb, ICOS_Float ub) {
      args[idx].arg->set_param_limits(lb, ub);
    }
    /** Only legal when arg[idx] is a func_parameter */
    inline void set_param_scale(int idx, ICOS_Float scl) {
      args[idx].arg->set_param_scale(scl);
    }
    /**
     * @param alamda The Levenberg-Marquardt lambda parameter
     * @param when indicates whether this invocation is before or after the fit
     * @param P Current pressure in Torr
     * @param T Current temperature in Kelvin
     * @return non-zero if line constraints have changed after fitting.
     *
     * Function returns:
     *   0 if constraints or parameter values have not changed
     *   1 if constraints have changed after the fit and require rollback
     *   2 if constraints have changed and fit should continue without rollback
     * Assumption is that non-zero values should only be returned when
     * when==scan_finalize.
     *
     * Might be possible to get into oscillation if line gets
     * re-disabled, but that should be unlikely. If it does
     * happen, it could be detected by keeping track. It is
     * probably best to leave it disabled if it happens twice.
     * The logic is: first time it is disabled because it is
     * getting small. When the width is corrected, it then
     * turns out to be large. It is then released (without
     * rollback) but during the continuing fit, it gets
     * small again. That is probably an error, so fix it
     * once more (with rollback) which will presumably take
     * us back to the larger value, but this time, don't
     * complain at alamda==0 time.
     */
    virtual int adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T);
    virtual func_line *is_line();
    virtual int line_check(int include, ICOS_Float& start, ICOS_Float& end,
                            ICOS_Float P, ICOS_Float T);
    virtual int skew_samples();
    virtual void dump_params();
    virtual void dump_partials();
    void print_indent( FILE *fp, int indent );
    virtual void print_config(FILE *fp);
    virtual void print_intermediates(FILE *fp);
    
    typedef enum { op_value, op_float, op_dscl, op_desc, op_desc_float, op_desc_dscl } op_type;
    /**
      @param ofp FILE pointer to ICOSsum.dat
      @param fixed true to output fixed/floating bool values, false to output
      parameter values.
      
      Default will recurse through arguments, but we
      will override for efficiency and consistency as
      necessary.
      Specific overrides are necessary for:
        - func_skew: base, abs
        - func_parameter: Just the value
     */
    virtual void output_params(FILE *ofp, op_type which, int &output_col);
    void output_params(FILE *ofp, op_type which);
    virtual void input_params(char *&bp, op_type which);

    // int n_params;
    std::vector<argref> args;
    std::vector<parameter> params;
    ICOS_Float value;
    const char *name;
    func_evaluator *parent;
    unsigned int n_references;
    static evaluation_order global_evaluation_order;
    static evaluation_order pre_evaluation_order;
    static evaluation_order dump_evaluation_order;
    bool added_to_eval;
};

class func_parameter : public func_evaluator {
  public:
    func_parameter(const char *name, ICOS_Float init_value,
                   bool indexed = false, int index = 0);
    void init(ICOS_Float *p);
    int adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T);
    void fix_float_param(bool float_it, unsigned int refnum);
    bool param_fixed();
    ICOS_Float set_param(ICOS_Float value);
    void set_param_limits(ICOS_Float lb_in, ICOS_Float ub_in);
    virtual void set_param_scale(ICOS_Float scl);
    /**
     * Added for testing jacobians
     */
    void pre_eval(ICOS_Float x, ICOS_Float *p);
    void evaluate(ICOS_Float x, ICOS_Float *p);
    void evaluate_partials();
    void dump_params();
    static inline void set(ICOS_Float *p, ICOS_Float *lb, ICOS_Float *ub,
                  bool *is_floating, ICOS_Float *dscl) {
      func_parameter::p_can = p;
      func_parameter::lb = lb;
      func_parameter::ub = ub;
      func_parameter::is_floating = is_floating;
      func_parameter::dscl = dscl;
    }
    void output_params(FILE *ofp, op_type which, int &output_col);
    virtual void input_params(char *&bp, op_type which);
    
    int index; ///< Parameter's global index
    static unsigned n_parameters;
    static bool checking_jacobian;
  protected:
    ICOS_Float init_val; ///< Initialization value
    uint32_t refs_float; ///< Bit-mapped
  private:
    static ICOS_Float *p_can; ///< fitdata's p vector, the canonical list of parameter values
    static ICOS_Float *ub; ///< mp-length vector of upper bounds
    static ICOS_Float *lb; ///< mp-length vector of lower bounds
    static bool *is_floating; ///< mp-length vector for floating status
    static ICOS_Float *dscl; ///< mp-length vector for parameter scaling
};

class QTdata {
  public:
    QTdata(int isotopologue);
    ~QTdata();
    double evaluate(double T);
    int isotop;
  private:
    int Tmin, Tmax, dT;
    static const int Tref = 296;
    static const int QTBUFSIZE = 80;
    std::vector<double> QT;
};

/**
 * func_line objects share location and width parameters.
 * Derived classes include gaussian, lorentzian and voigt,
 * which each add additional parameters.
 *
 * nu - an approximation of the line wavenumber
 * nu0 - static offset to extend precision of wavenumbers
 *       Set when the first line is defined.
 * nu1 - nu-nu0 (or a more precise version thereof)
 * nu_P - nu1+delta*P/760. : pressure-shifted wavenumber less nu0
 */
class func_line : public func_evaluator {
  public:
    func_line( const char *name, int mol, int iso,
      double nu, double S, double Gair, double E, double n,
      double delta, unsigned int ipos, double threshold, int fix_w,
      int fix_fp, func_parameter *N = 0 );
    ~func_line();
    unsigned int adopted(func_evaluator *new_parent);
    int adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T);
    func_line *is_line();
    static const int dnu_idx, w_idx, n_idx;
    int nu_F0_idx;
    static int n_lines;
    int line_number; ///< 1-based indexing
    bool fixed; ///< 0 = free, 1 = fixed
    bool fix_finepos; ///< 0 = free-ish, 1 = fixed
    bool fix_width; ///< 0 = free-ish, 1 = fixed
    void init(ICOS_Float *p);
    virtual ICOS_Float line_start();
    virtual ICOS_Float line_end();
    virtual void line_fix();
    virtual void line_float();
    int line_check(int include, ICOS_Float& start, ICOS_Float& end,
            ICOS_Float P, ICOS_Float T);
    void print_config(FILE *fp);
    void print_intermediates(FILE *fp);
    //--------------------------------------------------
    int isotopomer;
    double nu;
    ICOS_Float nu1, S, G_air, E, n_air, delta;
    unsigned int ipos; // was loc...
    ICOS_Float S_thresh;
    ICOS_Float molwt;
    ICOS_Float Ks, nu_P, Corr_Tref;
    ICOS_Float Ged_calc;
    // ICOS_Float prev_numdens;
    // ICOS_Float prev_ged;
    int rolledback;
    QTdata *QT;
    static double nu0;
    static const double DRTPI; // 1/SQRT(pi)
    static const double Tref; // 296. K
    static const double C2; // 1.4388 cm K second radiation constant hc/k
    /**
     * When floating, gamma_ed will be allowed to range from
     * Ged_calc/Ged_range to Ged_calc*Ged_range. Hence Ged_range
     * must be > 1. For starters, I will set it to 1.3.
     */
    static const double Ged_range;
};

/**
 * func_abs has 1 common parameter, which is nu_F0
 * In Release 2.2, we inherit nu_F0 from func_skew.
 * Each line then has it's own dnu that func_abs owns
 * and its own 4 parameters.
 * In Release 3.0, each line has both nu_F0 and dnu.
 * Lines own dnu, nu_F0 is owned by func_abs.
 */
class func_abs : public func_evaluator {
  public:
    func_abs();
    void init(ICOS_Float *p);
    void evaluate(ICOS_Float x, ICOS_Float *p);
    int adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T);
    void print_config(FILE *fp);
    void print_intermediates(FILE *fp);
    static const int nu_F0_idx = 0;
  private:
    bool initialized;
};
typedef func_abs *func_abs_p;
typedef func_line *func_line_p;
typedef func_parameter *func_parameter_p;
inline func_abs_p new_func_abs() { return new func_abs(); }
inline func_abs_p abs_append( func_abs_p abs, func_line_p line ) {
  abs->append_func( line );
  return abs;
}
func_parameter_p Nparameter(const char *group);

class gaussian : public func_line {
  public:
    inline gaussian( int mol, int iso,
          double nu_in, double S_in, double G_air_in, double E_in,
          double n_in, double delta_in, int ipos_in, double threshold, int fix_w ) :
       func_line( "gaussian", mol, iso, nu_in, S_in, G_air_in, E_in,
           n_in, delta_in, ipos_in, threshold, fix_w, 1 ) {};
    void evaluate(ICOS_Float x, ICOS_Float *p);
};
class lorentzian : public func_line {
  public:
    inline lorentzian( int mol, int iso,
          double nu_in, double S_in, double G_air_in, double E_in,
          double n_in, double delta_in, int ipos_in, double threshold, int fix_w ) :
       func_line( "lorentzian", mol, iso, nu_in, S_in, G_air_in, E_in,
           n_in, delta_in, ipos_in, threshold, fix_w, 1 ) {};
    void evaluate(ICOS_Float x, ICOS_Float *p);
};
// Based on R.J.Wells' functions
class voigt : public func_line {
  public:
    voigt( int mol, int iso,
          double nu_in, double S_in, double G_air_in, double E_in,
          double n_in, double delta_in, int ipos_in, double threshold,
          int fix_dw, int fix_lw, int fix_fp, func_parameter *N = 0 );
    void init(ICOS_Float *p);
    void evaluate(ICOS_Float x, ICOS_Float *p);
    ICOS_Float line_width();
    ICOS_Float line_start();
    ICOS_Float line_end();
    static const int gl_idx; // 3
    int adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T);
    void line_fix();
    void line_float();
    //void dump_params(ICOS_Float *p, int indent);
    void print_intermediates(FILE *fp);
    /**
     * When floating, gamma_ed will be allowed to range from
     * Gl_calc/Gl_range to Gl_calc*Gl_range. Hence Gl_range
     * must be > 1. For starters, I will set it to 1.3.
     */
    static const double Gl_range;
  private:
    ICOS_Float prev_gl;
    ICOS_Float prev_y;
    ICOS_Float X, Y, K;
    ICOS_Float YQ, XLIMA, XLIMB, XLIMC, XLIM4;
    int RGB, RGC, RGD;
    ICOS_Float A0, B1, C0, C2, D0, D1, D2, E0, E2, E4, F1, F3, F5;
    ICOS_Float G0, G2, G4, G6, H0, H2, H4, H6, P0, P2, P4, P6, P8;
    ICOS_Float Q1, Q3, Q5, Q7, R0, R2, W0, W2, W4, Z0, Z2, Z4, Z6, Z8;
    int fix_lwidth;
};
inline func_line_p new_voigt( int mol, int iso,
    double nu, double S, double Gair, double E, double n,
    double delta, int ipos, double threshold,
    int fix_dw, int fix_lw, int fix_fp, func_parameter *NP ) {
  return new voigt( mol, iso, nu, S, Gair, E, n, delta, ipos, threshold,
                    fix_dw, fix_lw, fix_fp, NP);
}

/** baseline functions. func_base is a virtual base class
 */
class func_base : public func_evaluator {
  public:
    inline func_base(const char *name = "base") :
      func_evaluator(name), uses_nu_F0(0) {}
    int uses_nu_F0; ///< 0 or 1
};

/**
 * This is the old func_base for SVDs as a function of x
 * The file format is ICOS standard binary with the first
 * element of each column being initial parameter settings
 */
class func_base_svdx : public func_base {
  public:
    func_base_svdx( const char *filename );
    void evaluate( ICOS_Float x, ICOS_Float *p );
  private:
    ICOS_Float **baseline;
    int n_pts;
};

/**
 * This is a function supporting vectors as a function of
 * nu as well as polynomials as a function of x or nu
 * The file format is:
 * i*4  0  To distinguish from func_base_svdx format
 * i*4  1  To identify func_base_ptbnu format
 * f*8 polynomial scale factor
 * f*8 nu0 smallest value of nu
 * f*8 dnu increment between samples
 * i*2 n_vectors
 * i*2 npts per vector
 * i*2 number of polynomial coefficients (degree+1)
 * i*2 polynomial of x == 0, nu == 1
 * f*4 X n_vectors initial parameter values
 * f*4 X n polynomial coefficients initial parameter values
 * f*4 X npts X n_vectors: vector data in column order

 * Can use global SignalRegion to determine range of x
 */
class func_base_ptbnu : public func_base {
  public:
    func_base_ptbnu(const char *filename, func_evaluator *nu_F0);
    void evaluate(ICOS_Float x, ICOS_Float *p);
    void init(ICOS_Float *p);
  private:
    struct {
      double poly_scale;
      double nu0;
      double dnu;
      unsigned short n_vectors;
      unsigned short n_pts;
      unsigned short poly_coeffs;
      unsigned short poly_of_nu;
    } cfg;
    ICOS_Float **vectors;
    ICOS_Float **dvdnu;
    ICOS_Float **polyvecs;
};

class func_base_input : public func_base {
  public:
    func_base_input( func_base *base );
    void evaluate( ICOS_Float x, ICOS_Float *p );
    void init(ICOS_Float *p);
  private:
};

extern func_base *pick_base_type(const char *filename, func_evaluator *nu_F0);


//-------------
// func_skew.c
//-------------
class func_beta : public func_evaluator {
  public:
    func_beta(func_abs *abs);
    void evaluate(ICOS_Float x, ICOS_Float *p);
};

class func_gamma : public func_evaluator {
  public:
    func_gamma(func_beta *beta);
    void evaluate(ICOS_Float x, ICOS_Float *p);
  private:
    ICOS_Float R2;
};

class func_epsilon : public func_evaluator {
  public:
    func_epsilon(func_gamma *gamma);
    void evaluate(ICOS_Float x, ICOS_Float *p);
  private:
    ICOS_Float N;
};

class func_delta : public func_evaluator {
  public:
    func_delta(func_epsilon *epsilon, func_gamma *gamma);
    void evaluate(ICOS_Float x, ICOS_Float *p);
};

class func_g : public func_evaluator {
  public:
    func_g(func_base *base, func_beta *beta, func_delta *delta);
    void evaluate(ICOS_Float x, ICOS_Float *p);
};

class skew_data {
  public:
    skew_data();
    void set_n_params(int n_gp, int n_epsp);
    ICOS_Float g;
    ICOS_Float *dg; // allocate n_params
    ICOS_Float eps;
    ICOS_Float *deps; // allocate n_params
    ICOS_Float Power;
    int initialized;
    int n;
};

/**
 * func_skew applies the cell skew function of ICOS. Its two
 * children define the input power curve (base) and the
 * intra-cavity absorption (abs).
 * base and abs have mostly independent parameters, but if
 * the base function uses nu_F0, that parameter is shared.
 * The skew member is used as an M-element circular buffer.
 */
class func_skew : public func_evaluator {
  public:
    func_skew(func_g *g, func_epsilon *epsilon);
    void init(ICOS_Float *p);
    void pre_eval(ICOS_Float x, ICOS_Float *p);
    void evaluate(ICOS_Float x, ICOS_Float *p);
    void evaluate_partials();
    int skew_samples();
    void output_params(FILE *ofp, op_type which, int &output_col);
    virtual void input_params(char *&bp, op_type which);
  private:
    void sub_eval(ICOS_Float x, ICOS_Float *p);
    ICOS_Float N;
    int M;
    ICOS_Float R2, R2N, P_scale;
    skew_data *skew; // We will have M of these
    int *depsi; // map from g parameters to eps parameters
    int skewidx;
    func_evaluator *basep;
    evaluation_order skew_eval_order;
};

/**
 * func_noskew calculates absorption for a simple multi-pass
 * cell. Its two children define the input power curve (base)
 * and the intra-cavity absorption (abs).
 * base and abs have mostly independent parameters, but if
 * the base function uses nu_F0, that parameter is shared.
 */
class func_noskew : public func_evaluator {
  public:
    func_noskew(func_base *base, func_abs *abs);
    void evaluate(ICOS_Float x, ICOS_Float *p);
  private:
    ICOS_Float N_Passes;
    int n_base_params, n_abs_params;
    func_base *basep;
    func_abs *absp;
};

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

#endif
