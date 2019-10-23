
/* interface of tree construction functions */

#ifndef TREECON_H
#define TREECON_H
#include "eliproto.h"

#include "err.h"

#include "nodeptr.h"

#include "HEAD.h"


extern void InitTree ELI_ARG((void));

extern void FreeTree ELI_ARG((void));

extern NODEPTR MkLineOpt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConfigLine ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkG1 ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLinedef ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkGroupSpec ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkGroupName ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLines ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLineOpts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFixFloat ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFixLineParam ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPosition ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLine ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkLineParam ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkThreshold ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConfigFile ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkopt_BaselineInput ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPTE_opt ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPTE_opts ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPTE_options ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFrequency ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkopt_tunerate ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkopt_cm ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkopt_wn ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkopt_preserve ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkScanNumRangeName ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkopt_ppm ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkConfigCmd ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkIntegerPair ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkFloatVal ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR MkPath ELI_ARG((POSITION *_coordref, NODEPTR _currn));
extern NODEPTR Mkrule_1 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_2 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_3 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_4 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_5 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_6 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_7 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_8 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_9 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_10 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_11 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4, NODEPTR _desc5, NODEPTR _desc6, int _TERM3, NODEPTR _desc7));
extern NODEPTR Mkrule_12 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_13 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_14 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_15 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_16 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_17 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_18 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_19 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_20 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_21 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_22 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_23 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_24 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_25 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_26 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_27 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_28 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_29 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_30 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_31 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_32 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_33 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_34 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_35 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_36 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_37 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_38 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_39 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_40 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_41 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_42 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_43 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_44 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_45 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_46 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_47 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_48 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_49 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_50 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_51 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_52 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_53 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_54 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_55 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_56 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_57 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_58 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_59 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_60 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_61 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_62 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_63 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_64 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_65 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_66 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_67 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_68 ELI_ARG((POSITION *_coordref, int _TERM1, NODEPTR _desc1));
extern NODEPTR Mkrule_69 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_70 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_71 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_72 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_73 ELI_ARG((POSITION *_coordref, int _TERM1, int _TERM2));
extern NODEPTR Mkrule_74 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_75 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_76 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_030 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_029 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_028 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_027 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_026 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_025 ELI_ARG((POSITION *_coordref, int _TERM1));
extern NODEPTR Mkrule_024 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_023 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_022 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_021 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_020 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_019 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_018 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_017 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_016 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_015 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_014 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_013 ELI_ARG((POSITION *_coordref));
extern NODEPTR Mkrule_012 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_011 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_010 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_09 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_08 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_07 ELI_ARG((POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2));
extern NODEPTR Mkrule_06 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_05 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_04 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_03 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_02 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
extern NODEPTR Mkrule_01 ELI_ARG((POSITION *_coordref, NODEPTR _desc1));
#define MkPathStr(pos,val) (val)
#define MkFloat(pos,val) (val)
#define MkInteger(pos,val) (val)
#define MkIdent(pos,val) (val)
#endif
