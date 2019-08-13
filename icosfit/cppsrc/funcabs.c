#include <math.h>
#include <cfloat>
#include "ICOSfit.h"
#include "global.h"
#include "nl_assert.h"

func_abs::func_abs() : func_evaluator("abs"),
    initialized(false) {
  append_func(new func_parameter("nu_F0", 0.));
}

/**
 * @param p The global parameter value vector.
 * We mark nu_F0 as fixed so that it floats only when
 * there are lines which are strong enough to float.
 */
void func_abs::init(ICOS_Float *p) {
  func_evaluator::init(p);
  fix_param(nu_F0_idx);
  set_param_scale(nu_F0_idx, 0.1);
}

void func_abs::evaluate(ICOS_Float x, ICOS_Float *p) {
  std::vector<argref>::iterator child;
  
  args[0].dyda = 0.;
  value = 0;
  for (child = ++args.begin(); child != args.end(); ++child) {
    value += child->arg->value;
    child->dyda = 1;
  }
}

int func_abs::adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T) {
  if (!initialized) {
    // This block is a one-time initialization, and would thus ordinarily
    // belong in func_abs::init(), but it depends on ICOSfile::wndata,
    // and line->nu_P, both of which require initializations for a specific
    // scan.
    nl_assert(ICOSfile::wndata != 0);
    ICOS_Float nu_F0 = 0.;
    if (GlobalData.RestartAt > 0) {
      nu_F0 = get_arg(nu_F0_idx);
    } else if (GlobalData.input.nu_F0 != 0) {
      nu_F0 = GlobalData.input.nu_F0;
    } else {
      std::vector<argref>::iterator child;
      int n_lines = 0;
      for (child = args.begin(); child != args.end(); ++child) {
        func_line *line = child->arg->is_line();
        if (line) {
          if ( line->ipos >= GlobalData.SignalRegion[0] &&
               line->ipos <= GlobalData.SignalRegion[1] ) {
            nu_F0 += line->nu_P - ICOSfile::wndata->data[line->ipos];
            ++n_lines;
          }
        }
      }
      if ( n_lines > 0 ) nu_F0 /= n_lines;
      else nl_error( 3, "No valid line starting positions recorded" );
    }
    set_param(nu_F0_idx, nu_F0);
    if (param_fixed(nu_F0_idx))
      set_param_limits(nu_F0_idx, nu_F0, nu_F0);
    else
      set_param_limits(nu_F0_idx, -DBL_MAX, DBL_MAX);
    initialized = true;
  }
  return 0;
}

void func_abs::print_config(FILE *fp) {
  std::vector<argref>::iterator child;
  
  fprintf(fp, "CavLen = %.1" FMT_F ";\n", GlobalData.CavityLength);
  fprintf(fp, "n_abs_params = 1;\nn_abs_line_params = 0;\n");
  fprintf(fp, "lines = [\n");
  // Skip the first arg, which is nu_F0
  for (child = args.begin(); child != args.end(); ++child) {
    child->arg->print_config(fp);
  }
  fprintf(fp, "];\n");
}

void func_abs::print_intermediates(FILE *fp) {
  std::vector<argref>::iterator child;
  for (child = args.begin(); child != args.end(); ++child) {
    child->arg->print_intermediates(fp);
  }
}
