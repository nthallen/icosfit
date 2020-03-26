#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <set>
#include <cfloat>
#include "nl.h"
#include "funceval.h"
#include "global.h"
#include "ptread.h"

static ICOS_Float get_molwt( int isotopomer ) {
  switch (isotopomer) {
    case 11: return 18.010565; // H_2O
    case 12: return 20.014811; // H_2{}^{18}O
    case 13: return 19.01478;  // H_2{}^{17}O
    case 14: return 19.01674;  // HDO
    case 15: return 21.020985; // HD^{18}O
    case 16: return 20.020956; // HD^{17}O
    case 21: return 43.989830; // CO2
    case 22: return 44.993183; // CO_2{}^{13}C
    case 23: return 45.994076; // CO_2{}^{18}O
    case 24: return 44.994045; // CO_2{}^{17}O
    case 41: return 44.001060; // N2O
    case 42: return 44.998096; // N^{15}NO
    case 43: return 44.998096; // NN^{15}O
    case 61: return 16.031300; // CH_4
    case 62: return 17.034655; // C13H4
    case 63: return 17.037476; // CH3D
    case 81: return 29.997990; // NO
    case 101: return 45.992905; // NO2
    case 131: return 17.002741; // OH
    case 151: return 35.976677; //H35Cl
    case 152: return 37.973728; //H37Cl
    case 153: return 36.983; // D35Cl
    case 154: return 38.98; // D37Cl
    case 201: return 30.010565; // H2C0
    case 202: return 31.013920; // H213CO
    case 203: return 32.014812; // H2C18O
    default:
      nl_error( 3,
        "Uncatalogued isotopomer '%d': Edit funceval.c get_molwt()",
         isotopomer );
      return 0; // Never reached
  }
}

/**
  func_line object has at least 3 parameters
    dnu_idx = 0: Fine location in cm-1
    w_idx = 1: Doppler E-folding halfwidth in cm-1
    n_idx = 2: Number Density in molecules/cm3
  These parameters are all initialized to zero.
 
  There are also a raft of fixed parameters based on HITRAN
  data for individual lines:
  molecule
  isotope
  nu = wavenumber
  S = spectral line intensity
  G_air = Gamma_air
  E = Lower state energy of the transition
  n = coefficient of temerature dependence or air-broadened hw
  delta = air-broadened pressure shift
  ipos = sample number of line center at start
 */
const int func_line::dnu_idx = 0;
const int func_line::w_idx = 1;
const int func_line::n_idx = 2;
const double func_line::DRTPI = 0.5641895835477563; // 1/SQRT(pi)
const double func_line::Tref = 296.; // K
const double func_line::C2 = 1.4388; // cm K second radiation constant hc/k
const double func_line::Ged_range = 1.3; // gamma_ed range [Ged_calc/Ged_range,Ged_calc*Ged_range]
double func_line::nu0 = 0.;
int func_line::n_lines = 0;

func_line::func_line( const char *name, int mol, int iso,
          double nu_in, double S_in, double G_air_in, double E_in,
          double n_in, double delta_in, unsigned int ipos_in, double threshold,
          int fix_w, int fix_fp, func_parameter *N ) :
    func_evaluator(name, true, ++n_lines) {
  line_number = n_lines;
  append_func(new func_parameter("dnu", 0., true, line_number));
  append_func(new func_parameter("gd", 1., true, line_number));
  append_func(N ? N : new func_parameter("N", 0., true, line_number));
  fixed = true;
  outside = false;
  fix_finepos = fix_fp;
  fix_width = fix_w;
  // prev_numdens = 0.;
  // prev_ged = 1.;
  rolledback = 0;
  isotopomer = mol*10 + iso;
  QT = 0;
  molwt = get_molwt(isotopomer);
  if ( nu0 == 0. ) nu0 = floor(nu_in);
  nu = nu_in;
  nu1 = nu_in - nu0;
  S = S_in;
  G_air = G_air_in;
  E = E_in;
  n_air = n_in;
  delta = delta_in;
  S_thresh = threshold;
  ipos = ipos_in-MLBASE;
  Corr_Tref = 1/(exp(-C2 * E / Tref ) * (1-exp(-C2*nu/Tref)));
  nu_F0_idx = -1;
}

func_line::~func_line() {
  delete(QT);
}

unsigned int func_line::adopted(func_evaluator *new_parent) {
  append_func(new_parent->args[0].arg);
  nu_F0_idx = args.size()-1;
  return func_evaluator::adopted(new_parent);
}

void func_line::init(ICOS_Float *p) {
  func_evaluator::init(p);
  if (fixed) line_fix();
  else line_float();
  if (QT == 0)
    QT = new QTdata(isotopomer);
  set_param(dnu_idx, 0.);
}

void func_line::print_config( FILE *fp ) {
  fprintf( fp,
    "  %d %d %.6lf %.4" FMT_E
    " %.4" FMT_F " %.4" FMT_F
    " %.2" FMT_F " %.6" FMT_F " %lu\n",
    isotopomer/10, isotopomer%10, nu1+nu0, S, G_air, E,
    n_air, delta, params.size() );
}

void func_line::print_intermediates(FILE *fp) {}

int func_line::adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T) {
  // Eliminated a check for drifting. Taken care of in func_abs.
  if (when == scan_init) { // first initialization
    double Spt = S * QT->evaluate(T) * exp(-C2*E/T) * (1-exp(-C2*nu/T))
            * Corr_Tref;
    Ks = Spt * GlobalData.CavityLength * DRTPI;
    Ged_calc = 4.30213e-7 * nu * sqrt(T/molwt);
    nu_P = nu1 + delta * P/760.;
    rolledback = 0;
    set_param_scale(w_idx, Ged_calc);
    ICOS_Float N = get_arg(n_idx);
    if (N <= 1e12) N = 1e12;
    if (GlobalData.Sigma > 0) N = GlobalData.Sigma;
    set_param_scale(n_idx, N);
  }
  ICOS_Float numdens = get_arg(n_idx);
  // Negative number densities, although physically nonsensical,
  // are important for statistical purposes. If we arbitrarily
  // force the fit to return values >= 0, that pushes the mean
  // values above zero even when no absorption is present.
  if (when == scan_init) {
    if (param_fixed(w_idx) ) {
      // The following formula comes from Liz's old lecture notes
      // (Webster?)
      // Value is stored in wavenumbers. It must be
      // multiplied by s_wn (param sc_idx) to get samples.
      // This will probably have to be adjusted
      // to take into account the laser line width
      set_param(w_idx, Ged_calc);
      set_param_limits(w_idx, Ged_calc, Ged_calc);
    } else {
      set_param_limits(w_idx, Ged_calc/Ged_range, Ged_calc*Ged_range);
    }
  }
  ICOS_Float gamma_ed = get_arg(w_idx);
  if (when == scan_finalize) {
    ICOS_Float strength = gamma_ed > 0 ? Ks * numdens / gamma_ed : 0.;
    if ( fixed ) {
      if ( !outside && strength > S_thresh * 4. ) {
        if ( rolledback < 2 ) {
          nl_error( 0, "Floating line %d (strength %" FMT_G ")",
                      line_number, strength );
          line_float();
          return 2;
        } else nl_error( 0, "NOT re-floating line %d",
                  line_number );
      }
    } else {
      if ( strength < S_thresh ) {
        nl_error( 0, "Fixing line %d (strength %" FMT_G ")",
                      line_number, strength );
        line_fix();
        ++rolledback;
        return 1;
      }
    }
  }
  return 0;
}

func_line *func_line::is_line() { return this; }

ICOS_Float func_line::line_start() {
  return (nu_P - GlobalData.RightLineMarginMultiplier*get_arg(w_idx));
}

ICOS_Float func_line::line_end() {
  return (nu_P + GlobalData.LeftLineMarginMultiplier*get_arg(w_idx));
}

/**
 * @param include 0, 1 or 2 to indicate pass
 * @param start The lowest wavenumber value in the current scan range
 * @param end The highest wavenumber value in the current scan range
 * @param P Pressure in Torr
 * @param T Temperature in Kelvin
 * @return non-zero if the range has changed
 *
 * line_check(include, start, end, P, T);
 * operates in three passes. First, include is set to 0 to
 * indicate the 'exclude' step. A line is excluded if it
 * hits the start or end boundary, and if so, the boundaries
 * are moved in to also exclude any significant portion
 * of this line. If the boundaries need to be moved, we
 * return 1, and another exclude pass is indicated. This
 * is necessary to deal with overlapping lines.
 *
 * Refinement to the exclusion: If a line hits the boundary,
 * we first try to re-evaluate it's width by fixing the line
 * and calling adjust_params. If that helps, then its threshold
 * needs to be raised. If it doesn't help, then turn it off.
 *
 * Next, include is set to 1. Any lines that were previously
 * excluded that now fall within the sample range are re-enabled.
 *
 * Once a final set of lines has been determined, include
 * is set to 2 to indicate the 'include' step. Here the
 * boundaries are expanded to include all the lines which
 * are still 'on'.
 */
int func_line::line_check(int include, ICOS_Float& start, ICOS_Float& end,
                    ICOS_Float P, ICOS_Float T) {
  ICOS_Float ls = line_start();
  ICOS_Float le = line_end();
  // func_line *next = lnext();
  if ( include == 0 ) {
    int rv = -1;
    if ( ! fixed && ( ls < start || le > end ) ) {
      ICOS_Float save_thresh = S_thresh;
      line_fix();
      S_thresh = Ks * get_arg(n_idx)*2/get_arg(w_idx);
      adjust_params(scan_init, P, T);
      ls = line_start();
      le = line_end();
      if ( ls >= start && le <= end ) {
        nl_error(0, "Raised threshold on line %d near boundary",
                      line_number );
      } else {
        nl_error( 0, "Fixing line %d (%.4" FMT_F ",%.4" FMT_F ")",
                          line_number, ls, le );
        S_thresh = save_thresh;
      }
    }
    if ( le < start || ls > end ) {
      ICOS_Float lem = le+GlobalData.LeftLineMargin;
      ICOS_Float lsm = ls-GlobalData.RightLineMargin;
      rv = 0;
      if ( ls < start && lem - GlobalData.LineMarginHysteresis > start ) {
        start = lem; rv = 1;
        if ( GlobalData.Verbosity & 2 )
          nl_error( 0, "Exclude: Updated start to %.4" FMT_F, start );
      }
      if ( le > end && lsm + GlobalData.LineMarginHysteresis < end ) {
        end = lsm; rv = 1;
        if ( GlobalData.Verbosity & 2 )
          nl_error( 0, "Exclude: Updated end to %.4" FMT_F, end );
      }
      if ( ! param_ref_fixed(n_idx) ) {
        nl_error( 0, "Turning off line %d (%.4" FMT_F ",%.4" FMT_F ")",
                          line_number, ls, le );
        fix_param(n_idx);
        if (param_fixed(n_idx)) { // Can be false if N is shared in a group
          set_param(n_idx, 0.);
          set_param_limits(n_idx, 0., 0.);
        }
        line_fix();
        outside = true;
      }
      if ( rv != 0 ) return rv;
    }
  }
  if (include == 1) {
    if ( ls >= start && le <= end && param_fixed(n_idx) ) {
      nl_error( 0, "Turning on line %d (%.4" FMT_F ",%.4" FMT_F ")",
                          line_number, ls, le );
      float_param(n_idx);
      outside = false;
      // We don't actually line_float() until the fit raises the
      // number density high enough.
    }
  }
  if (include == 2) {
    if ( ! param_fixed(n_idx) ) {
      if ( start == 0. || ls-GlobalData.RightLineMargin < start )
        start = ls-GlobalData.RightLineMargin;
      if ( end == 0. || le+GlobalData.LeftLineMargin > end )
        end = le+GlobalData.LeftLineMargin;
    }
  }
  return 0;
}

void func_line::line_fix() {
  fix_param(dnu_idx); // Limits will be set in adjust_params
  { ICOS_Float dnu = get_arg(dnu_idx);
    set_param_limits(dnu_idx, dnu, dnu);
  }
  fix_param(w_idx); // Limits must be set by adjust_params
  fix_param(nu_F0_idx);
  if (param_fixed(nu_F0_idx)) {
    ICOS_Float nu_F0 = get_arg(nu_F0_idx);
    set_param_limits(nu_F0_idx, nu_F0, nu_F0);
  }
  fixed = true;
}

void func_line::line_float() {
  float_param(nu_F0_idx);
  set_param_limits(nu_F0_idx, -DBL_MAX, DBL_MAX);
  if ( !fix_finepos ) {
    float_param(dnu_idx);
    set_param_limits(dnu_idx,
      -GlobalData.TolerableDrift, GlobalData.TolerableDrift);
  }
  if ( !fix_width)
    float_param(w_idx); // Limits must be set by adjust_params
  fixed = false;
}
