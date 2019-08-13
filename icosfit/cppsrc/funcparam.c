#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <set>
#include <cctype>
#include "nl.h"
#include "funceval.h"
#include "global.h"
#include "ptread.h"
#include "nl_assert.h"

func_parameter::func_parameter(const char *name, ICOS_Float init_value,
        bool indexed, int idx) : func_evaluator(name,indexed,idx) {
  index = n_parameters++;
  init_val = init_value;
  refs_float = 0;
  pre_evaluation_order.add(this);
}

void func_parameter::init(ICOS_Float *p) {
  func_evaluator::init(p);
  params.push_back(parameter(index, name));
  params.back().dyda = 1.0;
  p[index] = init_val;
  if (init_val != 0)
    dscl[index] = fabs(init_val);
  // params are initialized as all floating, so we will
  // do the same on a per-reference basis. This means
  // references must ask to fix.
  refs_float = (1<<n_references)-1;
}

void func_parameter::pre_eval(ICOS_Float x, ICOS_Float *p) {
  if (checking_jacobian || refs_float) params.back().dyda = 1.0;
  else params.back().dyda = 0;
}

int func_parameter::adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T) {
  value = p_can[index];
  return 0;
}

/**
 * @param float_it true to float the parameter
 * @param refnum The reference number
 * If any reference wants the parameter to float, it will float.
 * All references must request a parameter to be fixed before it is
 * actually fixed.
 * Note that parameters cannot be fixed or floated until after init()
 * (or at least until init() has run on all dependents)
 */
void func_parameter::fix_float_param(bool float_it, unsigned int refnum) {
  if (float_it) {
    refs_float |= 1 << refnum;
    is_floating[params[0].index] = true;
    params.back().dyda = 1.0;
  } else {
    refs_float &= ~(1U << refnum);
    if (refs_float == 0) {
      is_floating[params[0].index] = false;
      params.back().dyda = 0;
    }
  }
}

bool func_parameter::param_fixed() {
  return !is_floating[params[0].index];
}

ICOS_Float func_parameter::set_param(ICOS_Float value) {
  this->value = p_can[params[0].index] = value;
  return value;
}

void func_parameter::set_param_limits(ICOS_Float lb_in, ICOS_Float ub_in) {
  lb[index] = lb_in;
  ub[index] = ub_in;
}

void func_parameter::set_param_scale(ICOS_Float scl) {
  dscl[index] = scl;
}

void func_parameter::evaluate(ICOS_Float x, ICOS_Float *p){
  value = p[index];
}

/**
 * Does nothing. Partial is always 1.0
 */
void func_parameter::evaluate_partials() {
}

void func_parameter::dump_params() {
  // print_indent( stderr, indent );
  fprintf( stderr, "  %s (p[%d]) = %" FMT_G "\n", name, params[0].index, value);
}

void func_parameter::output_params(FILE *ofp, op_type which, int &output_col) {
  switch (which) {
    case op_value:
      fprintf(ofp, " %13.7" FMT_E, value);
      break;
    case op_float:
      fprintf(ofp, " %d", refs_float);
      break;
    case op_dscl:
      fprintf(ofp, " %13.7" FMT_E, dscl[index]);
      break;
    case op_desc:
      fprintf(ofp, "%% %2d: param[%2d] Value: %s\n", output_col, index, name);
      break;
    case op_desc_float:
      fprintf(ofp, "%% %2d: param[%2d] Floating: %s\n", output_col, index, name);
      break;
    case op_desc_dscl:
      fprintf(ofp, "%% %2d: param[%2d] Scale: %s\n", output_col, index, name);
      break;
    default:
      nl_error(3, "func_parameter::output_params(): op_type %d unsupported", which);
  }
  ++output_col;
}

void func_parameter::input_params(char *&bp, op_type which) {
  char *eos;
  switch (which) {
    case op_value:
      p_can[index] = strtod(bp, &eos);
      break;
    case op_float:
      refs_float = strtoul(bp, &eos, 10);
      nl_assert(index == params[0].index);
      if (refs_float) {
        is_floating[index] = true;
        params.back().dyda = 1.0;
      } else {
        is_floating[index] = false;
        params.back().dyda = 0;
        ub[index] = lb[index] = p_can[index];
      }
      break;
    case op_dscl:
      dscl[index] = strtod(bp, &eos);
      break;
    case op_desc:
    case op_desc_float:
    case op_desc_dscl:
    default:
      nl_error(3, "op_type %d unsupported in input_params()", which);
  }
  bp = eos;
  if (!isspace(*bp))
    nl_error(3, "Restart: Error reading type %d for param[%d] %s", which, index, name);
}

func_parameter_p Nparameter(const char *group) {
  char pname[40];
  snprintf(pname, 40, "N[%s]", group);
  return new func_parameter(nl_strdup(pname), 0);
}

unsigned func_parameter::n_parameters = 0;
ICOS_Float *func_parameter::p_can;
ICOS_Float *func_parameter::ub;
ICOS_Float *func_parameter::lb;
bool *func_parameter::is_floating;
ICOS_Float *func_parameter::dscl;
bool func_parameter::checking_jacobian = false;
