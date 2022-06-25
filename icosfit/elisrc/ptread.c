#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include "nl_assert.h"
#include "ptread.h"
#include "nl.h"
#include "global.h"
#include "mlf.h"

/**
 * There can be 21 defined columns plus an arbitrary number of
 * 'Placeholder' columns. The standard output from MATLAB uses
 * 17 characters for each column, so we need space for at least
 * 21*17 + 2 = 359 chars to include the newline and NUL.
 * No reason not to push this out to 512.
 */
const int MYBUFSIZE = 512;
const int MAX_VARS = 25;

PTfile::PTfile( const char *fname )
    : fname(fname),
      linenum(0),
      ScanNum(0),
      LastScan(0),
      next_ScanNum(0) {
  fp = fopen( fname, "r" );
  if ( fp == 0 )
    nl_error( nl_response, "Unable to open input file '%s'", fname );
  format = GlobalData.PTformat;
  last_file_pos = -1;
  switch ( format ) {
    case 0: n_vars = 12; break; // Obsolete
    case 1: n_vars = 7; break; // Obsolete
    case 2: n_vars = 11; break; // PTE file
    default: nl_error( nl_response, "Unknown format code: %d", format );
  }
  if (GlobalData.PTE_Feedback_col) {
    ++n_vars;
  }
  if (GlobalData.PTE_nu_F0_col) {
    ++n_vars;
  }
  if (GlobalData.PTE_MirrorLoss_col) {
    ++n_vars;
  }
  if (GlobalData.PTE_PowerParams_col) {
    n_vars += 7;
  }
  if ((GlobalData.PTE_Feedback_col || GlobalData.EtalonFeedback)
       && !GlobalData.PTE_PowerParams_col) {
    nl_error(nl_response,
      "EtalonFeedback and PTE option '+Feedback' both require PTE option '+PowerParams'");
  }
  if (n_vars > MAX_VARS) {
    nl_error( 3,
      "Number of PTE columns defined (%d) exceeds MAX_VARS (%d)\n",
      n_vars, MAX_VARS);
  }
}

int PTfile::readline() {
  if ( fp == 0 ) return 0;
  if ( ScanNum < next_ScanNum ) {
    // This does not include the case where ScanNum==0, because then
    // next_ScanNum == 0 as well.
    // Note that if format != 2 (PTEfile) next_ScanNum will always be 0
    // As we are eliminating other PT formats, this can be ignored.
    ScanNum++;
    return 1;
  }
  for (;;) {
    char buf[MYBUFSIZE], *p, *ep;
    double data[MAX_VARS];
    int i;

    last_file_pos = ftell(fp);
    for (;;) {
      if ( fgets( buf, MYBUFSIZE, fp ) == 0 ) {
        fclose(fp);
        fp = 0;
        return 0;
      }
      ++linenum;
      /* Deal with very long input lines */
      if (buf[strlen(buf)-1] != '\n') {
        nl_error(1, "%s:%d: buffer size (%d) exceeded, skipping\n",
          fname, linenum, MYBUFSIZE);
        while (buf[strlen(buf)-1] != '\n') {
          if ( fgets( buf, MYBUFSIZE, fp ) == 0 ) {
            fclose(fp);
            fp = 0;
            return 0;
          }
        }
      } else break;
    }
    for ( p = buf, i = 0; i < n_vars; i++ ) {
      data[i] = strtod( p, &ep );
      if ( p == ep && i != n_vars ) {
        nl_error( 2,
          "%s:%d: Invalid number of parameters: Expected %d, read %d\n",
          fname, linenum, n_vars, i);
        fclose(fp);
        fp = 0;
        return 0;
      }
      p = ep;
    }
    if ( format == 2 ) {
      int cooff = 0; // offset for coadding
      time = 0.;
      ScanNum = int(data[0]);
      if (GlobalData.PTE_coadd) {
        LastScan = int(data[1]);
        cooff = 1;
      }
      P = data[1+cooff];
      T = data[2+cooff];
      for ( i = 0; i < 8; i++ ) Etln_params[i] = data[i+3+cooff];
      // Subsequent options already resolve cooff during parsing
      if (GlobalData.PTE_nu_F0_col) {
        GlobalData.input.nu_F0 = data[GlobalData.PTE_nu_F0_col];
      }
      if (GlobalData.PTE_MirrorLoss_col) {
        GlobalData.input.MirrorLoss = data[GlobalData.PTE_MirrorLoss_col];
      }
      if (GlobalData.PTE_Feedback_col) {
        Etln_params[GlobalData.PTE_Feedback_col-3] = data[GlobalData.PTE_Feedback_col];
      }
      if (GlobalData.PTE_PowerParams_col) {
        for (i = 0; i < 4; ++i) {
          Etln_params[GlobalData.PTE_PowerParams_col + i - 3] =
            data[GlobalData.PTE_PowerParams_col + i];
        }
      }
      return 1;
    } else {
      time = data[0];
      P = data[1];
      if ( format == 0 ) {
        T = 273.15 + ( data[2] + data[3] + data[4] + data[5] ) / 4.;
        next_ScanNum = int(data[6]);
        cal_flow = data[8];
        inlet_flow = data[9];
        RORIS = int(data[10]);
        RateS = int(data[11]);
      } else {
        T = data[2];
        next_ScanNum = int(data[3]);
        cal_flow = data[4];
        inlet_flow = data[5];
        RORIS = int(data[6]);
        RateS = 0;
      }
      // if ( T < 249. ) T = 273.15 + GlobalData.DefaultTemp;
      if ( ScanNum != next_ScanNum ) {
        if ( RORIS == GlobalData.QCLI_Wave ) {
          ScanNum = (ScanNum==0) ? next_ScanNum :
            ( (ScanNum<next_ScanNum) ? ScanNum+1 : ScanNum-1 );
          return 1;
        } else ScanNum = next_ScanNum;
      }
    }
  }
}

/**
 * Repositions read pointer to before the most recently read line.
 * Used during restart processing.
 */
void PTfile::backup() {
  if (last_file_pos >= 0)
    fseek(fp, last_file_pos, SEEK_SET);
}

void PTfile::calc_wndata() {
  if (GlobalData.ICOSdirFineTuned) return;
  int from = GlobalData.SignalRegion[0];
  int to = GlobalData.SignalRegion[1];
  int i;
  
  if ( GlobalData.PTformat != 2 )
    nl_error( 4, "calc_wndata called erroneously" );
  if ( ICOSfile::wndata == 0 ) ICOSfile::wndata = new f_vector( to+1, 0 );
  ICOSfile::wndata->check( to );
  for (i = from; i <= to; ++i) {
    double ii = (i - Etln_params[0] + 1) * 1e-3;
    double fn = Etln_params[1] + Etln_params[2]*ii + Etln_params[3]*ii*ii
      + Etln_params[4]*exp(-ii/Etln_params[5])
      + Etln_params[6]*exp(-ii/Etln_params[7]);
    if (GlobalData.PTE_PowerParams_col &&
        (GlobalData.PTE_Feedback_col || GlobalData.EtalonFeedback != 0)) {
      int pc = GlobalData.PTE_PowerParams_col-3; // Should be 9
      double P = Etln_params[pc]*ii*ii*ii + Etln_params[pc+1]*ii*ii +
        Etln_params[pc+2]*ii + Etln_params[pc+3];
      if (GlobalData.PTE_Feedback_col) {
        P = P * Etln_params[GlobalData.PTE_Feedback_col-3]; // Should be 8, right?
      }
      if (GlobalData.EtalonFeedback != 0) {
        P = P * GlobalData.EtalonFeedback;
      }
      fn = fn - P*sin(2 * M_PI * fn);
    }
    ICOSfile::wndata->data[i-MLBASE] = -GlobalData.EtalonFSR * fn;
    if (i > from &&
        ICOSfile::wndata->data[i-MLBASE] >= ICOSfile::wndata->data[i-MLBASE-1]) {
      nl_error(3, "%ld:%d: Tuning rate not monotonically decreasing", ScanNum, i);
    }
  }
  ICOSfile::wndata->n_data = to;
}

const int ICOSfile::mindatasize = 1024;

ICOSfile::ICOSfile( const char *fbase, const char *obase, int bin )
    : mlf(mlf_init( 3, 60, 0, fbase, "dat", NULL )),
      omlf(mlf_init( 3, 60, 1, obase, "dat", NULL )),
      ofp(0),
      sdata(new f_vector(mindatasize, 0)),
      ssdata(0),
      sbdata(0),
      binary(bin)
{
  bdata = new f_vector(mindatasize, 0);
}

f_vector *ICOSfile::bdata;
f_vector *ICOSfile::wndata;

/**
 * @param firstscan Input file index for multi-level-file routines
 * @param lastscan Input file index for last file if coadding
 * @return 1 on success, 0 if there was an error
 * If lastfile is zero or less than or equal to fileno,
 *  then only a single file is read.
 */
int ICOSfile::coadd(uint32_t firstscan, uint32_t lastscan) {
  if (lastscan <= firstscan)
    return read(firstscan);
  uint32_t n_scans =  0;
  for (uint32_t scan = firstscan; scan <= lastscan; ++scan) {
    if (read(scan)) {
      if (n_scans == 0) {
        if (!ssdata)
          ssdata = new f_vector(mindatasize, 0);
        ssdata->clear();
        ssdata->check(sdata->n_data);
        if (GlobalData.BaselineInput) {
          if (!sbdata)
            sbdata = new  f_vector(mindatasize, 0);
          sbdata->clear();
          sbdata->check(bdata->n_data);
          nl_assert(sdata->n_data == bdata->n_data);
        }
        ++n_scans;
        // initialize from sdata
        for (int i = 0; i < sdata->n_data; ++i) {
          ssdata->append(sdata->data[i]);
          // ssdata->data[i] = sdata->data[i];
        }
        if (GlobalData.BaselineInput) {
          for (int i = 0; i < bdata->n_data; ++i) {
            sbdata->append(bdata->data[i]);
            // sbdata->data[i] = bdata->data[i];
          }
        }
      } else {
        if (sdata->n_data != ssdata->n_data) {
          nl_error(2, "Scan length changed during coadd");
        } else {
          ++n_scans;
          // coadd from sdata into ssdata
          for (int i = 0; i < sdata->n_data; ++i) {
            ssdata->data[i] += sdata->data[i];
          }
          if (GlobalData.BaselineInput) {
            // coadd from bdata into sbdata
            nl_assert(sdata->n_data == bdata->n_data);
            for (int i = 0; i < bdata->n_data; ++i) {
              sbdata->data[i] += bdata->data[i];
            }
          }
        }
      }
    }
  }
  if (n_scans) {
    // average back from ssdata into sdata
    for (int i = 0; i < sdata->n_data; ++i) {
      sdata->data[i] = ssdata->data[i]/n_scans;
    }
    if (GlobalData.BaselineInput) {
      // average back from sbdata into bdata
      for (int i = 0; i < bdata->n_data; ++i) {
        bdata->data[i] = sbdata->data[i]/n_scans;
      }
    }
    return 1;
  }
  return 0;
}

/**
 * @param fileno Input file index for multi-level-file routines
 * @param lastfile Input file index for last file if coadding
 * @return 1 on success, 0 if there was an error
 * If lastfile is zero or less than or equal to fileno,
 *  then only a single file is read.
 * For ASCII Processing:
 *  fgets() reads in the line including the newline
 *  strtod() updates the endptr (ep) to point to the char
 *  immediately following the converted value. This should
 *  satisfy isspace(*ep) for every successful conversion,
 *  and since strtod swallows whitespace at the beginning,
 *  it should be false for every unsuccessful conversion.
 *
 *  An ASCII file is deemed to have an etalon if there are
 *  two numbers on a line. Clearly it would make sense
 *  to make this determination once per file and avoid
 *  testing each line.
 */
int ICOSfile::read(unsigned long int fileno) {
  FILE *fp;
  mlf_set_index( mlf, fileno );
  fp = mlf_next_file(mlf);
  if ( fp == 0 ) return 0;
  sdata->clear();
  // fdata->clear();
  bdata->clear();
  if ( binary ) {
    icos_hdr_t header[2];
    if ( fread_swap32( header, sizeof(icos_hdr_t), 2, fp ) != 2 ) {
      nl_error( 2, "%s: Error reading header: %s", mlf->fpath,
        strerror(errno) );
      fclose(fp);
      return 0;
    }
    // Support for new SSP file format
    if ((header[0] | 0x10000) == 0x10006 && header[1] > 255) {
      icos_hdr_t data[5];
      if (fread(data, sizeof(icos_hdr_t), 5, fp) != 5) {
        nl_error( 2, "%s: Error reading SSP header: %s", mlf->fpath,
          strerror(errno) );
        fclose(fp);
        return 0;
      }
      header[0] = header[1]>>16;
      header[1] &= 0xFF;
    }
    if ( header[0] <= 0 || header[1] <= 0 || header[1] > 3 ) {
      nl_error( 2, "%s: Invalid header ( %ld, %ld )", mlf->fpath,
        header[0], header[1] );
      fclose(fp);
      return 0;
    }
    sdata->check(header[0]);
    sdata->n_data =
      fread_swap32( sdata->data+sdata->offset, sizeof(float), header[0], fp );
    if ( sdata->n_data != (int)header[0] ) {
      nl_error( 2, "%s: Error reading sdata: %s", mlf->fpath, strerror(errno) );
      fclose(fp);
      return 0;
#if RESIZE_INPUT
    } else {
      float *raw = (float*)(sdata->data+sdata->offset);
      raw = raw - sdata->offset;
      for (int i = sdata->n_data; i > 0; --i) {
        sdata->data[i] = raw[i];
      }
#endif
    }
    if ( GlobalData.ICOSdirFineTuned ) {
      if ( wndata == 0 ) ICOSfile::wndata = new f_vector( header[0]+1, 0 );
      wndata->check(header[0]);
      wndata->n_data =
        fread_swap32( wndata->data+wndata->offset, sizeof(float), header[0], fp );
      if ( sdata->n_data != (int)header[0] ) {
        nl_error( 2, "%s: Error reading etalon/wndata: %s", mlf->fpath, strerror(errno) );
        fclose(fp);
        return 0;
  #if RESIZE_INPUT
      } else {
        float *raw = (float*)(wndata->data+wndata->offset);
        raw = raw - wndata->offset;
        for (int i = wndata->n_data; i > 0; --i) {
          wndata->data[i] = raw[i];
        }
  #endif
      }
    } else if (GlobalData.BaselineInput && header[1] >= 3) {
      // Skip column 2 (etalon)
      if (fseek(fp, header[0] * sizeof(float), SEEK_CUR)) {
        nl_error( 2, "%s: Error skipping edata: %s", mlf->fpath,
          strerror(errno));
        fclose(fp);
        return 0;
      }
    }
    if (GlobalData.BaselineInput && header[1] >= 3) {
      bdata->check(header[0]);
      bdata->n_data =
        fread_swap32( bdata->data+bdata->offset, sizeof(float), header[0], fp );
      if ( bdata->n_data != (int)header[0] ) {
        nl_error( 2, "%s: Error reading bdata: %s", strerror(errno) );
        fclose(fp);
        return 0;
#if RESIZE_INPUT
      } else {
        float *raw = (float*)(bdata->data+bdata->offset);
        raw = raw - bdata->offset;
        for (int i = bdata->n_data+bdata->offset-1; i >= bdata->offset; --i) {
          bdata->data[i] = raw[i];
        }
#endif
      }
    }
  } else {
    for (;;) {
      char buf[MYBUFSIZE], *ep;
      double value;

      if ( fgets( buf, MYBUFSIZE, fp ) == 0 ) {
        fclose(fp);
        break;
      }
      value = strtod( buf, &ep );
      if ( !isspace(*ep) ) {
        nl_error( 2, "%s:%d: No value read", mlf->fpath, sdata->n_data+1 );
        fclose(fp);
        return 0;
      }
      sdata->append(value);
      if ( GlobalData.BaselineInput ) {
        while (isspace(*ep)) ++ep;
        while ((*ep != '\0') && !isspace(*ep)) ++ep; // skip etalon
        value = strtod( ep, &ep );
        if ( !isspace(*ep) ) {
          nl_error( 2, "%s:%d: Expected three values in ASCII input",
              mlf->fpath, sdata->n_data );
          fclose(fp);
          return 0;
        } else bdata->append(value);
      }
    }
  }
  fclose(fp);
  if ( GlobalData.PTformat != 2 )
    nl_error(3, "Unsupported PTformat: %d", GlobalData.PTformat);

  // This first baseline calculation is the zero baseline which
  // precedes the laser-on ICOS data. It should not be confused
  // with the baseline function which follows which attempts to
  // match the laser power function.
  if ( GlobalData.BackgroundRegion[0] <=
       GlobalData.BackgroundRegion[1] ) {
    ICOS_Float baseline = 0., *yin = sdata->data;
    unsigned int i;
    for (i = GlobalData.BackgroundRegion[0]-MLBASE;
         i <= GlobalData.BackgroundRegion[1]-MLBASE;
         ++i) baseline += yin[i];
    baseline /=
      GlobalData.BackgroundRegion[1]-GlobalData.BackgroundRegion[0]+1;
    for (i = sdata->offset; (int)i < sdata->n_data+sdata->offset; ++i)
      yin[i] = yin[i] - baseline;
  }
  return 1;
}

/**
 * Translate wavenumber back to 0-based sample number
 * We will now assume that nu_F0 (the free parameter) has been
 * subtracted from wn before the call, and hence wn is suitable
 * for direct lookup in wndata.
 */
int ICOSfile::wn_sample( ICOS_Float wn ) {
  nl_assert( wndata->n_data >= (int)GlobalData.SignalRegion[1] );
  // Note that wavenumber decreases with sample, so I use 'low'
  // to identify the lower wavenumber value, although it is the
  // higher index number
  // wn -= nu_F0;
  int low = GlobalData.SignalRegion[1]-MLBASE;
  int high = GlobalData.SignalRegion[0]-MLBASE;
  ICOS_Float wnlow = wndata->data[low];
  ICOS_Float wnhigh = wndata->data[high];
  if (isnan(wnlow) || isnan(wnhigh)) {
    if (GlobalData.ICOSdirFineTuned)
      nl_error(3, "SignalRegion has apparently changed since FineTuned scans were generated");
    else
      nl_error(3, "Non-number from wndata in wn_sample");
  }
  if ( wn <= wnlow ) return low;
  if ( wn >= wnhigh ) return high;
  while ( low > high ) {
    int mid = floor(0.5+low + (wn-wnlow)*(high-low)/(wnhigh-wnlow));
    nl_assert( high <= mid && mid <= low );
    if ( mid == low ) return low;
    if ( mid == high ) return high;
    ICOS_Float wnmid = wndata->data[mid];
    if ( wn < wnmid ) {
      high = mid;
      wnhigh = wnmid;
    } else {
      low = mid;
      wnlow = wnmid;
    }
  }
  nl_error( 4, "wn_sample failed" );
  return 0;
}

FILE *ICOSfile::writefp(uint32_t index) {
  FILE *fp;
  mlf_set_index( omlf, index );
  fp = mlf_next_file(omlf);
  return fp;
}

#ifdef USE_BIG_ENDIAN
 int fread_swap32( void *buf, size_t size, size_t count, FILE *fp ) {
   int rv = fread( buf, size, count, fp );
   icos_hdr_t *bptr = (icos_hdr_t *)buf;
   if (size != 4) nl_error( 4, "fread_swap32 requires size == 4" );
   int i;
   for ( i = 0; i < rv; i++ ) {
     bptr[i] = bswap_32(bptr[i]);
   }
   return rv;
 }
#endif
