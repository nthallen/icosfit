
/* definition of tree node structure */

#ifndef NODE_H
#define NODE_H
#include "err.h"
#include "nodeptr.h" /* defines NODEPTR */
#include "HEAD.h"

#ifdef MONITOR
#define _NODECOMMON int _prod; POSITION _coord; int _uid;
#else
#define _NODECOMMON int _prod;
#endif
struct NODEPTR_struct {
        _NODECOMMON
#ifdef __cplusplus
        void* operator new(size_t size);
#endif
};

typedef struct _TSLineOpt* _TSPLineOpt;
typedef struct _TSConfigLine* _TSPConfigLine;
typedef struct _TSG1* _TSPG1;
typedef struct _TSLinedef* _TSPLinedef;
typedef struct _TSGroupSpec* _TSPGroupSpec;
typedef struct _TSGroupName* _TSPGroupName;
typedef struct _TSLines* _TSPLines;
typedef struct _TSLineOpts* _TSPLineOpts;
typedef struct _TSFixFloat* _TSPFixFloat;
typedef struct _TSFixLineParam* _TSPFixLineParam;
typedef struct _TSPosition* _TSPPosition;
typedef struct _TSLine* _TSPLine;
typedef struct _TSLineParam* _TSPLineParam;
typedef struct _TSThreshold* _TSPThreshold;
typedef struct _TSConfigFile* _TSPConfigFile;
typedef struct _TSopt_BaselineInput* _TSPopt_BaselineInput;
typedef struct _TSPTE_opt* _TSPPTE_opt;
typedef struct _TSPTE_opts* _TSPPTE_opts;
typedef struct _TSPTE_options* _TSPPTE_options;
typedef struct _TSopt_coadd* _TSPopt_coadd;
typedef struct _TSFrequency* _TSPFrequency;
typedef struct _TSopt_tunerate* _TSPopt_tunerate;
typedef struct _TSopt_cm* _TSPopt_cm;
typedef struct _TSopt_wn* _TSPopt_wn;
typedef struct _TSopt_preserve* _TSPopt_preserve;
typedef struct _TSScanNumRangeName* _TSPScanNumRangeName;
typedef struct _TSopt_ppm* _TSPopt_ppm;
typedef struct _TSConfigCmd* _TSPConfigCmd;
typedef struct _TSIntegerPair* _TSPIntegerPair;
typedef struct _TSFloatVal* _TSPFloatVal;
typedef struct _TSPath* _TSPPath;
typedef struct _TPrule_1* _TPPrule_1;
typedef struct _TPrule_2* _TPPrule_2;
typedef struct _TPrule_3* _TPPrule_3;
typedef struct _TPrule_4* _TPPrule_4;
typedef struct _TPrule_5* _TPPrule_5;
typedef struct _TPrule_6* _TPPrule_6;
typedef struct _TPrule_7* _TPPrule_7;
typedef struct _TPrule_8* _TPPrule_8;
typedef struct _TPrule_9* _TPPrule_9;
typedef struct _TPrule_10* _TPPrule_10;
typedef struct _TPrule_11* _TPPrule_11;
typedef struct _TPrule_12* _TPPrule_12;
typedef struct _TPrule_13* _TPPrule_13;
typedef struct _TPrule_14* _TPPrule_14;
typedef struct _TPrule_15* _TPPrule_15;
typedef struct _TPrule_16* _TPPrule_16;
typedef struct _TPrule_17* _TPPrule_17;
typedef struct _TPrule_18* _TPPrule_18;
typedef struct _TPrule_19* _TPPrule_19;
typedef struct _TPrule_20* _TPPrule_20;
typedef struct _TPrule_21* _TPPrule_21;
typedef struct _TPrule_22* _TPPrule_22;
typedef struct _TPrule_23* _TPPrule_23;
typedef struct _TPrule_24* _TPPrule_24;
typedef struct _TPrule_25* _TPPrule_25;
typedef struct _TPrule_26* _TPPrule_26;
typedef struct _TPrule_27* _TPPrule_27;
typedef struct _TPrule_28* _TPPrule_28;
typedef struct _TPrule_29* _TPPrule_29;
typedef struct _TPrule_30* _TPPrule_30;
typedef struct _TPrule_31* _TPPrule_31;
typedef struct _TPrule_32* _TPPrule_32;
typedef struct _TPrule_33* _TPPrule_33;
typedef struct _TPrule_34* _TPPrule_34;
typedef struct _TPrule_35* _TPPrule_35;
typedef struct _TPrule_36* _TPPrule_36;
typedef struct _TPrule_37* _TPPrule_37;
typedef struct _TPrule_38* _TPPrule_38;
typedef struct _TPrule_39* _TPPrule_39;
typedef struct _TPrule_40* _TPPrule_40;
typedef struct _TPrule_41* _TPPrule_41;
typedef struct _TPrule_42* _TPPrule_42;
typedef struct _TPrule_43* _TPPrule_43;
typedef struct _TPrule_44* _TPPrule_44;
typedef struct _TPrule_45* _TPPrule_45;
typedef struct _TPrule_46* _TPPrule_46;
typedef struct _TPrule_47* _TPPrule_47;
typedef struct _TPrule_48* _TPPrule_48;
typedef struct _TPrule_49* _TPPrule_49;
typedef struct _TPrule_50* _TPPrule_50;
typedef struct _TPrule_51* _TPPrule_51;
typedef struct _TPrule_52* _TPPrule_52;
typedef struct _TPrule_53* _TPPrule_53;
typedef struct _TPrule_54* _TPPrule_54;
typedef struct _TPrule_55* _TPPrule_55;
typedef struct _TPrule_56* _TPPrule_56;
typedef struct _TPrule_57* _TPPrule_57;
typedef struct _TPrule_58* _TPPrule_58;
typedef struct _TPrule_59* _TPPrule_59;
typedef struct _TPrule_60* _TPPrule_60;
typedef struct _TPrule_61* _TPPrule_61;
typedef struct _TPrule_62* _TPPrule_62;
typedef struct _TPrule_63* _TPPrule_63;
typedef struct _TPrule_64* _TPPrule_64;
typedef struct _TPrule_65* _TPPrule_65;
typedef struct _TPrule_66* _TPPrule_66;
typedef struct _TPrule_67* _TPPrule_67;
typedef struct _TPrule_68* _TPPrule_68;
typedef struct _TPrule_69* _TPPrule_69;
typedef struct _TPrule_70* _TPPrule_70;
typedef struct _TPrule_71* _TPPrule_71;
typedef struct _TPrule_72* _TPPrule_72;
typedef struct _TPrule_73* _TPPrule_73;
typedef struct _TPrule_74* _TPPrule_74;
typedef struct _TPrule_75* _TPPrule_75;
typedef struct _TPrule_76* _TPPrule_76;
typedef struct _TPrule_77* _TPPrule_77;
typedef struct _TPrule_78* _TPPrule_78;
typedef struct _TPrule_79* _TPPrule_79;
typedef struct _TPrule_80* _TPPrule_80;
typedef struct _TPrule_031* _TPPrule_031;
typedef struct _TPrule_030* _TPPrule_030;
typedef struct _TPrule_029* _TPPrule_029;
typedef struct _TPrule_028* _TPPrule_028;
typedef struct _TPrule_027* _TPPrule_027;
typedef struct _TPrule_026* _TPPrule_026;
typedef struct _TPrule_025* _TPPrule_025;
typedef struct _TPrule_024* _TPPrule_024;
typedef struct _TPrule_023* _TPPrule_023;
typedef struct _TPrule_022* _TPPrule_022;
typedef struct _TPrule_021* _TPPrule_021;
typedef struct _TPrule_020* _TPPrule_020;
typedef struct _TPrule_019* _TPPrule_019;
typedef struct _TPrule_018* _TPPrule_018;
typedef struct _TPrule_017* _TPPrule_017;
typedef struct _TPrule_016* _TPPrule_016;
typedef struct _TPrule_015* _TPPrule_015;
typedef struct _TPrule_014* _TPPrule_014;
typedef struct _TPrule_013* _TPPrule_013;
typedef struct _TPrule_012* _TPPrule_012;
typedef struct _TPrule_011* _TPPrule_011;
typedef struct _TPrule_010* _TPPrule_010;
typedef struct _TPrule_09* _TPPrule_09;
typedef struct _TPrule_08* _TPPrule_08;
typedef struct _TPrule_07* _TPPrule_07;
typedef struct _TPrule_06* _TPPrule_06;
typedef struct _TPrule_05* _TPPrule_05;
typedef struct _TPrule_04* _TPPrule_04;
typedef struct _TPrule_03* _TPPrule_03;
typedef struct _TPrule_02* _TPPrule_02;
typedef struct _TPrule_01* _TPPrule_01;

struct _TSLineOpt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSConfigLine
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSG1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLinedef
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSGroupSpec
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSGroupName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATLineKey;
};

struct _TSLines
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
};

struct _TSLineOpts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFixFloat
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFixLineParam
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATfixfloat;
};

struct _TSPosition
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSLine
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
};

struct _TSLineParam
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSThreshold
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSConfigFile
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
DefTableKey _ATKey;
};

struct _TSopt_BaselineInput
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPTE_opt
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPTE_opts
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSPTE_options
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSopt_coadd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFrequency
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSopt_tunerate
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSopt_cm
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSopt_wn
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSopt_preserve
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSScanNumRangeName
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSopt_ppm
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSConfigCmd
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSIntegerPair
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TSFloatVal
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATFVal;
};

struct _TSPath
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_1
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPGroupName _desc1;
};

struct _TPrule_2
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATLineKey;
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_3
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_4
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_5
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_6
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_7
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_8
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_9
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_10
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_11
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
DefTableKey _ATKey;
_TSPFloatVal _desc1;
_TSPFloatVal _desc2;
_TSPFloatVal _desc3;
_TSPFloatVal _desc4;
_TSPFloatVal _desc5;
_TSPFloatVal _desc6;
_TSPLineOpts _desc7;
int _ATTERM_3;
int _ATTERM_2;
int _ATTERM_1;
};

struct _TPrule_12
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_13
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_14
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_15
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_16
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_17
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATfixfloat;
_TSPFixFloat _desc1;
_TSPLineParam _desc2;
};

struct _TPrule_18
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_19
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
POSITION _AT_pos;
};

struct _TPrule_20
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_21
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_22
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_23
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
};

struct _TPrule_24
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
};

struct _TPrule_25
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
};

struct _TPrule_26
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
};

struct _TPrule_27
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
};

struct _TPrule_28
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
_TSPopt_BaselineInput _desc2;
};

struct _TPrule_29
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_30
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_31
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_32
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_33
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
};

struct _TPrule_34
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPTE_opts _desc1;
};

struct _TPrule_35
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_36
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
_TSPopt_coadd _desc2;
_TSPPTE_options _desc3;
};

struct _TPrule_37
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
POSITION _AT_pos;
};

struct _TPrule_38
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
POSITION _AT_pos;
};

struct _TPrule_39
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPath _desc1;
};

struct _TPrule_40
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_41
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_42
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_43
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_44
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
POSITION _AT_pos;
int _ATTERM_1;
};

struct _TPrule_45
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_46
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_47
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_48
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_49
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_50
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_51
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_52
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_ppm _desc2;
};

struct _TPrule_53
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPFrequency _desc2;
};

struct _TPrule_54
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_tunerate _desc2;
POSITION _AT_pos;
};

struct _TPrule_55
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_56
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_cm _desc2;
};

struct _TPrule_57
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_cm _desc2;
};

struct _TPrule_58
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_59
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_wn _desc2;
};

struct _TPrule_60
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_61
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_wn _desc2;
};

struct _TPrule_62
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_63
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_wn _desc2;
};

struct _TPrule_64
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_wn _desc2;
};

struct _TPrule_65
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_wn _desc2;
};

struct _TPrule_66
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
POSITION _AT_pos;
};

struct _TPrule_67
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
};

struct _TPrule_68
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_wn _desc2;
};

struct _TPrule_69
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPFloatVal _desc2;
POSITION _AT_pos;
};

struct _TPrule_70
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_71
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_72
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPopt_preserve _desc1;
int _ATTERM_1;
};

struct _TPrule_73
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPScanNumRangeName _desc1;
_TSPIntegerPair _desc2;
};

struct _TPrule_74
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIntegerPair _desc1;
};

struct _TPrule_75
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPIntegerPair _desc1;
};

struct _TPrule_76
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFloatVal _desc1;
_TSPopt_ppm _desc2;
};

struct _TPrule_77
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_2;
int _ATTERM_1;
};

struct _TPrule_78
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATFVal;
_TSPFloatVal _desc1;
};

struct _TPrule_79
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATFVal;
int _ATTERM_1;
};

struct _TPrule_80
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
double _ATFVal;
int _ATTERM_1;
};

struct _TPrule_031
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_030
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_029
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_028
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_027
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_026
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_025
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_024
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_023
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_022
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_021
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_020
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_019
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
int _ATTERM_1;
};

struct _TPrule_018
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPTE_opts _desc1;
_TSPPTE_opt _desc2;
};

struct _TPrule_017
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_016
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
_TSPLines _desc1;
_TSPLine _desc2;
};

struct _TPrule_015
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
};

struct _TPrule_014
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLines _desc1;
};

struct _TPrule_013
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLineOpts _desc1;
_TSPLineOpt _desc2;
};

struct _TPrule_012
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
};

struct _TPrule_011
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPThreshold _desc1;
};

struct _TPrule_010
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPPosition _desc1;
};

struct _TPrule_09
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPGroupSpec _desc1;
};

struct _TPrule_08
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFixLineParam _desc1;
};

struct _TPrule_07
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPG1 _desc1;
_TSPConfigLine _desc2;
};

struct _TPrule_06
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPConfigLine _desc1;
};

struct _TPrule_05
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPConfigCmd _desc1;
};

struct _TPrule_04
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
Environment _ATEnv;
DefTableKey _ATKey;
_TSPG1 _desc1;
};

struct _TPrule_03
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPThreshold _desc1;
};

struct _TPrule_02
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPLinedef _desc1;
};

struct _TPrule_01
#ifdef __cplusplus
	: public NODEPTR_struct {
#else
{
_NODECOMMON
#endif
_TSPFixLineParam _desc1;
};

#undef _NODECOMMON
#endif
