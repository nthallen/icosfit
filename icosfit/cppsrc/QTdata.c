#include <math.h>
#include "ICOSfit.h"
#include "global.h"
#include "nl_assert.h"

QTdata::QTdata(int isotopologue) {
  char filename[FILENAME_MAX];
  char buf[QTBUFSIZE];
  FILE *fp;
  double QTref = 0.;
  
  isotop = isotopologue;
  dT = 0;
  Tmin = 0;
  Tmax = 0;
  snprintf(filename, FILENAME_MAX, "%s/QT_%d.dat",
    GlobalData.QTdir, isotopologue);
  fp = fopen(filename, "r");
  if (fp == NULL) {
    int T;
    nl_error(1, "Unable to open QT source '%s': using default", filename);
    Tmin = 160;
    Tmax = 320;
    dT = 2;
    QT.reserve(1+(Tmax-Tmin)/dT);
    for (T = Tmin; T <= Tmax; T += dT) {
      double ratio = pow(((double)Tref)/T, 1.5);
      QT.push_back(ratio);
    }
    return;
  } else {
    while (fgets(buf, QTBUFSIZE, fp)) {
      int n, T;
      double Q;
      n = sscanf(buf, "%d%lf", &T, &Q);
      switch (n) {
        case 0: break;
        case 2:
          if (dT) {
            if (T - Tmax != dT)
              nl_error(3, "%s: dT is not constant: was %d, but %d at %d",
                filename, dT, T-Tmax, T);
          } else if (Tmax) {
            dT = T - Tmax;
            if (dT <= 0)
              nl_error(3, "%s: dT (%d) <= 0", filename, dT);
          } else {
            Tmin = T;
          }
          QT.push_back(Q);
          if (T == Tref) QTref = Q;
          Tmax = T;
          break;
        case -1: /* printf("Blank\n"); */ break;
        default: nl_error(3, "Unexpected return: %d", n);
      }
    }
    fclose(fp);
  }
  if (dT) {
    unsigned i;
    for (i = 0; i < QT.size(); ++i) {
      QT[i] = QTref/QT[i];
    }
  } else {
    int T;
    nl_error(1, "Using default QT values for isotopologue %d", isotop);
    Tmin = 160;
    Tmax = 320;
    dT = 2;
    QT.clear();
    QT.reserve(1+(Tmax-Tmin)/dT);
    for (T = Tmin; T <= Tmax; T += dT) {
      double ratio = pow(((double)Tref)/T, 1.5);
      QT.push_back(ratio);
    }
  }
}

QTdata::~QTdata() {}

double QTdata::evaluate(double T) {
  unsigned i;
  double delta;
  if (T < Tmin || T > Tmax) {
    nl_error(2, "T (%lf) out of range for isotopologue %d", T, isotop);
    return pow(Tref/T, 1.5);
  }
  i = floor((T-Tmin)/dT);
  delta = (T-(Tmin+i*dT))/dT;
  nl_assert(delta >= 0 && delta <= 1 && i+1 < QT.size());
  return delta * QT[i+1] + (1 - delta) * QT[i];
}
