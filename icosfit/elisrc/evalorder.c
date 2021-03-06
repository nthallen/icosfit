#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <set>
#include "funceval.h"
#include "nl.h"

evaluation_order func_evaluator::global_evaluation_order;
evaluation_order func_evaluator::pre_evaluation_order;
evaluation_order func_evaluator::dump_evaluation_order;

void evaluation_order::set(func_evaluator*func, bool top, bool clear) {
  if (top) {
    set(func, false, true);
  }
  std::vector<argref>::iterator arg;
  for (arg = func->args.begin(); arg != func->args.end(); ++arg) {
    set(arg->arg, false, clear);
  }
  if (clear) {
    func->added_to_eval = false;
  } else if (!func->added_to_eval) {
    add(func);
    func->added_to_eval = true;
  }
}

void evaluation_order::set_pre_order(func_evaluator*func, bool top, bool clear) {
  if (top) {
    set(func, false, true);
  }
  if (clear) {
    func->added_to_eval = false;
  } else if (!func->added_to_eval) {
    add(func);
    func->added_to_eval = true;
  }
  std::vector<argref>::iterator arg;
  for (arg = func->args.begin(); arg != func->args.end(); ++arg) {
    set_pre_order(arg->arg, false, clear);
  }
}

void evaluation_order::set_children(func_evaluator*func) {
  set(func, false, true);
  func->added_to_eval = true;
  set(func, false, false);
}

void evaluation_order::add(func_evaluator*func) {
  order.push_back(func);
}

void evaluation_order::evaluate(ICOS_Float x, ICOS_Float *a) {
  std::vector<func_evaluator*>::iterator func;
  for (func = order.begin(); func != order.end(); ++func) {
    (*func)->evaluate(x, a);
  }
}

void evaluation_order::evaluate_partials(ICOS_Float x, ICOS_Float *a) {
  std::vector<func_evaluator*>::iterator func;
  for (func = order.begin(); func != order.end(); ++func) {
    (*func)->evaluate(x, a);
    (*func)->evaluate_partials();
  }
}

void evaluation_order::pre_eval(ICOS_Float x, ICOS_Float *a) {
  std::vector<func_evaluator*>::iterator func;
  for (func = order.begin(); func != order.end(); ++func) {
    (*func)->pre_eval(x, a);
  }
}

void evaluation_order::init(ICOS_Float *a) {
  std::vector<func_evaluator*>::iterator func;
  for (func = order.begin(); func != order.end(); ++func) {
    (*func)->init(a);
  }
}

int evaluation_order::adjust_params(adjust_event when, ICOS_Float P,
      ICOS_Float T) {
  int rv1 = 0; // Return of 1 means rollback
  int rv2 = 0; // Return of 2 means repeat, but don't rollback
  std::vector<func_evaluator*>::iterator func;
  for (func = order.begin(); func != order.end(); ++func) {
    int rv;
    switch (rv = (*func)->adjust_params(when, P, T)) {
      case 0: break;
      case 1: rv1 = 1; break;
      case 2: rv2 = 1; break;
      default: nl_error(3, "Invalid return %d from %s::adjust_params()", rv, (*func)->name);
    }
  }
  return rv1 ? 1 : (rv2 ? 2 : 0);
}

void evaluation_order::dump() {
  fprintf(stderr, "Evaluation State:\n");
  std::vector<func_evaluator*>::iterator func;
  for (func = order.begin(); func != order.end(); ++func) {
    (*func)->dump_params();
    (*func)->dump_partials();
  }
}
