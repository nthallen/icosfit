#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "funceval.h"
#include "ptread.h"
#include "global.h"
#include "nl.h"

func_beta::func_beta(func_abs *abs)
    : func_evaluator("beta") {
  append_func(abs);
}

void func_beta::evaluate(ICOS_Float x, ICOS_Float *a) {
  value = exp(-args[0].arg->value);
  args[0].dyda = -value;
  if ( isnan(value) ) {
    nl_error(2,"Absorb(%.0lf) is NaN", x);
  }
}

func_gamma::func_gamma(func_beta *beta)
    : func_evaluator("gamma") {
  ICOS_Float R = 1 - GlobalData.MirrorLoss;
  R2 = R*R;
  append_func(beta);
}

void func_gamma::evaluate(ICOS_Float x, ICOS_Float *a) {
  ICOS_Float beta = args[0].arg->value;
  value = R2 * beta * beta;
  args[0].dyda = 2 * R2 * beta;
}

func_epsilon::func_epsilon(func_gamma *gamma)
    : func_evaluator("epsilon") {
  append_func(gamma);
  const ICOS_Float c = 2.99792458e10; // cm/s
  N = c/(2*GlobalData.CavityLength*GlobalData.SampleRate);
}

void func_epsilon::evaluate(ICOS_Float x, ICOS_Float *a) {
  ICOS_Float gNm1 = pow(args[0].arg->value, N-1);
  value = gNm1 * args[0].arg->value;
  args[0].dyda = N*gNm1;
}

func_delta::func_delta(func_epsilon *epsilon, func_gamma *gamma)
    : func_evaluator("delta") {
  append_func(epsilon);
  append_func(gamma);
}

void func_delta::evaluate(ICOS_Float x, ICOS_Float *a) {
  ICOS_Float gm1 = 1/(args[1].arg->value - 1);
  value = (args[0].arg->value - 1)*gm1;
  args[0].dyda = gm1;
  args[1].dyda = -value * gm1;
}

func_g::func_g(func_base *base, func_beta *beta, func_delta *delta)
    : func_evaluator("g0") {
  append_func(base);
  append_func(beta);
  append_func(delta);
} 
     
void func_g::evaluate(ICOS_Float x, ICOS_Float *a) {
  ICOS_Float P = args[0].arg->value;
  ICOS_Float beta = args[1].arg->value;
  ICOS_Float delta = args[2].arg->value;
  if ( isnan(P) ) {
    nl_error(2,"Base(%.0lf) is NaN", x);
  }
  value = P*beta*delta;
  args[0].dyda = beta*delta;
  args[1].dyda = P*delta;
  args[2].dyda = P*beta;
}

//-----------------------------------------------
// To recast func_skew to accept a base function
// that depends on nu_F0, we should not derive
// from func_aggregate, since that 
// assumes all params are independent.
//-----------------------------------------------

skew_data::skew_data() {
  dg = deps = 0;
  g = eps = 0.;
  Power = 0.;
  initialized = 0;
  n = 0;
}

void skew_data::set_n_params(int n_gp, int n_epsp ) {
  dg = new ICOS_Float[n_gp];
  deps = new ICOS_Float[n_epsp];
}

func_skew::func_skew( func_g *g, func_epsilon *eps ) :
    func_evaluator("skew") {
  append_func(g);
  append_func(eps);
  basep = g->args[0].arg;
  depsi = 0;
  
  const ICOS_Float c = 2.99792458e10; // cm/s
  N = c/(2*GlobalData.CavityLength*GlobalData.SampleRate);
  ICOS_Float R = 1 - GlobalData.MirrorLoss;
  R2 = R*R;
  R2N = pow(R2,N);
  P_scale = (1-R2N)/(1-R2);
  M = (int) ceil(log(GlobalData.SkewTolerance)/(2*N*log(R)));
  skew = new skew_data[M];
  skew_eval_order.set_children(this);
  pre_evaluation_order.add(this);
}

void func_skew::init(ICOS_Float *a) {
  func_evaluator::init(a);
  func_evaluator *g = args[0].arg;
  assert(params.size() == g->params.size());
  for (int i = 0; i < M; i++ )
    skew[i].set_n_params(params.size(), args[1].arg->params.size());
  depsi = new int[params.size()];
  // Assumption is that func_skew and func_g have identical parameters
  // Verify this:
  for (unsigned int pi = 0; pi < params.size(); ++pi) {
    assert(params[pi].index == g->params[pi].index);
    depsi[pi] = -1;
    std::vector<paramref>::iterator ref;
    for (ref = params[pi].refs.begin(); ref != params[pi].refs.end(); ++ref) {
      if (ref->arg_num == 1) {
        assert(params[pi].index == args[1].arg->params[ref->param_num].index);
        depsi[pi] = ref->param_num;
      }
    }
  }
}

int func_skew::skew_samples() {
  int rv = func_evaluator::skew_samples();
  if ( M > rv ) rv = M;
  return rv;
}

void func_skew::pre_eval(ICOS_Float x, ICOS_Float *a) {
  if (GlobalData.PTE_MirrorLoss_col) {
    ICOS_Float R = 1 - GlobalData.input.MirrorLoss;
    R2 = R*R;
    R2N = pow(R2,N);
    P_scale = (1-R2N)/(1-R2);
  }
  for ( int i = 0; i < M; i++ )
    skew[i].initialized = 0;
  skewidx = 0;
  for (ICOS_Float xi = x - M + 1.; xi < x; ++xi) {
    skew_eval_order.evaluate(xi, a);
    sub_eval(xi, a);
  }
}

/**
 * Reinitializes skew[skewidx] with n=0 and iterates
 * all the other elements that have been initialized
 */
void func_skew::sub_eval(ICOS_Float x, ICOS_Float *a) {
  int i;
  func_evaluator *g = args[0].arg;
  func_evaluator *eps = args[1].arg;
  for (i = 0; i < M; ++i) {
    skew_data *curskew = &skew[i];
    ICOS_Float *dg = curskew->dg;
    ICOS_Float *deps = curskew->deps;
    if (i == skewidx) {
      curskew->n = 0;
      curskew->g = g->value;
      curskew->Power = basep->value;
      for (unsigned j = 0; j < g->params.size(); ++j) {
        dg[j] = g->params[j].dyda;
      }
      curskew->eps = eps->value;
      for (unsigned j = 0; j < eps->params.size(); ++j) {
        deps[j] = eps->params[j].dyda;
      }
      curskew->initialized = 1;
    } else if (skew[i].initialized) {
      ++curskew->n;
      // func_skew and func_g have identical parameters
      for (unsigned int pi = 0; pi < params.size(); ++pi) {
        dg[pi] *= curskew->eps;
        int epspi = depsi[pi];
        if (epspi >= 0) {
          dg[pi] += curskew->g * deps[epspi];
        }
      }
      curskew->g *= curskew->eps;
      curskew->Power *= R2N;
    }
  }
  if (++skewidx == M)
    skewidx = 0;
}

/**
 * Prior to version 3.0, we depended
 * on the fact that the functions are evaluated
 * for monotonically increasing values of x. We know we are
 * starting over if x decreases. We also know that x is
 * essentially integral.
 *
 * With 3.0, we use the pre_evaluation_order, which is called
 * at the beginning of each evaluation sequence.
 *
 * Note: The calculation of 'Power' is not part of the fit
 * per se. It is performed only to generate the effective
 * skewed baseline for diagnostic output. The baseline
 * function determines the input power, but for useful
 * comparison with the raw data, we need to estimate the
 * output power in the absence of absorption.
 */
void func_skew::evaluate(ICOS_Float x, ICOS_Float *a) {
  sub_eval(x, a);
  value = 0;
  ICOS_Float Pwr = 0;
  for (int i = 0; i < M; i++) {
    skew_data *cs = &skew[i];
    assert(cs->initialized);
    value += cs->g;
    Pwr += cs->Power;
  }
  basep->value = Pwr * P_scale; // For diagnostic output
}

void func_skew::evaluate_partials() {
  std::vector<parameter>::iterator p;
  for (p = params.begin(); p != params.end(); ++p) {
    p->dyda = 0;
  }
  for (int i = 0; i < M; i++) {
    skew_data *cs = &skew[i];
    for (unsigned int pi = 0; pi < params.size(); ++pi) {
      params[pi].dyda += cs->dg[pi];
    }
  }
}

void func_skew::output_params(FILE *ofp, op_type which, int &output_col) {
  basep->output_params(ofp, which, output_col);
  GlobalData.absorb->output_params(ofp, which, output_col);
}

void func_skew::input_params(char *&bp, op_type which) {
  basep->input_params(bp, which);
  GlobalData.absorb->input_params(bp, which);
}
