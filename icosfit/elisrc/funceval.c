#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <set>
#include "nl.h"
#include "funceval.h"
#include "global.h"
#include "ptread.h"

func_evaluator::func_evaluator(const char *sname, bool indexed, int idx) {
  if (indexed) {
    char buf[80];
    snprintf(buf, 80, "%s[%d]", sname, idx);
    name = nl_strdup(buf);
  } else {
    name = sname;
  }
  parent = 0;
  value = 0.;
  n_references = 0;
  added_to_eval = false;
}

/**
 * @param newfunc The new argument, appended to args vector.
 * @param owner if true, newfunc's parent is set
 */
void func_evaluator::append_func( func_evaluator *newfunc) {
  args.push_back(argref(newfunc, newfunc->adopted(this)));
}

/**
 * @param new_parent The called object is now a child of the new_parent object
 * By overloading this function, children can gain access to needed
 * information from the parents. Specifically, line types can access the
 * parent func_abs's nu_F0 parameter.
 */
unsigned int func_evaluator::adopted(func_evaluator *new_parent) {
  if (parent == 0) {
    parent = new_parent;
  }
  return n_references++;
}

void func_evaluator::init( ICOS_Float *p, ICOS_Float* lb, ICOS_Float *ub,
                                bool *is_floating, ICOS_Float *dscl) {
  // printf( "func_evaluator::init(%s, p, ub, lb);\n", name );
  func_parameter::set(p, lb, ub, is_floating, dscl);
  global_evaluation_order.init(p);
}

void func_evaluator::init(ICOS_Float *p) {
  std::vector<argref>::iterator child;
  std::set<int> pidx;
  
  for (child = args.begin(); child != args.end(); ++child) {
    std::vector<parameter>::iterator cp;
    for (cp = child->arg->params.begin(); cp < child->arg->params.end(); ++cp) {
      pidx.insert(cp->index);
    }
  }
  // Now we know exactly how many and which parameters we depend on
  std::set<int>::iterator ipidx;
  for (ipidx = pidx.begin(); ipidx != pidx.end(); ++ipidx) {
    params.push_back(parameter(*ipidx));
  }
  // Now go back through the children and record where the
  // child references appear
  unsigned int argi, argpi, pi;
  for (argi = 0; argi < args.size(); ++argi) {
    for (argpi = 0; argpi < args[argi].arg->params.size(); ++argpi) {
      for (pi = 0; pi < params.size(); ++pi) {
        if (params[pi].index == args[argi].arg->params[argpi].index) {
          params[pi].name = args[argi].arg->params[argpi].name;
          params[pi].refs.push_back(paramref(argi, argpi));
          break;
        }
      }
    }
  }
}

/**
 * @param float true to float, false to fix parameter.
 * This call is currently illegal unless object is a
 * func_parameter.
 */
void func_evaluator::fix_float_param(bool float_it, unsigned int refnum) {
  nl_error(3, "Illegal attempt to %s a non-parameter",
      float_it ? "float" : "fix");
}

/**
 * @return true if the parameter is fixed.
 * This call is currently illegal unless object is a
 * func_parameter.
 */
bool func_evaluator::param_fixed() {
  nl_error(3, "Illegal attempt to query fixed state of a non-parameter");
  return false;
}

ICOS_Float func_evaluator::set_param(ICOS_Float value) {
  nl_error(3, "Illegal attempt to set value of a non-parameter");
  return 0.;
}

void func_evaluator::set_param_limits(ICOS_Float lb, ICOS_Float ub) {
  nl_error(3, "Illegal attempt to set limits of a non-parameter");
}

void func_evaluator::set_param_scale(ICOS_Float scl) {
  nl_error(3, "Illegal attempt to set scale of a non-parameter");
}

void func_evaluator::pre_eval(ICOS_Float x, ICOS_Float *p) {}

void func_evaluator::evaluate(ICOS_Float x, ICOS_Float *p) {}

void func_evaluator::evaluate_partials() {
  std::vector<parameter>::iterator p;
  for (p = params.begin(); p != params.end(); ++p) {
    parameter pc = *p;
    p->dyda = 0;
    std::vector<paramref>::iterator ref;
    for (ref = p->refs.begin(); ref != p->refs.end(); ++ref) {
      paramref refc = *ref;
      argref argc = args[ref->arg_num];
      parameter paramc = argc.arg->params[refc.param_num];
      p->dyda += 
        args[ref->arg_num].dyda *
        args[ref->arg_num].arg->params[ref->param_num].dyda;
      // refc.arg_num = refc.arg_num;
      // argc.refnum = argc.refnum;
    }
  }
}

/**
 * With version 3, adjust_params() no longer recurses, since
 * the execution order is determined during init().
 * Sub classes will override this method and are tasked
 * with calculating value and the partial derivative with
 * respect to each of their arguments (args).
 * @return non-zero if a parameter value has been changed.
 */
int func_evaluator::adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T) {
  return 0;
}

void func_evaluator::output_params(FILE *ofp, op_type which, int &output_col) {
  std::vector<argref>::iterator child;
  for (child = args.begin(); child != args.end(); ++child) {
    child->arg->output_params(ofp, which, output_col);
  }
}

void func_evaluator::output_params(FILE *ofp, op_type which) {
  int output_col = 0;
  output_params(ofp, which, output_col);
}

void func_evaluator::input_params(char *&bp, op_type which) {
  std::vector<argref>::iterator child;
  for (child = args.begin(); child != args.end(); ++child) {
    child->arg->input_params(bp, which);
  }
}


/**
 * @return zero for non-line classes
 */
func_line *func_evaluator::is_line() { return 0; }

int func_evaluator::line_check(int include, ICOS_Float& start, ICOS_Float& end,
                ICOS_Float P, ICOS_Float T) {

  std::vector<argref>::iterator arg;
  for (arg = args.begin(); arg != args.end(); ++arg) {
    if (arg->arg->line_check(include, start, end, P, T))
      return 1;
  }
  return 0;
}

int func_evaluator::skew_samples() {
  int rv = 0;
  int frv;
  std::vector<argref>::iterator arg;
  for (arg = args.begin(); arg != args.end(); ++arg) {
    frv = arg->arg->skew_samples();
    if ( frv > rv ) rv = frv;
  }
  return rv;
}

/**
  dump_params() is a diagnostic tool that is invoked
  at times of failure. The default version simply lists
  all the parameters and their values without recursing
  to children, but overrides can delegate to children.
 */
void func_evaluator::dump_params() {
  // print_indent( stderr, indent );
  const char *comma = "";
  int len = fprintf( stderr, "  %s(", name );
  std::vector<argref>::iterator arg;
  for (arg = args.begin(); arg != args.end(); ++arg) {
    if (len+strlen(arg->arg->name) > 50) {
      fprintf(stderr, "%s\n      ", comma);
      len = 6;
      comma = "";
    }
    len += fprintf(stderr, "%s%s", comma, arg->arg->name);
    comma = ",";
  }
  fprintf(stderr, ") = %" FMT_G "\n", value);
  for (arg = args.begin(); arg != args.end(); ++arg) {
    fprintf(stderr, "    d(%s)/d(%s) = %" FMT_G "\n",
      name, arg->arg->name, arg->dyda);
    comma = ",";
  }
}

void func_evaluator::dump_partials() {
  fprintf(stderr, "    Partials with respect to parameters for %s():\n", name);
  std::vector<parameter>::iterator param;
  for (param = params.begin(); param != params.end(); ++param) {
    fprintf(stderr, "      /d[%d] (%s) = %" FMT_G "\n", param->index,
      param->name, param->dyda);
  }
}

void func_evaluator::print_indent( FILE *fp, int indent ) {
  while (indent-- > 0) fputc(' ', fp );
}

void func_evaluator::print_config(FILE *fp) {}
void func_evaluator::print_intermediates(FILE *fp) {}


//---------------------------------------------------------
// func_abs: in funcabs.cc
//---------------------------------------------------------


//---------------------------------------------------------
// gaussian
//---------------------------------------------------------
// Evaluation of this will get out of hand if
// w becomes small, or more specifically if
// w^2 becomes small
// This form of the gaussian is normalized in
// various ways presumably to match the lorentzian.
// ### This needs to be fixed for cm-1 scale
void gaussian::evaluate(ICOS_Float x, ICOS_Float *p) {
  static const ICOS_Float four_log_2 = 4 * log(2.);
  static const ICOS_Float fl2_pi = sqrt(four_log_2/M_PI);
  ICOS_Float dnu = p[params[dnu_idx].index] +
    p[params[nu_F0_idx].index];
  ICOS_Float w = p[params[w_idx].index];
  ICOS_Float s = p[params[n_idx].index];
  assert( s >= 0. );
  ICOS_Float w2 = w * w;
  ICOS_Float v1 = fl2_pi * s / w;
  int xx = int(x);
  ICOS_Float diff = ICOSfile::wndata->data[xx] - nu_P + dnu;
  ICOS_Float diff2 = diff * diff;
  ICOS_Float v2 = exp( - diff2 * four_log_2 / w2 );
  value = v1 * v2;
  args[n_idx].dyda = fl2_pi * v2 / w;
  args[dnu_idx].dyda = args[nu_F0_idx].dyda =
    2*v1*v2*diff*four_log_2/w2;
  ICOS_Float v3 = fl2_pi * s * v2 / w2;
  args[w_idx].dyda = -(v3/w) + v3 * 2 * diff2 * four_log_2 / w2;
}

//---------------------------------------------------------
// lorentzian
//---------------------------------------------------------
// ### This needs to be fixed for wavenumber scale
void lorentzian::evaluate(ICOS_Float x, ICOS_Float *p) {
  ICOS_Float dnu = p[params[dnu_idx].index] +
    p[params[nu_F0_idx].index];
  ICOS_Float w = p[params[w_idx].index];
  ICOS_Float s = p[params[n_idx].index];
  int xx = int(x);
  ICOS_Float diff = ICOSfile::wndata->data[xx] - nu_P + dnu;
  ICOS_Float v1 = M_PI * ( 4 * diff *diff + w * w );
  ICOS_Float v12 = v1 * v1;
  value = 2 * w * s / v1;
  args[n_idx].dyda = 2 * w / v1;
  args[dnu_idx].dyda = args[nu_F0_idx].dyda =
    16*M_PI*w*s*diff / v12;
  args[w_idx].dyda = (2*s*v1 - 4*M_PI*s*w*w)/v12;
}

//----------------------------------------------------------
// voigt: in humdev.cc
//----------------------------------------------------------
