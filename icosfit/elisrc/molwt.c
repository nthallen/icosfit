#include "funceval.h"
#include "nl.h"

ICOS_Float func_line::get_molwt( int isotopomer ) {
  switch (isotopomer) {
    case 11: return 18.010565; // H_2O
    case 12: return 20.014811; // H_2{}^{18}O
    case 13: return 19.01478;  // H_2{}^{17}O
    case 14: return 19.01674;  // HDO
    case 15: return 21.020985; // HD^{18}O
    case 16: return 20.020956; // HD^{17}O
    case 21: return 43.989830; // CO2
    case 22: return 44.993183; // CO_2{}^{13}C
    case 23: return 45.994076; // CO_2{}^{18}O
    case 24: return 44.994045; // CO_2{}^{17}O
    case 41: return 44.001060; // N2O
    case 42: return 44.998096; // N^{15}NO
    case 43: return 44.998096; // NN^{15}O
    case 61: return 16.031300; // CH_4
    case 62: return 17.034655; // C13H4
    case 63: return 17.037476; // CH3D
    case 81: return 29.997990; // NO
    case 101: return 45.992905; // NO2
    case 131: return 17.002741; // OH
    case 151: return 35.976677; //H35Cl
    case 152: return 37.973728; //H37Cl
    case 153: return 36.983; // D35Cl
    case 154: return 38.98; // D37Cl
    case 201: return 30.010565; // H2C0
    case 202: return 31.013920; // H213CO
    case 203: return 32.014812; // H2C18O
    default:
      nl_error( 3,
        "Uncatalogued isotopomer '%d': Edit funceval.c get_molwt()",
         isotopomer );
      return 0; // Never reached
  }
}
