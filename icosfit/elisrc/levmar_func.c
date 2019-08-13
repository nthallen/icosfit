#include "ICOSfit.h"

void levmar_func(ICOS_Float *p, ICOS_Float *hx, int m, int n, void *adata) {
  levmar_adata_t *lm_adata = (levmar_adata_t *)adata;
  
  func_evaluator::global_evaluation_order.pre_eval(lm_adata->x[0], p);
  for (int xi = 0; xi < n; ++xi) {
    func_evaluator::global_evaluation_order.evaluate(lm_adata->x[xi], p);
    hx[xi] = lm_adata->func->value;
  }
}

void levmar_jacf(ICOS_Float *p, ICOS_Float *j, int m, int n, void *adata) {
  levmar_adata_t *lm_adata = (levmar_adata_t *)adata;
  fitdata *fit = lm_adata->fit;
  func_evaluator::global_evaluation_order.pre_eval(lm_adata->x[0], p);
  int Li = 0;
  for (int xi = 0; xi < n; ++xi) {
    func_evaluator::global_evaluation_order.evaluate_partials(lm_adata->x[xi], p);
    for (int pj = 0; pj < m; ++pj) {
      // j[xi][pj] = j[xi*m+pj] = dx[xi]/dp[pj]
      j[Li++] = lm_adata->func->params[pj].dyda;
    }
  }
  if (!func_parameter::checking_jacobian)
    fit->vwrite(p, j);
}
