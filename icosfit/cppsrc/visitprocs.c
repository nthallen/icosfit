
#include "HEAD.h"
#include "err.h"
#include "node.h"
#include "visitprocs.h"
#include "attrpredef.h"

#include "visitmap.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "liga_dapto.h"
#endif

#ifndef _VisitVarDecl
#define _VisitVarDecl()
#endif

#ifndef _VisitEntry
#define _VisitEntry()
#endif

#ifndef _VisitExit
#define _VisitExit()
#endif


#if defined(__STDC__) || defined(__cplusplus)
#define _CALL_VS_(args) (void (*)args)
#else
#define _CALL_VS_(args) 
#endif
int* _IG_incl6;
DefTableKey* _IG_incl5;
DefTableKey* _IG_incl3;
Environment* _IG_incl0;
DefTableKey* _IG_incl1;
func_abs_p _AVConfigLineAbsorb_post;
Binding _AVGroupName_Bind;
DefTableKey _AVGroupName_Key;
int _AVGroupName_DefCond;
int _AVGroupName_GroupRefUnique;
int _AVGroupName_Sym;
int _AVFixFloat_fixfloat;
int _AVPosition_ipos;
DefTableKey _AVPosition_Key;
int _AVLine_fixfinepos;
int _AVLine_fixlorentz;
int _AVLine_fixdoppler;
double _AVLine_threshold;
int _AVLine_ipos;
int _AVLine_ierr;
double _AVLine_delta;
double _AVLine_n;
double _AVLine_E;
double _AVLine_Gair;
double _AVLine_S;
double _AVLine_nu;
int _AVLine_iso;
int _AVLine_mol;
DefTableKey _AVLineParam_Key;
DefTableKey _AVThreshold_Key;
double _AVThreshold_threshold;
int _AVPTE_optPTE_column_post;
int _AVPTE_optPTE_column_pre;
int _AVPTE_opt_PTE_ncols;
double _AVFrequency_FVal;
double _AVopt_ppm_FVal;
int _AVIntegerPair_High;
int _AVIntegerPair_Low;
int _AVPath_String;

#if defined(__STDC__) || defined(__cplusplus)
void LIGA_ATTREVAL (NODEPTR _currn)
#else
void LIGA_ATTREVAL (_currn) NODEPTR _currn;
#endif
{(*(VS1MAP[_currn->_prod])) ((NODEPTR)_currn);}
/*SPC(0)*/

#if defined(__STDC__) || defined(__cplusplus)
void _VS0Empty(NODEPTR _currn)
#else
void _VS0Empty(_currn) NODEPTR _currn;
#endif
{ _VisitVarDecl()
_VisitEntry();

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_1(_TPPrule_1 _currn)
#else
void _VS1rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_desc1->_ATLineKey=(* _IG_incl1);
/*SPC(333)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_1(_TPPrule_1 _currn)
#else
void _VS2rule_1(_currn )
_TPPrule_1 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVGroupName_DefCond=EQ(NoBinding, BindingInEnv((* _IG_incl0), _AVGroupName_Sym));
/*SPC(438)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_2(_TPPrule_2 _currn)
#else
void _VS1rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGroupRefUnique(_currn->_ATLineKey, 1, 0);
/*SPC(510)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_2(_TPPrule_2 _currn)
#else
void _VS2rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVGroupName_Sym=_currn->_ATTERM_1;
/*SPC(326)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_2(_TPPrule_2 _currn)
#else
void _VS3rule_2(_currn )
_TPPrule_2 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVGroupName_Bind=
((_AVGroupName_DefCond
) ? (BindIdn((* _IG_incl0), _AVGroupName_Sym)
) : (BindingInEnv((* _IG_incl0), _AVGroupName_Sym)))
;
/*SPC(442)*/
_AVGroupName_Key=KeyOf(_AVGroupName_Bind);
/*SPC(447)*/

if (_AVGroupName_DefCond) {
SetNparameter(_AVGroupName_Key, Nparameter(StringTable(_AVGroupName_Sym)), 0);

} else {
}
;
SetNparameter(_currn->_ATLineKey, GetNparameter(_AVGroupName_Key, 0), 0);
;
/*SPC(337)*/
_AVGroupName_GroupRefUnique=GetGroupRefUnique(_currn->_ATLineKey, 0);
/*SPC(513)*/

if (NOT(_AVGroupName_GroupRefUnique)) {
message(ERROR, "Group name is multiply defined", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(336)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_3(_TPPrule_3 _currn)
#else
void _VS1rule_3(_currn )
_TPPrule_3 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(BaselineInput, 1);
/*SPC(321)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_4(_TPPrule_4 _currn)
#else
void _VS1rule_4(_currn )
_TPPrule_4 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFrequency_FVal=100000.;
/*SPC(320)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_5(_TPPrule_5 _currn)
#else
void _VS1rule_5(_currn )
_TPPrule_5 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFrequency_FVal=1000.;
/*SPC(319)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_6(_TPPrule_6 _currn)
#else
void _VS1rule_6(_currn )
_TPPrule_6 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFrequency_FVal=1;
/*SPC(318)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_7(_TPPrule_7 _currn)
#else
void _VS1rule_7(_currn )
_TPPrule_7 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFrequency_FVal=1;
/*SPC(317)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_8(_TPPrule_8 _currn)
#else
void _VS1rule_8(_currn )
_TPPrule_8 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVopt_ppm_FVal=.000001;
/*SPC(316)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_9(_TPPrule_9 _currn)
#else
void _VS1rule_9(_currn )
_TPPrule_9 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVopt_ppm_FVal=.01;
/*SPC(315)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_10(_TPPrule_10 _currn)
#else
void _VS1rule_10(_currn )
_TPPrule_10 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVopt_ppm_FVal=1.;
/*SPC(314)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_11(_TPPrule_11 _currn)
#else
void _VS1rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
DefTableKey* _IL_incl5;
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc3->_prod])))((NODEPTR) _currn->_desc3);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc4->_prod])))((NODEPTR) _currn->_desc4);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc5->_prod])))((NODEPTR) _currn->_desc5);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc6->_prod])))((NODEPTR) _currn->_desc6);
_currn->_ATKey=NewKey();
/*SPC(275)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc7->_prod])))((NODEPTR) _currn->_desc7);
_IG_incl5=_IL_incl5;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_11(_TPPrule_11 _currn)
#else
void _VS2rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
DefTableKey* _IL_incl5;
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKey);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc7->_prod])))((NODEPTR) _currn->_desc7);
_IG_incl5=_IL_incl5;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_11(_TPPrule_11 _currn)
#else
void _VS3rule_11(_currn )
_TPPrule_11 _currn;

#endif
{
DefTableKey* _IL_incl5;
DefTableKey* _IL_incl1;

_VisitVarDecl()
_VisitEntry();
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATKey);
_IL_incl1=_IG_incl1;_IG_incl1= &(_currn->_ATKey);
_AVLine_fixfinepos=GetFixFinePosition(_currn->_ATKey, GetFixFinePosition((* _IG_incl3), 1));
/*SPC(295)*/
_AVLine_fixlorentz=GetFixLorentz(_currn->_ATKey, GetFixLorentz((* _IG_incl3), 0));
/*SPC(292)*/
_AVLine_fixdoppler=GetFixDoppler(_currn->_ATKey, GetFixDoppler((* _IG_incl3), 0));
/*SPC(289)*/
_AVLine_threshold=GetThreshold(_currn->_ATKey, GetThreshold((* _IG_incl3), 0.0001));
/*SPC(286)*/
_AVLine_ipos=GetPosition(_currn->_ATKey, 0);
/*SPC(285)*/
_AVLine_ierr=_currn->_ATTERM_3;
/*SPC(284)*/
_AVLine_delta=_currn->_desc6->_ATFVal;
/*SPC(283)*/
_AVLine_n=_currn->_desc5->_ATFVal;
/*SPC(282)*/
_AVLine_E=_currn->_desc4->_ATFVal;
/*SPC(281)*/
_AVLine_Gair=_currn->_desc3->_ATFVal;
/*SPC(280)*/
_AVLine_S=_currn->_desc2->_ATFVal;
/*SPC(279)*/
_AVLine_nu=_currn->_desc1->_ATFVal;
/*SPC(278)*/
_AVLine_iso=_currn->_ATTERM_2;
/*SPC(277)*/
_AVLine_mol=_currn->_ATTERM_1;
/*SPC(276)*/
_AVConfigLineAbsorb_post=abs_append(_AVConfigLineAbsorb_post, new_voigt(_AVLine_mol, _AVLine_iso, _AVLine_nu, _AVLine_S, _AVLine_Gair, _AVLine_E, _AVLine_n, _AVLine_delta, _AVLine_ipos, _AVLine_threshold, _AVLine_fixdoppler, _AVLine_fixlorentz, _AVLine_fixfinepos, GetNparameter(_currn->_ATKey, 0)));
/*SPC(306)*/
_IG_incl5=_IL_incl5;
_IG_incl1=_IL_incl1;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_12(_TPPrule_12 _currn)
#else
void _VS1rule_12(_currn )
_TPPrule_12 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLineParam_Key=(* _IG_incl5);
/*SPC(266)*/

if (HasFixFinePosition(_AVLineParam_Key)) {
message(ERROR, "Multiple Fix/Float FinePosition definitions", 0, (&( _currn->_AT_pos)));

} else {
SetFixFinePosition(_AVLineParam_Key, (* _IG_incl6), 0);
}
;
/*SPC(267)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_13(_TPPrule_13 _currn)
#else
void _VS1rule_13(_currn )
_TPPrule_13 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLineParam_Key=(* _IG_incl5);
/*SPC(260)*/

if (HasFixLorentz(_AVLineParam_Key)) {
message(ERROR, "Multiple Fix/Float Lorentz definitions", 0, (&( _currn->_AT_pos)));

} else {
SetFixLorentz(_AVLineParam_Key, (* _IG_incl6), 0);
}
;
/*SPC(261)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_14(_TPPrule_14 _currn)
#else
void _VS1rule_14(_currn )
_TPPrule_14 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVLineParam_Key=(* _IG_incl5);
/*SPC(254)*/

if (HasFixDoppler(_AVLineParam_Key)) {
message(ERROR, "Multiple Fix/Float Doppler definitions", 0, (&( _currn->_AT_pos)));

} else {
SetFixDoppler(_AVLineParam_Key, (* _IG_incl6), 0);
}
;
/*SPC(255)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_15(_TPPrule_15 _currn)
#else
void _VS1rule_15(_currn )
_TPPrule_15 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFixFloat_fixfloat=0;
/*SPC(251)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_16(_TPPrule_16 _currn)
#else
void _VS1rule_16(_currn )
_TPPrule_16 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVFixFloat_fixfloat=1;
/*SPC(248)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_17(_TPPrule_17 _currn)
#else
void _VS1rule_17(_currn )
_TPPrule_17 _currn;

#endif
{
int* _IL_incl6;

_VisitVarDecl()
_VisitEntry();
_IL_incl6=_IG_incl6;_IG_incl6= &(_currn->_ATfixfloat);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATfixfloat=_AVFixFloat_fixfloat;
/*SPC(245)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl6=_IL_incl6;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_18(_TPPrule_18 _currn)
#else
void _VS1rule_18(_currn )
_TPPrule_18 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPosition_ipos=_currn->_ATTERM_1;
/*SPC(237)*/
_AVPosition_Key=(* _IG_incl1);
/*SPC(236)*/

if (HasPosition(_AVPosition_Key)) {
message(ERROR, "Multiple Position definitions", 0, (&( _currn->_AT_pos)));

} else {
SetPosition(_AVPosition_Key, _AVPosition_ipos, 0);
}
;
/*SPC(238)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_19(_TPPrule_19 _currn)
#else
void _VS1rule_19(_currn )
_TPPrule_19 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVThreshold_Key=(* _IG_incl5);
/*SPC(230)*/
_AVThreshold_threshold=_currn->_desc1->_ATFVal;
/*SPC(229)*/

if (HasThreshold(_AVThreshold_Key)) {
message(ERROR, "Multiple threshold definitions", 0, (&( _currn->_AT_pos)));

} else {
SetThreshold(_AVThreshold_Key, _AVThreshold_threshold, 0.);
}
;
/*SPC(231)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_20(_TPPrule_20 _currn)
#else
void _VS1rule_20(_currn )
_TPPrule_20 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(N_Passes, _currn->_ATTERM_1);
/*SPC(218)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_21(_TPPrule_21 _currn)
#else
void _VS1rule_21(_currn )
_TPPrule_21 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(QCLI_Wave, _currn->_ATTERM_1);
/*SPC(215)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_22(_TPPrule_22 _currn)
#else
void _VS1rule_22(_currn )
_TPPrule_22 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(Verbosity, _currn->_ATTERM_1);
/*SPC(212)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_23(_TPPrule_23 _currn)
#else
void _VS1rule_23(_currn )
_TPPrule_23 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(QTdir, StringTable(_AVPath_String));
/*SPC(209)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_24(_TPPrule_24 _currn)
#else
void _VS1rule_24(_currn )
_TPPrule_24 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(MFile, StringTable(_AVPath_String));
/*SPC(206)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_25(_TPPrule_25 _currn)
#else
void _VS1rule_25(_currn )
_TPPrule_25 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(LogFile, StringTable(_AVPath_String));
/*SPC(203)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_26(_TPPrule_26 _currn)
#else
void _VS1rule_26(_currn )
_TPPrule_26 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(OutputFile, StringTable(_AVPath_String));
/*SPC(200)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_27(_TPPrule_27 _currn)
#else
void _VS1rule_27(_currn )
_TPPrule_27 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(OutputDir, StringTable(_AVPath_String));
/*SPC(197)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_28(_TPPrule_28 _currn)
#else
void _VS1rule_28(_currn )
_TPPrule_28 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(BaselineFile, StringTable(_AVPath_String));
/*SPC(194)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_29(_TPPrule_29 _currn)
#else
void _VS1rule_29(_currn )
_TPPrule_29 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPTE_opt_PTE_ncols=1;
/*SPC(190)*/
_AVPTE_optPTE_column_post=ADD(_AVPTE_optPTE_column_pre, _AVPTE_opt_PTE_ncols);
/*SPC(167)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_30(_TPPrule_30 _currn)
#else
void _VS1rule_30(_currn )
_TPPrule_30 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPTE_opt_PTE_ncols=1;
/*SPC(185)*/
_AVPTE_optPTE_column_post=ADD(_AVPTE_optPTE_column_pre, _AVPTE_opt_PTE_ncols);
/*SPC(167)*/

if (SetGlobalOnce(PTE_Feedback_col, _AVPTE_optPTE_column_pre)) {
message(ERROR, "Cannot specify '+ Feedback' more than once", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(187)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_31(_TPPrule_31 _currn)
#else
void _VS1rule_31(_currn )
_TPPrule_31 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPTE_opt_PTE_ncols=7;
/*SPC(180)*/
_AVPTE_optPTE_column_post=ADD(_AVPTE_optPTE_column_pre, _AVPTE_opt_PTE_ncols);
/*SPC(167)*/

if (SetGlobalOnce(PTE_PowerParams_col, _AVPTE_optPTE_column_pre)) {
message(ERROR, "Cannot specify '+ PowerParams' more than once", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(182)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_32(_TPPrule_32 _currn)
#else
void _VS1rule_32(_currn )
_TPPrule_32 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPTE_opt_PTE_ncols=1;
/*SPC(175)*/
_AVPTE_optPTE_column_post=ADD(_AVPTE_optPTE_column_pre, _AVPTE_opt_PTE_ncols);
/*SPC(167)*/

if (SetGlobalOnce(PTE_MirrorLoss_col, _AVPTE_optPTE_column_pre)) {
message(ERROR, "Cannot specify '+ MirrorLoss' more than once", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(177)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_33(_TPPrule_33 _currn)
#else
void _VS1rule_33(_currn )
_TPPrule_33 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPTE_opt_PTE_ncols=1;
/*SPC(170)*/
_AVPTE_optPTE_column_post=ADD(_AVPTE_optPTE_column_pre, _AVPTE_opt_PTE_ncols);
/*SPC(167)*/

if (SetGlobalOnce(PTE_nu_F0_col, _AVPTE_optPTE_column_pre)) {
message(ERROR, "Cannot specify '+ nu_F0' more than once", 0, (&( _currn->_AT_pos)));

} else {
}
;
/*SPC(172)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_34(_TPPrule_34 _currn)
#else
void _VS1rule_34(_currn )
_TPPrule_34 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPTE_optPTE_column_post=11;
/*SPC(164)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_35(_TPPrule_35 _currn)
#else
void _VS1rule_35(_currn )
_TPPrule_35 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(PTformat, 2);
/*SPC(157)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(PTFile, StringTable(_AVPath_String));
/*SPC(156)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_36(_TPPrule_36 _currn)
#else
void _VS1rule_36(_currn )
_TPPrule_36 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(PTformat, 1);
/*SPC(153)*/
message(ERROR, "PTFile format is obsolete", 0, (&( _currn->_AT_pos)));
/*SPC(152)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(PTFile, StringTable(_AVPath_String));
/*SPC(151)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_37(_TPPrule_37 _currn)
#else
void _VS1rule_37(_currn )
_TPPrule_37 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(PTformat, 0);
/*SPC(148)*/
message(ERROR, "PandTFile format is obsolete", 0, (&( _currn->_AT_pos)));
/*SPC(147)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(PTFile, StringTable(_AVPath_String));
/*SPC(146)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_38(_TPPrule_38 _currn)
#else
void _VS1rule_38(_currn )
_TPPrule_38 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(ICOSdir, StringTable(_AVPath_String));
/*SPC(143)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_39(_TPPrule_39 _currn)
#else
void _VS1rule_39(_currn )
_TPPrule_39 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(FitFunction, StringTable(_currn->_ATTERM_1));
/*SPC(140)*/
message(ERROR, "FitFunction keyword is currently non-functional", 0, (&( _currn->_AT_pos)));
/*SPC(139)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_40(_TPPrule_40 _currn)
#else
void _VS1rule_40(_currn )
_TPPrule_40 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(binary, 0);
/*SPC(135)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_41(_TPPrule_41 _currn)
#else
void _VS1rule_41(_currn )
_TPPrule_41 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(binary, 1);
/*SPC(132)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_42(_TPPrule_42 _currn)
#else
void _VS1rule_42(_currn )
_TPPrule_42 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();

if (Nu0IsSet) {
message(ERROR, "Cannot redefine nu0", 0, (&( _currn->_AT_pos)));

} else {
SetNu0(_currn->_ATTERM_1);
}
;
/*SPC(128)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_43(_TPPrule_43 _currn)
#else
void _VS1rule_43(_currn )
_TPPrule_43 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(MaxIterations, _currn->_ATTERM_1);
/*SPC(122)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_44(_TPPrule_44 _currn)
#else
void _VS1rule_44(_currn )
_TPPrule_44 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(ConvergenceCount, _currn->_ATTERM_1);
/*SPC(119)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_45(_TPPrule_45 _currn)
#else
void _VS1rule_45(_currn )
_TPPrule_45 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(ConvergenceStep, _currn->_desc1->_ATFVal);
/*SPC(116)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_46(_TPPrule_46 _currn)
#else
void _VS1rule_46(_currn )
_TPPrule_46 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(epsilon3, _currn->_desc1->_ATFVal);
/*SPC(113)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_47(_TPPrule_47 _currn)
#else
void _VS1rule_47(_currn )
_TPPrule_47 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(epsilon2, _currn->_desc1->_ATFVal);
/*SPC(110)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_48(_TPPrule_48 _currn)
#else
void _VS1rule_48(_currn )
_TPPrule_48 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(epsilon1, _currn->_desc1->_ATFVal);
/*SPC(107)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_49(_TPPrule_49 _currn)
#else
void _VS1rule_49(_currn )
_TPPrule_49 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(mu_scale, _currn->_desc1->_ATFVal);
/*SPC(104)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_50(_TPPrule_50 _currn)
#else
void _VS1rule_50(_currn )
_TPPrule_50 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
SetGlobal(SkewTolerance, MUL(_currn->_desc1->_ATFVal, _AVopt_ppm_FVal));
/*SPC(101)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_51(_TPPrule_51 _currn)
#else
void _VS1rule_51(_currn )
_TPPrule_51 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
SetGlobal(SampleRate, MUL(_currn->_desc1->_ATFVal, _AVFrequency_FVal));
/*SPC(98)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_52(_TPPrule_52 _currn)
#else
void _VS1rule_52(_currn )
_TPPrule_52 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
message(ERROR, "TuningRate is no longer supported", 0, (&( _currn->_AT_pos)));
/*SPC(95)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_53(_TPPrule_53 _currn)
#else
void _VS1rule_53(_currn )
_TPPrule_53 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(Sigma, _currn->_desc1->_ATFVal);
/*SPC(92)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_54(_TPPrule_54 _currn)
#else
void _VS1rule_54(_currn )
_TPPrule_54 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(CavityFixedLength, _currn->_desc1->_ATFVal);
/*SPC(89)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_55(_TPPrule_55 _currn)
#else
void _VS1rule_55(_currn )
_TPPrule_55 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(CavityLength, _currn->_desc1->_ATFVal);
/*SPC(86)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_56(_TPPrule_56 _currn)
#else
void _VS1rule_56(_currn )
_TPPrule_56 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(RightLineMarginMultiplier, _currn->_desc1->_ATFVal);
/*SPC(83)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_57(_TPPrule_57 _currn)
#else
void _VS1rule_57(_currn )
_TPPrule_57 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(RightLineMargin, _currn->_desc1->_ATFVal);
/*SPC(80)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_58(_TPPrule_58 _currn)
#else
void _VS1rule_58(_currn )
_TPPrule_58 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(LeftLineMarginMultiplier, _currn->_desc1->_ATFVal);
/*SPC(77)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_59(_TPPrule_59 _currn)
#else
void _VS1rule_59(_currn )
_TPPrule_59 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(LeftLineMargin, _currn->_desc1->_ATFVal);
/*SPC(74)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_60(_TPPrule_60 _currn)
#else
void _VS1rule_60(_currn )
_TPPrule_60 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(LeftLineMarginMultiplier, _currn->_desc1->_ATFVal);
/*SPC(70)*/
SetGlobal(RightLineMarginMultiplier, _currn->_desc1->_ATFVal);
/*SPC(71)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_61(_TPPrule_61 _currn)
#else
void _VS1rule_61(_currn )
_TPPrule_61 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(LeftLineMargin, _currn->_desc1->_ATFVal);
/*SPC(66)*/
SetGlobal(RightLineMargin, _currn->_desc1->_ATFVal);
/*SPC(67)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_62(_TPPrule_62 _currn)
#else
void _VS1rule_62(_currn )
_TPPrule_62 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(MaxEnsembleDriftPerScan, _currn->_desc1->_ATFVal);
/*SPC(63)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_63(_TPPrule_63 _currn)
#else
void _VS1rule_63(_currn )
_TPPrule_63 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(MaxFinePositionOffset, _currn->_desc1->_ATFVal);
/*SPC(60)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_64(_TPPrule_64 _currn)
#else
void _VS1rule_64(_currn )
_TPPrule_64 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
message(ERROR, "MinimumFringeSpacing is no longer supported", 0, (&( _currn->_AT_pos)));
/*SPC(57)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_65(_TPPrule_65 _currn)
#else
void _VS1rule_65(_currn )
_TPPrule_65 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(EtalonFeedback, _currn->_desc1->_ATFVal);
/*SPC(54)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_66(_TPPrule_66 _currn)
#else
void _VS1rule_66(_currn )
_TPPrule_66 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(EtalonFSR, _currn->_desc1->_ATFVal);
/*SPC(51)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_67(_TPPrule_67 _currn)
#else
void _VS1rule_67(_currn )
_TPPrule_67 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
message(ERROR, "DSFRLimits is no longer supported", 0, (&( _currn->_AT_pos)));
/*SPC(48)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_68(_TPPrule_68 _currn)
#else
void _VS1rule_68(_currn )
_TPPrule_68 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(PreserveOutput, 1);
/*SPC(44)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_69(_TPPrule_69 _currn)
#else
void _VS1rule_69(_currn )
_TPPrule_69 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
SetGlobal(RestartAt, _currn->_ATTERM_1);
/*SPC(41)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_70(_TPPrule_70 _currn)
#else
void _VS1rule_70(_currn )
_TPPrule_70 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
SetGlobalPair(ScanNumRange, _AVIntegerPair_Low, _AVIntegerPair_High);
/*SPC(37)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_71(_TPPrule_71 _currn)
#else
void _VS1rule_71(_currn )
_TPPrule_71 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobalPair(SignalRegion, _AVIntegerPair_Low, _AVIntegerPair_High);
/*SPC(33)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_72(_TPPrule_72 _currn)
#else
void _VS1rule_72(_currn )
_TPPrule_72 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobalPair(BackgroundRegion, _AVIntegerPair_Low, _AVIntegerPair_High);
/*SPC(29)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_73(_TPPrule_73 _currn)
#else
void _VS1rule_73(_currn )
_TPPrule_73 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
SetGlobal(MirrorLoss, MUL(_currn->_desc1->_ATFVal, _AVopt_ppm_FVal));
/*SPC(25)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_74(_TPPrule_74 _currn)
#else
void _VS1rule_74(_currn )
_TPPrule_74 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVIntegerPair_High=_currn->_ATTERM_2;
/*SPC(22)*/
_AVIntegerPair_Low=_currn->_ATTERM_1;
/*SPC(21)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_75(_TPPrule_75 _currn)
#else
void _VS1rule_75(_currn )
_TPPrule_75 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATFVal=SUB(ZERO(), _currn->_desc1->_ATFVal);
/*SPC(16)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_76(_TPPrule_76 _currn)
#else
void _VS1rule_76(_currn )
_TPPrule_76 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATFVal=CAST(double, _currn->_ATTERM_1);
/*SPC(13)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_77(_TPPrule_77 _currn)
#else
void _VS1rule_77(_currn )
_TPPrule_77 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_currn->_ATFVal=atof(StringTable(_currn->_ATTERM_1));
/*SPC(10)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_020(_TPPrule_020 _currn)
#else
void _VS1rule_020(_currn )
_TPPrule_020 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPath_String=_currn->_ATTERM_1;
/*SPC(7)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_019(_TPPrule_019 _currn)
#else
void _VS1rule_019(_currn )
_TPPrule_019 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
_AVPath_String=_currn->_ATTERM_1;
/*SPC(7)*/

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_018(_TPPrule_018 _currn)
#else
void _VS1rule_018(_currn )
_TPPrule_018 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_AVPTE_optPTE_column_pre=_AVPTE_optPTE_column_post;
/*SPC(0)*/
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_016(_TPPrule_016 _currn)
#else
void _VS1rule_016(_currn )
_TPPrule_016 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_016(_TPPrule_016 _currn)
#else
void _VS2rule_016(_currn )
_TPPrule_016 _currn;

#endif
{
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATEnv=RootEnv;
/*SPC(359)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_016(_TPPrule_016 _currn)
#else
void _VS3rule_016(_currn )
_TPPrule_016 _currn;

#endif
{
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_016(_TPPrule_016 _currn)
#else
void _VS4rule_016(_currn )
_TPPrule_016 _currn;

#endif
{
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_015(_TPPrule_015 _currn)
#else
void _VS2rule_015(_currn )
_TPPrule_015 _currn;

#endif
{
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
_currn->_ATEnv=RootEnv;
/*SPC(359)*/
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_015(_TPPrule_015 _currn)
#else
void _VS3rule_015(_currn )
_TPPrule_015 _currn;

#endif
{
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS4rule_015(_TPPrule_015 _currn)
#else
void _VS4rule_015(_currn )
_TPPrule_015 _currn;

#endif
{
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_014(_TPPrule_014 _currn)
#else
void _VS1rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_014(_TPPrule_014 _currn)
#else
void _VS2rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_014(_TPPrule_014 _currn)
#else
void _VS3rule_014(_currn )
_TPPrule_014 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS4MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_013(_TPPrule_013 _currn)
#else
void _VS1rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_013(_TPPrule_013 _currn)
#else
void _VS2rule_013(_currn )
_TPPrule_013 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_07(_TPPrule_07 _currn)
#else
void _VS3rule_07(_currn )
_TPPrule_07 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc2->_prod])))((NODEPTR) _currn->_desc2);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_06(_TPPrule_06 _currn)
#else
void _VS3rule_06(_currn )
_TPPrule_06 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_04(_TPPrule_04 _currn)
#else
void _VS1rule_04(_currn )
_TPPrule_04 _currn;

#endif
{
DefTableKey* _IL_incl5;
DefTableKey* _IL_incl3;
Environment* _IL_incl0;

_VisitVarDecl()
_VisitEntry();
_IL_incl5=_IG_incl5;_IG_incl5= &(_currn->_ATKey);
_IL_incl3=_IG_incl3;_IG_incl3= &(_currn->_ATKey);
_IL_incl0=_IG_incl0;_IG_incl0= &(_currn->_ATEnv);
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATKey=NewKey();
/*SPC(224)*/
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
_currn->_ATEnv=RootEnv;
/*SPC(359)*/
_AVConfigLineAbsorb_post=new_func_abs();
/*SPC(302)*/
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);
SetGlobal(absorb, _AVConfigLineAbsorb_post);
/*SPC(303)*/
_IG_incl5=_IL_incl5;
_IG_incl3=_IL_incl3;
_IG_incl0=_IL_incl0;

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_03(_TPPrule_03 _currn)
#else
void _VS2rule_03(_currn )
_TPPrule_03 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS1rule_02(_TPPrule_02 _currn)
#else
void _VS1rule_02(_currn )
_TPPrule_02 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_02(_TPPrule_02 _currn)
#else
void _VS2rule_02(_currn )
_TPPrule_02 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS2MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS3rule_02(_TPPrule_02 _currn)
#else
void _VS3rule_02(_currn )
_TPPrule_02 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS3MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

#if defined(__STDC__) || defined(__cplusplus)
void _VS2rule_01(_TPPrule_01 _currn)
#else
void _VS2rule_01(_currn )
_TPPrule_01 _currn;

#endif
{

_VisitVarDecl()
_VisitEntry();
(*(_CALL_VS_((NODEPTR )) (VS1MAP[_currn->_desc1->_prod])))((NODEPTR) _currn->_desc1);

_VisitExit();
}

