#include "funceval.h"
#include "nl.h"

ICOS_Float func_line::get_molwt( int isotopomer ) {
  switch (isotopomer) {
    case 11: return 18.010565; // H_{2}^{16}O
    case 12: return 20.014811; // H_{2}^{18}O
    case 13: return 19.014780; // H_{2}^{17}O
    case 14: return 19.016740; // HD^{16}O
    case 15: return 21.020985; // HD^{18}O
    case 16: return 20.020956; // HD^{17}O
    case 21: return 43.989830; // ^{12}C^{16}O_{2}
    case 22: return 44.993185; // ^{13}C^{16}O_{2}
    case 23: return 45.994076; // ^{16}O^{12}C^{18}O
    case 24: return 44.994045; // ^{16}O^{12}C^{17}O
    case 31: return 47.984745; // ^{16}O_{3}
    case 41: return 44.001062; // ^{14}N_{2}^{16}O
    case 42: return 44.998096; // ^{14}N^{15}N^{16}O
    case 43: return 44.998096; // ^{15}N^{14}N^{16}O
    case 44: return 46.005308; // ^{14}N_{2}^{18}O
    case 45: return 45.005278; // ^{14}N_{2}^{17}O
    case 61: return 16.031300; // ^{12}CH_{4}
    case 62: return 17.034655; // ^{13}CH_{4}
    case 63: return 17.037475; // ^{12}CH_{3}D
    case 81: return 29.997989; // ^{14}N^{16}O
    case 101: return 45.992904; // ^{14}N^{16}O_{2}
    case 131: return 17.002740; // ^{16}OH
    case 151: return 35.976678; // H^{35}Cl
    case 152: return 37.973729; // H^{37}Cl
    case 153: return 36.982853; // D^{35}Cl
    case 154: return 38.979904; // D^{37}Cl
    case 201: return 30.010565; // H_{2}^{12}C^{16}O
    case 202: return 31.013920; // H_{2}^{13}C^{16}O
    case 203: return 32.014811; // H_{2}^{12}C^{18}O
    default:
      nl_error( 3,
        "Uncatalogued isotopomer '%d': Edit funceval.c get_molwt()",
         isotopomer );
      return 0; // Never reached
  }
}
