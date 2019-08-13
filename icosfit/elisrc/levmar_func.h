#ifndef LEVMAR_FUNC_H_INCLUDED
#define LEVMAR_FUNC_H_INCLUDED

#include "funceval.h"

void levmar_func(ICOS_Float *p, ICOS_Float *hx, int m, int n, void *adata);

/**
 * @param p The parameter vector of length m
 * @param m The number of parameters in p
 * @param n The number of points in the scan we are fitting
 * @param j The jacobian matrix of dimensions n x m
 *
 * If there are m parameters in the p array and n measurements in the x array,
 * the jacobian is a two-dimensional array J[n][m] with
 *    J[i][j] = dxi/dpj
 * If accessed linearly, J[i][j] = J[i*m+j] where 0<=i< n and 0 <= j < m,
 * Hence, if we adopt the standard nomenclature that J[n][m] has n rows and m columns:
 *  - the rows map to measurement indices (npts)
 *  - the columns map to parameter indices (mp)
 *  - values are stored in memory by row, i.e. all of J[0][*] preceeds all of J[1][*], etc.
 */
void levmar_jacf(ICOS_Float *p, ICOS_Float *j, int m, int n, void *adata);

class fitdata;

typedef struct {
  fitdata *fit;
  func_evaluator *func;
  ICOS_Float *x;
} levmar_adata_t;

#endif
