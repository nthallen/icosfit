#ifndef PTREAD_H_INCLUDED
#define PTREAD_H_INCLUDED
#include <stdio.h>
#include "mlf.h"
#include "f_vector.h"

class PTfile {
  public:
    FILE *fp;
    double time;
    double P, T;
    double cal_flow, inlet_flow;
    unsigned long ScanNum;
    int RORIS, RateS;
    unsigned long next_ScanNum;

    int readline();
    void backup();
    void calc_wndata();
    PTfile( const char *fname );
  private:
    int format;
    int n_vars;
    const char *fname;
    int linenum;
    long int last_file_pos;
    double Etln_params[14];
};

class ICOSfile {
  public:
    ICOSfile(const char *fbase, const char *obase, int bin );
    int read(unsigned long int fileno);
    FILE *writefp();
    int wn_sample( ICOS_Float wn );

    mlf_def_t *mlf;
    mlf_def_t *omlf;
    FILE *ofp;
    /** Scan data vector */
    f_vector *sdata;
    /* Apparently unused */
    // f_vector *fdata;
    /** Baseline input data from column 3 of scan file, indicated
        by '+ Input' in BaselineFile definition. */
    static f_vector *bdata;
    /** Lookup table mapping sample number to wavenumber based on
     * etln_fit parameterization from the PTEfile */
    static f_vector *wndata;
    static ICOS_Float nu_F0;
    static int dFN;
    int binary;
    static const int mindatasize;
};

#endif
