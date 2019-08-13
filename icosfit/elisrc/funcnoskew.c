/* funcnoskew.c */
#include <math.h>
#include <stdlib.h>
#include "funceval.h"
#include "global.h"
#include "nl.h"

/**
 * func_noskew calculates absorption for a simple multi-pass
 * cell. Its two children define the input power curve (base)
 * and the intra-cavity absorption (abs).
 * base and abs have mostly independent parameters, but if
 * the base function uses nu_F0, that parameter is shared.
 * value = base * exp(- NPasses * abs)
 * d/dbase = exp(-NPasses*abs)
 * d/dabs = base * (-NPasses)*exp(- NPasses * abs)
 */
func_noskew::func_noskew(func_base *base, func_abs *abs) :
    func_evaluator("noskew") {
  append_func(base);
  append_func(abs);
  basep = base;
  absp = abs;
  if ( basep->uses_nu_F0 != 0 && basep->uses_nu_F0 != 1)
    nl_error(4,"uses_nu_F0 must be 0 or 1");
  N_Passes = GlobalData.N_Passes +
    GlobalData.CavityFixedLength/GlobalData.CavityLength;
}

void func_noskew::evaluate(ICOS_Float x, ICOS_Float *a) {
  ICOS_Float P = basep->value;
  ICOS_Float Abs = absp->value;
  if ( isnan(P) )
    nl_error(2,"Base(%.0lf) is NaN", x);
  if ( isnan(Abs) )
    nl_error(2,"Absorb(%.0lf) is NaN", x);
  ICOS_Float eNabs = exp( -N_Passes * Abs );
  value = P * eNabs;
  if ( isnan(value) )
    nl_error(2,"noskew(%.0lf) is NaN", x);
  args[0].dyda = eNabs;
  args[1].dyda = value * (-N_Passes);
}
