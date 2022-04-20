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
    unsigned long ScanNum, LastScan;
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
    int coadd(uint32_t firstscan, uint32_t lastscan);
    int read(unsigned long int fileno);
    FILE *writefp();
    int wn_sample( ICOS_Float wn );

    mlf_def_t *mlf;
    mlf_def_t *omlf;
    FILE *ofp;
    /** Scan data vector */
    f_vector *sdata;
    f_vector *ssdata; // for coadding sdata
    /** Baseline input data from column 3 of scan file, indicated
        by '+ Input' in BaselineFile definition. */
    static f_vector *bdata;
    f_vector *sbdata; // for coadding bdata
    /** Lookup table mapping sample number to wavenumber based on
     * etln_fit parameterization from the PTEfile */
    static f_vector *wndata;
    // f_vector *swndata; // we won't coadd wndata for now
    static ICOS_Float nu_F0;
    static int dFN;
    int binary;
    static const int mindatasize;
};

#endif
