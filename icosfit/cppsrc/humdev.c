// humdev.cc hand-converted from humdev.for
// Written by R.J. Wells
// Published in
// Rapid Approximation to the Voigt/Faddeeva Function and its Derivatives
// JQSRT 62 1999 29-48
//
// Modified to operate with a single X argument but to
// hold onto values calculated from Y, thereby retaining the
// optimization.
#include <math.h>
#include <setjmp.h>
#include "config.h"
#include <stdlib.h>
#include "funceval.h"
#include "ptread.h"
#include "nl.h"
#include "global.h"

extern jmp_buf Fit_buf;
#define DBLE(x) ((double)x)
#define SNGL(x) ((ICOS_Float)x)

const int voigt::gl_idx = 3;

voigt::voigt( int mol, int iso,
          double nu_in, double S_in, double G_air_in, double E_in,
          double n_in, double delta_in, int ipos_in, double threshold,
          int fix_dw, int fix_lw, int fix_fp, func_parameter *N )
    : func_line( "voigt", mol, iso, nu_in, S_in, G_air_in, E_in,
                   n_in, delta_in, ipos_in, threshold, fix_dw,
                   fix_fp, N) {
  append_func(new func_parameter("Gl", 0., true, line_number));
  prev_gl = 0.;
  prev_y = 0.;
  fix_lwidth = fix_lw;
}

/**
 * This formulation for the empirical fit to line width is from
 * Liz's old lecture notes (Webster?) and is attributed to
 * Olivero and Longbothum.
 */
ICOS_Float voigt::line_width() {
  ICOS_Float ged = get_arg(w_idx);
  ICOS_Float gl = get_arg(gl_idx);
  ICOS_Float wid = .5346*gl + sqrt(.2166*gl*gl + .69315*ged*ged);
  return wid;
}

void voigt::init(ICOS_Float*p) {
  if (fixed || fix_lwidth) fix_param(gl_idx);
  func_line::init(p);
}

ICOS_Float voigt::line_start() {
  return (nu_P - GlobalData.RightLineMarginMultiplier*line_width());
}
ICOS_Float voigt::line_end() {
  return (nu_P + GlobalData.LeftLineMarginMultiplier*line_width());
}

void voigt::evaluate( ICOS_Float xx, ICOS_Float *p) {
  ICOS_Float numdens = get_arg(n_idx);
  ICOS_Float gamma_ed = get_arg(w_idx);
  ICOS_Float gamma_l = get_arg(gl_idx);
  ICOS_Float dnu = get_arg(dnu_idx)+get_arg(nu_F0_idx);
  int ixx = int(xx);

  // X, Y and K now private object members
  X = (ICOSfile::wndata->data[ixx] - nu_P + dnu)/gamma_ed;
  Y = gamma_l/gamma_ed;
  // K Voigt output (Real part)
  ICOS_Float L; // Imaginery Part (needed for derivatives)
  ICOS_Float DKDX; // dVoigt/dX
  ICOS_Float DKDY; // dVoigt/dY

// Constants
  static const ICOS_Float  RRTPI = 0.56418958;
  static const ICOS_Float Y0 = 1.5; // for CPF12 algorithm
  static const ICOS_Float Y0PY0 = Y0+Y0;
  static const ICOS_Float Y0Q = Y0*Y0;
  static const ICOS_Float C[6] = {
         1.0117281,    -0.75197147, 0.012557727,
       0.010022008, -0.00024206814, 0.00000050084806 };
  static const ICOS_Float S[6] = {
           1.393237,       0.23115241,  -0.15535147,
       0.0062183662,   0.000091908299,  -0.00000062752596 };
  static const ICOS_Float T[6] = {
       0.31424038,  0.94778839, 1.5976826,
       2.2795071,   3.0206370,  3.8897249 };

// Local variables
  int J;                                      // Loop variables
  ICOS_Float ABX, XQ;                      // |x|, x^2
  ICOS_Float MT[6], MQ[6], PT[6], PQ[6];              // Temporary variables
  ICOS_Float XP[6], XM[6], YP[6], YM[6], MF[6], PF[6];
  ICOS_Float YP2Y0, YPY0, YPY0Q, YF1, YF2, MFQ, PFQ, D,  U, DUDY, DVDY;
  double DB;

//**** Start of executable code ****************************************

  if ( Y != prev_y ) {;
    RGB = 1;
    RGC = 1;
    RGD = 1;
    YQ  = Y*Y;                 // y^2
    XLIMA = 146.7 - Y;         // Region A boundary
    XLIMB = 24.0 - Y;          // Region B boundary
    XLIMC = 7.4 - Y;           // Region C boundary
    XLIM4 = 18.1*Y + 1.65;     // CPF12 I-II boundary
    prev_y = Y;
  };
//.....
  ABX = fabs( X );    // |x|
  XQ  = ABX*ABX;    // x^2
  if ( ABX > XLIMA ) {    // Region A
    D       = 1.0 / (XQ + YQ);
    D1      = D*RRTPI;
    K    = D1*Y;
    L    = D1*X;
    D1      = D1*D;
    DKDX = -D1*(Y+Y)*X;
    DKDY = D1*(XQ-YQ);
  } else if ( ABX > XLIMB ) {    // Region B
    if ( RGB != 0 ) {    // First point in Region B
      RGB = 0;
      A0 = YQ + 0.5;    // Region A y-dependents
      B1 = YQ - 0.5;
      D0 = A0*A0;    // y^4 + y^2 + 0.25
      D2 = B1 + B1;    // 2y^2 - 1
      C0 = 1.5   + YQ*(1.0 - D2);    // 1.5 + 2y^2 - 2y^4
      C2 = A0 + A0;    // 2y^2 + 1
      R0 = 0.125 + YQ*(0.25 - YQ*(0.5 + YQ));
      R2 = 0.25  + YQ*(5.0  + YQ);
    }
    D       = 1.0 / (D0 + XQ*(D2 + XQ));
    D1      = RRTPI*D;
    K    = D1*(A0 + XQ)*Y;
    L    = D1*(B1 + XQ)*X;
    D1      = D1*D;
    DKDX = D1*X*Y*(C0 - (C2 + XQ)*(XQ+XQ));
    DKDY = D1*(R0 - XQ*(R2 - XQ*(B1 + XQ)));
  } else {    // Not Region A
   if ( ABX > XLIMC ) {    // Region C
    if ( RGC != 0 ) {    // First point in Region C
      RGC = 0;
      H0 =  0.5625 + YQ*( 4.5  + YQ*(10.5 + YQ*(6.0 + YQ)) );    // Region B y-dependents
      H2 = -4.5    + YQ*( 9.0  + YQ*( 6.0 + YQ* 4.0));
      H4 = 10.5    - YQ*( 6.0  - YQ*  6.0);
      H6 = -6.0    + YQ*  4.0;
      W0 =  1.875  + YQ*(24.25 + YQ*(27.5 + YQ* 7.0));
      W2 =  5.25   + YQ*( 3.0  + YQ* 15.0);
      W4 = -4.5    + YQ*  9.0;
      F1 = -1.875  + YQ*( 5.25 + YQ*( 4.5 + YQ));
      F3 =  8.25   - YQ*( 1.0  - YQ*  3.0);
      F5 = -5.5    + YQ*  3.0;
      E0 = Y*(1.875 + YQ*( 8.25 + YQ*( 5.5 + YQ)));
      E2 = Y*(5.25  + YQ*( 1.0  + YQ*  3.0));
      E4 = Y*0.75*H6;
      G0 = Y*(  9.0 + YQ*(42.0  + YQ*(36.0 + YQ* 8.0)));
      G2 = Y*( 18.0 + YQ*(24.0  + YQ* 24.0));
      G4 = Y*(-12.0 + YQ* 24.0);
      G6 = Y*   8.0;
    }
    U = E0 + XQ*(E2 + XQ*(E4 + XQ*Y));
    D = 1.0 / (H0 + XQ*(H2 + XQ*(H4 + XQ*(H6 + XQ))));
    K = RRTPI*D*U;
    L = RRTPI*D*X*(F1 + XQ*(F3 + XQ*(F5 + XQ)));
    DUDY = W0 + XQ*(W2 + XQ*(W4 + XQ));
    DVDY = G0 + XQ*(G2 + XQ*(G4 + XQ*G6));
    DKDY = RRTPI*D*(DUDY - D*U*DVDY);
   } else if ( ABX < 0.85 ) {    // Region C
    if ( RGD != 0 ) {    // First point in Region D
      RGD = 0;
      Z0 =     272.1014 + Y*(1280.829   + Y*(2802.870  + Y*(3764.966 // Region C y-dependents
          + Y*(3447.629 + Y*(2256.981   + Y*(1074.409
          + Y*(369.1989 + Y*(  88.26741 + Y*(  13.3988 + Y)))))))));
      Z2 =      211.678 + Y*( 902.3066  + Y*(1758.336  + Y*(2037.310
          + Y*(1549.675 + Y*( 793.4273  + Y*( 266.2987
                        + Y*(  53.59518 + Y*    5.0)))))));
      Z4 =     78.86585 + Y*( 308.1852  + Y*( 497.3014 + Y*(479.2576
          + Y*(269.2916 + Y*(  80.39278 + Y*   10.0)))));
      Z6 =     22.03523 + Y*(  55.02933 + Y*(  92.75679
                        + Y*(  53.59518 + Y*   10.0)));
      Z8 =     1.496460 + Y*(  13.39880 + Y*    5.0);
      P0 =     153.5168 + Y*( 549.3954  + Y*( 919.4955 + Y*(946.897
          + Y*(662.8097 + Y*( 328.2151  + Y*( 115.3772
          + Y*(27.93941 + Y*(   4.264678+ Y*    0.3183291))))))));
      P2 =    -34.16955 + Y*(  -1.322256+ Y*( 124.5975 + Y*(189.773
                        + Y*( 139.4665  + Y*(  56.81652
                        + Y*(  12.79458 + Y*    1.2733163))))));
      P4 =     2.584042 + Y*(  10.46332 + Y*(  24.01655
          + Y*(29.81482 + Y*(  12.79568 + Y*    1.9099744))));
      P6 =  -0.07272979 + Y*(   0.9377051
          + Y*(4.266322 + Y*    1.273316));
      P8 = 0.0005480304 + Y*    0.3183291;
      Q1 =     173.2355 + Y*( 508.2585  + Y*( 685.8378
          + Y*(557.5178 + Y*( 301.3208  + Y*( 111.0528
          + Y*( 27.6294 + Y*(   4.26413 + Y*    0.3183291)))))));
      Q3 =     18.97431 + Y*( 100.7375  + Y*( 160.4013 + Y*(130.8905
          + Y*(55.88650 + Y*(  12.79239 + Y*    1.273316)))));
      Q5 =     7.985877 + Y*(  19.83766 + Y*(  28.88480
                        + Y*(  12.79239 + Y*    1.909974)));
      Q7 =    0.6276985 + Y*(   4.26413 + Y*    1.273316);
    }
    U    = 1.7724538*(P0 + XQ*(P2 + XQ*(P4 + XQ*(P6 + XQ*P8))));
    D    = 1.0 / (Z0 + XQ*(Z2 + XQ*(Z4 + XQ*(Z6 + XQ*(Z8 + XQ)))));
    K = D*U;
    L = 1.7724538*D*X*
                  (Q1 + XQ*(Q3 + XQ*(Q5 + XQ*(Q7 + XQ*0.3183291))));
    DB = DBLE(X)*DBLE(L) + DBLE(Y)*DBLE(K) - DRTPI;    // Double precision
    DKDY = SNGL( DB + DB );    // Single precision
   } else {    // Use CPF12
    YPY0  = Y + Y0;
    YPY0Q = YPY0*YPY0;
    K = 0.0;
    L = 0.0;
    for ( J = 0; J <= 5; J++ ) {
      MT[J] = X - T[J];
      MQ[J] = MT[J]*MT[J];
      MF[J] = 1.0 / (MQ[J] + YPY0Q);
      XM[J] = MF[J]*MT[J];
      YM[J] = MF[J]*YPY0;
      PT[J] = X + T[J];
      PQ[J] = PT[J]*PT[J];
      PF[J] = 1.0 / (PQ[J] + YPY0Q);
      XP[J] = PF[J]*PT[J];
      YP[J] = PF[J]*YPY0;
      L = L + C[J]*(XM[J]+XP[J]) + S[J]*(YM[J]-YP[J]);
    }
    if ( ABX <= XLIM4 ) {    // Humlicek CPF12 Region I
      YF1 = YPY0 + YPY0;
      YF2 = YPY0Q + YPY0Q;
      DKDY = 0.0;
      for ( J = 0; J <= 5; J++ ) {
       MFQ = MF[J]*MF[J];
       PFQ = PF[J]*PF[J];
       K = K + C[J]*(YM[J]+YP[J]) - S[J]*(XM[J]-XP[J]);
       DKDY = DKDY
                + C[J]*( MF[J] + PF[J] - YF2*(MFQ + PFQ) )
                + S[J]*YF1*( MT[J]*MFQ - PT[J]*PFQ );
      }
    } else {    // Humlicek CPF12 Region II
     YP2Y0 = Y + Y0PY0;
     for ( J = 0; J <= 5; J++ ) {
      K = K
            + (C[J]*(MQ[J]*MF[J]-Y0*YM[J]) + S[J]*YP2Y0*XM[J])
              / (MQ[J]+Y0Q)
            + (C[J]*(PQ[J]*PF[J]-Y0*YP[J]) - S[J]*YP2Y0*XP[J])
              / (PQ[J]+Y0Q);
     }
     K = Y*K + exp( -XQ );
     DB = DBLE(X)*DBLE(L) + DBLE(Y)*DBLE(K) - DRTPI;    // Double precision
     DKDY = SNGL( DB + DB );
    }
   }
   DB = DBLE(Y)*DBLE(L) - DBLE(X)*DBLE(K);    // Double precision
   DKDX = SNGL( DB + DB );
  }    // Not region A
  
  ICOS_Float sed = Ks/gamma_ed;
  args[n_idx].dyda = sed * K;
  sed *= numdens; // Ks*N/Ged
  value = sed * K;
  sed /= gamma_ed; // Ks*N/Ged^2
  args[dnu_idx].dyda = args[nu_F0_idx].dyda = sed * DKDX;
  args[w_idx].dyda = -sed * ( K + X * DKDX + Y * DKDY );
  args[gl_idx].dyda = sed * DKDY;
}

/** adjust_params
 * @param when either before or after the fit
 * @param P Current pressure in Torr
 * @param T Current temperature in Kelvin
 * @param a Pointer to paramater values vector
 * @return non-zero if a change in which parameters are free is mandated.
 *
 * Might be possible to get into oscillation if line gets
 *  re-disabled, but that should be unlikely. If it does
 *  happen, it could be detected by keeping track. It is
 *  probably best to leave it disabled if it happens twice.
 *  The logic is: first time it is disabled because it is
 *  getting small. When the width is corrected, it then
 *  turns out to be large. It is then released (without
 *  rollback) but during the continuing fit, it gets
 *  small again. That is probably an error, so fix it
 *  once more (with rollback) which will presumably take
 *  us back to the larger value, but this time, don't
 *  complain at alamda==0 time.
 */
int voigt::adjust_params(adjust_event when, ICOS_Float P, ICOS_Float T) {
  int rv;
  if ( rv = func_line::adjust_params(when, P, T) )
    return rv;
  if (when == scan_init) {
    ICOS_Float Gl_calc = G_air * (P/760.) * pow( 296./T, n_air);
    set_param_scale(gl_idx, Gl_calc);
    if (param_fixed(gl_idx)) {
      // The following formula comes from the HITRAN appendix
      set_param(gl_idx, Gl_calc);
      set_param_limits(gl_idx, Gl_calc, Gl_calc);
    } else {
      set_param_limits(gl_idx, Gl_calc/Gl_range, Gl_calc*Gl_range);
    }
  }
  return 0;
}

void voigt::line_fix() {
  fix_param(gl_idx); // Limits must be set in adjust_params
  func_line::line_fix();
}

void voigt::line_float() {
  if ( fix_lwidth == 0 ) float_param(gl_idx);
  func_line::line_float();
}

void voigt::print_intermediates(FILE *fp) {
  fprintf(fp, " %12.6le %12.6le", X, K);
}

const double voigt::Gl_range = 1.3;