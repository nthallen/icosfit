
/* implementation of tree construction functions */

#include "node.h"

#include "nodecode.h"

#include "attrpredef.h"

#include "visitmap.h"

#include "treeact.h"

#ifdef MONITOR
#include "attr_mon_dapto.h"
#include "MONTblStack.h"
#endif

#include <stdlib.h>

#define _USE_OBSTACK 1

/* use of obstack: */

#if _USE_OBSTACK

#include "obstack.h"
static struct obstack TreeSpace;
static void *_TreeBase;

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	return obstack_alloc(&TreeSpace, size);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	return (char *)(obstack_alloc(&TreeSpace, size));
}
#endif

void InitTree()
{
	obstack_init(&TreeSpace);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

void FreeTree()
{
	obstack_free(&TreeSpace, _TreeBase);
	_TreeBase=obstack_alloc(&TreeSpace,0);
}

#else

#include <stdio.h>

#ifdef __cplusplus
void* NODEPTR_struct::operator new(size_t size)
{
	void *retval = malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#else
#if defined(__STDC__) || defined(__cplusplus)
char* TreeNodeAlloc(int size)
#else
char* TreeNodeAlloc(size) int size;
#endif
{
	char *retval = (char *) malloc(size);
	if (retval) return retval;
	fprintf(stderr, "*** DEADLY: No more memory.\n");
	exit(1);
}
#endif

void InitTree() { }

void FreeTree() { }

#endif

#ifdef MONITOR
#define _SETCOORD(node) \
        node->_coord = _coordref ? *_coordref : NoCoord;
#define _COPYCOORD(node) \
        node->_coord = _currn->_desc1->_coord;
#else
#define _SETCOORD(node)
#define _COPYCOORD(node)
#endif
#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLineOpt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLineOpt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLineOpt)) return (_currn);
if (IsSymb (_currn, SYMBFixLineParam)) return (Mkrule_08(_coordref, _currn));
if (IsSymb (_currn, SYMBGroupSpec)) return (Mkrule_09(_coordref, _currn));
if (IsSymb (_currn, SYMBPosition)) return (Mkrule_010(_coordref, _currn));
if (IsSymb (_currn, SYMBThreshold)) return (Mkrule_011(_coordref, _currn));
return(NULLNODEPTR);
}/* MkLineOpt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConfigLine (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConfigLine (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConfigLine)) return (_currn);
return(NULLNODEPTR);
}/* MkConfigLine */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkG1 (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkG1 (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBG1)) return (_currn);
if (IsSymb (_currn, SYMBConfigLine)) return (Mkrule_06(_coordref, _currn));
return(NULLNODEPTR);
}/* MkG1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLinedef (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLinedef (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLinedef)) return (_currn);
return(NULLNODEPTR);
}/* MkLinedef */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGroupSpec (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkGroupSpec (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBGroupSpec)) return (_currn);
return(NULLNODEPTR);
}/* MkGroupSpec */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkGroupName (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkGroupName (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBGroupName)) return (_currn);
return(NULLNODEPTR);
}/* MkGroupName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLines (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLines (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLines)) return (_currn);
return(NULLNODEPTR);
}/* MkLines */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLineOpts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLineOpts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLineOpts)) return (_currn);
return(NULLNODEPTR);
}/* MkLineOpts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFixFloat (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFixFloat (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFixFloat)) return (_currn);
return(NULLNODEPTR);
}/* MkFixFloat */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFixLineParam (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFixLineParam (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFixLineParam)) return (_currn);
return(NULLNODEPTR);
}/* MkFixLineParam */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPosition (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPosition (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPosition)) return (_currn);
return(NULLNODEPTR);
}/* MkPosition */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLine (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLine (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLine)) return (_currn);
return(NULLNODEPTR);
}/* MkLine */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkLineParam (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkLineParam (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBLineParam)) return (_currn);
return(NULLNODEPTR);
}/* MkLineParam */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkThreshold (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkThreshold (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBThreshold)) return (_currn);
return(NULLNODEPTR);
}/* MkThreshold */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConfigFile (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConfigFile (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConfigFile)) return (_currn);
if (IsSymb (_currn, SYMBConfigLine)) return (Mkrule_04(_coordref, _currn));
if (IsSymb (_currn, SYMBG1)) return (Mkrule_04(_coordref, _currn));
return(NULLNODEPTR);
}/* MkConfigFile */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkopt_BaselineInput (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkopt_BaselineInput (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBopt_BaselineInput)) return (_currn);
return(NULLNODEPTR);
}/* Mkopt_BaselineInput */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPTE_opt (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPTE_opt (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPTE_opt)) return (_currn);
return(NULLNODEPTR);
}/* MkPTE_opt */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPTE_opts (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPTE_opts (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPTE_opts)) return (_currn);
return(NULLNODEPTR);
}/* MkPTE_opts */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPTE_options (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPTE_options (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPTE_options)) return (_currn);
if (IsSymb (_currn, SYMBPTE_opts)) return (Mkrule_34(_coordref, _currn));
return(NULLNODEPTR);
}/* MkPTE_options */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFrequency (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFrequency (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFrequency)) return (_currn);
return(NULLNODEPTR);
}/* MkFrequency */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkopt_tunerate (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkopt_tunerate (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBopt_tunerate)) return (_currn);
return(NULLNODEPTR);
}/* Mkopt_tunerate */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkopt_cm (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkopt_cm (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBopt_cm)) return (_currn);
return(NULLNODEPTR);
}/* Mkopt_cm */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkopt_wn (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkopt_wn (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBopt_wn)) return (_currn);
return(NULLNODEPTR);
}/* Mkopt_wn */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkopt_preserve (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkopt_preserve (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBopt_preserve)) return (_currn);
return(NULLNODEPTR);
}/* Mkopt_preserve */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkScanNumRangeName (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkScanNumRangeName (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBScanNumRangeName)) return (_currn);
return(NULLNODEPTR);
}/* MkScanNumRangeName */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkopt_ppm (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR Mkopt_ppm (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBopt_ppm)) return (_currn);
return(NULLNODEPTR);
}/* Mkopt_ppm */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkConfigCmd (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkConfigCmd (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBConfigCmd)) return (_currn);
if (IsSymb (_currn, SYMBLinedef)) return (Mkrule_02(_coordref, _currn));
if (IsSymb (_currn, SYMBFixLineParam)) return (Mkrule_01(_coordref, _currn));
if (IsSymb (_currn, SYMBThreshold)) return (Mkrule_03(_coordref, _currn));
return(NULLNODEPTR);
}/* MkConfigCmd */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkIntegerPair (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkIntegerPair (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBIntegerPair)) return (_currn);
return(NULLNODEPTR);
}/* MkIntegerPair */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkFloatVal (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkFloatVal (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBFloatVal)) return (_currn);
return(NULLNODEPTR);
}/* MkFloatVal */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR MkPath (POSITION *_coordref, NODEPTR _currn)
#else
NODEPTR MkPath (_coordref, _currn)
	POSITION *_coordref; NODEPTR _currn;
#endif
{
if (_currn == NULLNODEPTR) return NULLNODEPTR;
if (IsSymb (_currn, SYMBPath)) return (_currn);
return(NULLNODEPTR);
}/* MkPath */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_1 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_1 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_1 _currn;
#ifdef __cplusplus
_currn = new _TPrule_1;
#else
_currn = (_TPPrule_1) TreeNodeAlloc (sizeof (struct _TPrule_1));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_1;
_currn->_desc1 = (_TSPGroupName) MkGroupName (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_1: root of subtree no. 1 can not be made a GroupName node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_1;
return ( (NODEPTR) _currn);
}/* Mkrule_1 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_2 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_2 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_2 _currn;
#ifdef __cplusplus
_currn = new _TPrule_2;
#else
_currn = (_TPPrule_2) TreeNodeAlloc (sizeof (struct _TPrule_2));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_2;
_SETCOORD(_currn)
_TERMACT_rule_2;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Ident", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_2 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_3 (POSITION *_coordref)
#else
NODEPTR Mkrule_3 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_3 _currn;
#ifdef __cplusplus
_currn = new _TPrule_3;
#else
_currn = (_TPPrule_3) TreeNodeAlloc (sizeof (struct _TPrule_3));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_3;
_SETCOORD(_currn)
_TERMACT_rule_3;
return ( (NODEPTR) _currn);
}/* Mkrule_3 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_4 (POSITION *_coordref)
#else
NODEPTR Mkrule_4 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_4 _currn;
#ifdef __cplusplus
_currn = new _TPrule_4;
#else
_currn = (_TPPrule_4) TreeNodeAlloc (sizeof (struct _TPrule_4));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_4;
_SETCOORD(_currn)
_TERMACT_rule_4;
return ( (NODEPTR) _currn);
}/* Mkrule_4 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_5 (POSITION *_coordref)
#else
NODEPTR Mkrule_5 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_5 _currn;
#ifdef __cplusplus
_currn = new _TPrule_5;
#else
_currn = (_TPPrule_5) TreeNodeAlloc (sizeof (struct _TPrule_5));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_5;
_SETCOORD(_currn)
_TERMACT_rule_5;
return ( (NODEPTR) _currn);
}/* Mkrule_5 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_6 (POSITION *_coordref)
#else
NODEPTR Mkrule_6 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_6 _currn;
#ifdef __cplusplus
_currn = new _TPrule_6;
#else
_currn = (_TPPrule_6) TreeNodeAlloc (sizeof (struct _TPrule_6));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_6;
_SETCOORD(_currn)
_TERMACT_rule_6;
return ( (NODEPTR) _currn);
}/* Mkrule_6 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_7 (POSITION *_coordref)
#else
NODEPTR Mkrule_7 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_7 _currn;
#ifdef __cplusplus
_currn = new _TPrule_7;
#else
_currn = (_TPPrule_7) TreeNodeAlloc (sizeof (struct _TPrule_7));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_7;
_SETCOORD(_currn)
_TERMACT_rule_7;
return ( (NODEPTR) _currn);
}/* Mkrule_7 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_8 (POSITION *_coordref)
#else
NODEPTR Mkrule_8 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_8 _currn;
#ifdef __cplusplus
_currn = new _TPrule_8;
#else
_currn = (_TPPrule_8) TreeNodeAlloc (sizeof (struct _TPrule_8));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_8;
_SETCOORD(_currn)
_TERMACT_rule_8;
return ( (NODEPTR) _currn);
}/* Mkrule_8 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_9 (POSITION *_coordref)
#else
NODEPTR Mkrule_9 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_9 _currn;
#ifdef __cplusplus
_currn = new _TPrule_9;
#else
_currn = (_TPPrule_9) TreeNodeAlloc (sizeof (struct _TPrule_9));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_9;
_SETCOORD(_currn)
_TERMACT_rule_9;
return ( (NODEPTR) _currn);
}/* Mkrule_9 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_10 (POSITION *_coordref)
#else
NODEPTR Mkrule_10 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_10 _currn;
#ifdef __cplusplus
_currn = new _TPrule_10;
#else
_currn = (_TPPrule_10) TreeNodeAlloc (sizeof (struct _TPrule_10));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_10;
_SETCOORD(_currn)
_TERMACT_rule_10;
return ( (NODEPTR) _currn);
}/* Mkrule_10 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_11 (POSITION *_coordref, int _TERM1, int _TERM2, NODEPTR _desc1, NODEPTR _desc2, NODEPTR _desc3, NODEPTR _desc4, NODEPTR _desc5, NODEPTR _desc6, int _TERM3, NODEPTR _desc7)
#else
NODEPTR Mkrule_11 (_coordref, _TERM1, _TERM2,_desc1,_desc2,_desc3,_desc4,_desc5,_desc6, _TERM3,_desc7)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
	NODEPTR _desc1;
	NODEPTR _desc2;
	NODEPTR _desc3;
	NODEPTR _desc4;
	NODEPTR _desc5;
	NODEPTR _desc6;
	int _TERM3;
	NODEPTR _desc7;
#endif
{	_TPPrule_11 _currn;
#ifdef __cplusplus
_currn = new _TPrule_11;
#else
_currn = (_TPPrule_11) TreeNodeAlloc (sizeof (struct _TPrule_11));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_11;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPFloatVal) MkFloatVal (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 2 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc3 = (_TSPFloatVal) MkFloatVal (_coordref, _desc3);	
if (((NODEPTR)_currn->_desc3) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 3 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc4 = (_TSPFloatVal) MkFloatVal (_coordref, _desc4);	
if (((NODEPTR)_currn->_desc4) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 4 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc5 = (_TSPFloatVal) MkFloatVal (_coordref, _desc5);	
if (((NODEPTR)_currn->_desc5) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 5 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc6 = (_TSPFloatVal) MkFloatVal (_coordref, _desc6);	
if (((NODEPTR)_currn->_desc6) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 6 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc7 = (_TSPLineOpts) MkLineOpts (_coordref, _desc7);	
if (((NODEPTR)_currn->_desc7) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_11: root of subtree no. 7 can not be made a LineOpts node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_11;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer[2]", _TERM2);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer[3]", _TERM3);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_11 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_12 (POSITION *_coordref)
#else
NODEPTR Mkrule_12 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_12 _currn;
#ifdef __cplusplus
_currn = new _TPrule_12;
#else
_currn = (_TPPrule_12) TreeNodeAlloc (sizeof (struct _TPrule_12));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_12;
_SETCOORD(_currn)
_TERMACT_rule_12;
return ( (NODEPTR) _currn);
}/* Mkrule_12 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_13 (POSITION *_coordref)
#else
NODEPTR Mkrule_13 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_13 _currn;
#ifdef __cplusplus
_currn = new _TPrule_13;
#else
_currn = (_TPPrule_13) TreeNodeAlloc (sizeof (struct _TPrule_13));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_13;
_SETCOORD(_currn)
_TERMACT_rule_13;
return ( (NODEPTR) _currn);
}/* Mkrule_13 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_14 (POSITION *_coordref)
#else
NODEPTR Mkrule_14 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_14 _currn;
#ifdef __cplusplus
_currn = new _TPrule_14;
#else
_currn = (_TPPrule_14) TreeNodeAlloc (sizeof (struct _TPrule_14));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_14;
_SETCOORD(_currn)
_TERMACT_rule_14;
return ( (NODEPTR) _currn);
}/* Mkrule_14 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_15 (POSITION *_coordref)
#else
NODEPTR Mkrule_15 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_15 _currn;
#ifdef __cplusplus
_currn = new _TPrule_15;
#else
_currn = (_TPPrule_15) TreeNodeAlloc (sizeof (struct _TPrule_15));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_15;
_SETCOORD(_currn)
_TERMACT_rule_15;
return ( (NODEPTR) _currn);
}/* Mkrule_15 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_16 (POSITION *_coordref)
#else
NODEPTR Mkrule_16 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_16 _currn;
#ifdef __cplusplus
_currn = new _TPrule_16;
#else
_currn = (_TPPrule_16) TreeNodeAlloc (sizeof (struct _TPrule_16));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_16;
_SETCOORD(_currn)
_TERMACT_rule_16;
return ( (NODEPTR) _currn);
}/* Mkrule_16 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_17 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_17 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_17 _currn;
#ifdef __cplusplus
_currn = new _TPrule_17;
#else
_currn = (_TPPrule_17) TreeNodeAlloc (sizeof (struct _TPrule_17));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_17;
_currn->_desc1 = (_TSPFixFloat) MkFixFloat (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 1 can not be made a FixFloat node ", 0, _coordref);
_currn->_desc2 = (_TSPLineParam) MkLineParam (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_17: root of subtree no. 2 can not be made a LineParam node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_17;
return ( (NODEPTR) _currn);
}/* Mkrule_17 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_18 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_18 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_18 _currn;
#ifdef __cplusplus
_currn = new _TPrule_18;
#else
_currn = (_TPPrule_18) TreeNodeAlloc (sizeof (struct _TPrule_18));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_18;
_SETCOORD(_currn)
_TERMACT_rule_18;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_18 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_19 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_19 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_19 _currn;
#ifdef __cplusplus
_currn = new _TPrule_19;
#else
_currn = (_TPPrule_19) TreeNodeAlloc (sizeof (struct _TPrule_19));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_19;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_19: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_19;
return ( (NODEPTR) _currn);
}/* Mkrule_19 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_20 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_20 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_20 _currn;
#ifdef __cplusplus
_currn = new _TPrule_20;
#else
_currn = (_TPPrule_20) TreeNodeAlloc (sizeof (struct _TPrule_20));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_20;
_SETCOORD(_currn)
_TERMACT_rule_20;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_20 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_21 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_21 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_21 _currn;
#ifdef __cplusplus
_currn = new _TPrule_21;
#else
_currn = (_TPPrule_21) TreeNodeAlloc (sizeof (struct _TPrule_21));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_21;
_SETCOORD(_currn)
_TERMACT_rule_21;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_21 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_22 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_22 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_22 _currn;
#ifdef __cplusplus
_currn = new _TPrule_22;
#else
_currn = (_TPPrule_22) TreeNodeAlloc (sizeof (struct _TPrule_22));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_22;
_SETCOORD(_currn)
_TERMACT_rule_22;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_22 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_23 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_23 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_23 _currn;
#ifdef __cplusplus
_currn = new _TPrule_23;
#else
_currn = (_TPPrule_23) TreeNodeAlloc (sizeof (struct _TPrule_23));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_23;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_23: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_23;
return ( (NODEPTR) _currn);
}/* Mkrule_23 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_24 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_24 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_24 _currn;
#ifdef __cplusplus
_currn = new _TPrule_24;
#else
_currn = (_TPPrule_24) TreeNodeAlloc (sizeof (struct _TPrule_24));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_24;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_24: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_24;
return ( (NODEPTR) _currn);
}/* Mkrule_24 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_25 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_25 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_25 _currn;
#ifdef __cplusplus
_currn = new _TPrule_25;
#else
_currn = (_TPPrule_25) TreeNodeAlloc (sizeof (struct _TPrule_25));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_25;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_25: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_25;
return ( (NODEPTR) _currn);
}/* Mkrule_25 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_26 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_26 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_26 _currn;
#ifdef __cplusplus
_currn = new _TPrule_26;
#else
_currn = (_TPPrule_26) TreeNodeAlloc (sizeof (struct _TPrule_26));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_26;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_26: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_26;
return ( (NODEPTR) _currn);
}/* Mkrule_26 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_27 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_27 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_27 _currn;
#ifdef __cplusplus
_currn = new _TPrule_27;
#else
_currn = (_TPPrule_27) TreeNodeAlloc (sizeof (struct _TPrule_27));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_27;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_27: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_27;
return ( (NODEPTR) _currn);
}/* Mkrule_27 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_28 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_28 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_28 _currn;
#ifdef __cplusplus
_currn = new _TPrule_28;
#else
_currn = (_TPPrule_28) TreeNodeAlloc (sizeof (struct _TPrule_28));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_28;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_BaselineInput) Mkopt_BaselineInput (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_28: root of subtree no. 2 can not be made a opt_BaselineInput node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_28;
return ( (NODEPTR) _currn);
}/* Mkrule_28 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_29 (POSITION *_coordref)
#else
NODEPTR Mkrule_29 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_29 _currn;
#ifdef __cplusplus
_currn = new _TPrule_29;
#else
_currn = (_TPPrule_29) TreeNodeAlloc (sizeof (struct _TPrule_29));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_29;
_SETCOORD(_currn)
_TERMACT_rule_29;
return ( (NODEPTR) _currn);
}/* Mkrule_29 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_30 (POSITION *_coordref)
#else
NODEPTR Mkrule_30 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_30 _currn;
#ifdef __cplusplus
_currn = new _TPrule_30;
#else
_currn = (_TPPrule_30) TreeNodeAlloc (sizeof (struct _TPrule_30));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_30;
_SETCOORD(_currn)
_TERMACT_rule_30;
return ( (NODEPTR) _currn);
}/* Mkrule_30 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_31 (POSITION *_coordref)
#else
NODEPTR Mkrule_31 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_31 _currn;
#ifdef __cplusplus
_currn = new _TPrule_31;
#else
_currn = (_TPPrule_31) TreeNodeAlloc (sizeof (struct _TPrule_31));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_31;
_SETCOORD(_currn)
_TERMACT_rule_31;
return ( (NODEPTR) _currn);
}/* Mkrule_31 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_32 (POSITION *_coordref)
#else
NODEPTR Mkrule_32 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_32 _currn;
#ifdef __cplusplus
_currn = new _TPrule_32;
#else
_currn = (_TPPrule_32) TreeNodeAlloc (sizeof (struct _TPrule_32));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_32;
_SETCOORD(_currn)
_TERMACT_rule_32;
return ( (NODEPTR) _currn);
}/* Mkrule_32 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_33 (POSITION *_coordref)
#else
NODEPTR Mkrule_33 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_33 _currn;
#ifdef __cplusplus
_currn = new _TPrule_33;
#else
_currn = (_TPPrule_33) TreeNodeAlloc (sizeof (struct _TPrule_33));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_33;
_SETCOORD(_currn)
_TERMACT_rule_33;
return ( (NODEPTR) _currn);
}/* Mkrule_33 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_34 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_34 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_34 _currn;
#ifdef __cplusplus
_currn = new _TPrule_34;
#else
_currn = (_TPPrule_34) TreeNodeAlloc (sizeof (struct _TPrule_34));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_34;
_currn->_desc1 = (_TSPPTE_opts) MkPTE_opts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_34: root of subtree no. 1 can not be made a PTE_opts node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_34;
return ( (NODEPTR) _currn);
}/* Mkrule_34 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_35 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_35 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_35 _currn;
#ifdef __cplusplus
_currn = new _TPrule_35;
#else
_currn = (_TPPrule_35) TreeNodeAlloc (sizeof (struct _TPrule_35));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_35;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_35: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_currn->_desc2 = (_TSPPTE_options) MkPTE_options (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_35: root of subtree no. 2 can not be made a PTE_options node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_35;
return ( (NODEPTR) _currn);
}/* Mkrule_35 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_36 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_36 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_36 _currn;
#ifdef __cplusplus
_currn = new _TPrule_36;
#else
_currn = (_TPPrule_36) TreeNodeAlloc (sizeof (struct _TPrule_36));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_36;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_36: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_36;
return ( (NODEPTR) _currn);
}/* Mkrule_36 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_37 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_37 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_37 _currn;
#ifdef __cplusplus
_currn = new _TPrule_37;
#else
_currn = (_TPPrule_37) TreeNodeAlloc (sizeof (struct _TPrule_37));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_37;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_37: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_37;
return ( (NODEPTR) _currn);
}/* Mkrule_37 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_38 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_38 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_38 _currn;
#ifdef __cplusplus
_currn = new _TPrule_38;
#else
_currn = (_TPPrule_38) TreeNodeAlloc (sizeof (struct _TPrule_38));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_38;
_currn->_desc1 = (_TSPPath) MkPath (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_38: root of subtree no. 1 can not be made a Path node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_38;
return ( (NODEPTR) _currn);
}/* Mkrule_38 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_39 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_39 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_39 _currn;
#ifdef __cplusplus
_currn = new _TPrule_39;
#else
_currn = (_TPPrule_39) TreeNodeAlloc (sizeof (struct _TPrule_39));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_39;
_SETCOORD(_currn)
_TERMACT_rule_39;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Ident", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_39 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_40 (POSITION *_coordref)
#else
NODEPTR Mkrule_40 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_40 _currn;
#ifdef __cplusplus
_currn = new _TPrule_40;
#else
_currn = (_TPPrule_40) TreeNodeAlloc (sizeof (struct _TPrule_40));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_40;
_SETCOORD(_currn)
_TERMACT_rule_40;
return ( (NODEPTR) _currn);
}/* Mkrule_40 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_41 (POSITION *_coordref)
#else
NODEPTR Mkrule_41 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_41 _currn;
#ifdef __cplusplus
_currn = new _TPrule_41;
#else
_currn = (_TPPrule_41) TreeNodeAlloc (sizeof (struct _TPrule_41));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_41;
_SETCOORD(_currn)
_TERMACT_rule_41;
return ( (NODEPTR) _currn);
}/* Mkrule_41 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_42 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_42 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_42 _currn;
#ifdef __cplusplus
_currn = new _TPrule_42;
#else
_currn = (_TPPrule_42) TreeNodeAlloc (sizeof (struct _TPrule_42));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_42;
_SETCOORD(_currn)
_TERMACT_rule_42;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_42 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_43 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_43 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_43 _currn;
#ifdef __cplusplus
_currn = new _TPrule_43;
#else
_currn = (_TPPrule_43) TreeNodeAlloc (sizeof (struct _TPrule_43));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_43;
_SETCOORD(_currn)
_TERMACT_rule_43;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_43 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_44 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_44 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_44 _currn;
#ifdef __cplusplus
_currn = new _TPrule_44;
#else
_currn = (_TPPrule_44) TreeNodeAlloc (sizeof (struct _TPrule_44));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_44;
_SETCOORD(_currn)
_TERMACT_rule_44;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_44 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_45 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_45 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_45 _currn;
#ifdef __cplusplus
_currn = new _TPrule_45;
#else
_currn = (_TPPrule_45) TreeNodeAlloc (sizeof (struct _TPrule_45));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_45;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_45: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_45;
return ( (NODEPTR) _currn);
}/* Mkrule_45 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_46 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_46 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_46 _currn;
#ifdef __cplusplus
_currn = new _TPrule_46;
#else
_currn = (_TPPrule_46) TreeNodeAlloc (sizeof (struct _TPrule_46));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_46;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_46: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_46;
return ( (NODEPTR) _currn);
}/* Mkrule_46 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_47 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_47 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_47 _currn;
#ifdef __cplusplus
_currn = new _TPrule_47;
#else
_currn = (_TPPrule_47) TreeNodeAlloc (sizeof (struct _TPrule_47));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_47;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_47: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_47;
return ( (NODEPTR) _currn);
}/* Mkrule_47 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_48 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_48 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_48 _currn;
#ifdef __cplusplus
_currn = new _TPrule_48;
#else
_currn = (_TPPrule_48) TreeNodeAlloc (sizeof (struct _TPrule_48));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_48;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_48: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_48;
return ( (NODEPTR) _currn);
}/* Mkrule_48 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_49 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_49 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_49 _currn;
#ifdef __cplusplus
_currn = new _TPrule_49;
#else
_currn = (_TPPrule_49) TreeNodeAlloc (sizeof (struct _TPrule_49));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_49;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_49: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_49;
return ( (NODEPTR) _currn);
}/* Mkrule_49 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_50 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_50 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_50 _currn;
#ifdef __cplusplus
_currn = new _TPrule_50;
#else
_currn = (_TPPrule_50) TreeNodeAlloc (sizeof (struct _TPrule_50));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_50;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_50: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_ppm) Mkopt_ppm (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_50: root of subtree no. 2 can not be made a opt_ppm node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_50;
return ( (NODEPTR) _currn);
}/* Mkrule_50 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_51 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_51 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_51 _currn;
#ifdef __cplusplus
_currn = new _TPrule_51;
#else
_currn = (_TPPrule_51) TreeNodeAlloc (sizeof (struct _TPrule_51));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_51;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPFrequency) MkFrequency (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_51: root of subtree no. 2 can not be made a Frequency node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_51;
return ( (NODEPTR) _currn);
}/* Mkrule_51 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_52 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_52 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_52 _currn;
#ifdef __cplusplus
_currn = new _TPrule_52;
#else
_currn = (_TPPrule_52) TreeNodeAlloc (sizeof (struct _TPrule_52));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_52;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_tunerate) Mkopt_tunerate (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_52: root of subtree no. 2 can not be made a opt_tunerate node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_52;
return ( (NODEPTR) _currn);
}/* Mkrule_52 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_53 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_53 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_53 _currn;
#ifdef __cplusplus
_currn = new _TPrule_53;
#else
_currn = (_TPPrule_53) TreeNodeAlloc (sizeof (struct _TPrule_53));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_53;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_53: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_53;
return ( (NODEPTR) _currn);
}/* Mkrule_53 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_54 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_54 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_54 _currn;
#ifdef __cplusplus
_currn = new _TPrule_54;
#else
_currn = (_TPPrule_54) TreeNodeAlloc (sizeof (struct _TPrule_54));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_54;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_54: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_cm) Mkopt_cm (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_54: root of subtree no. 2 can not be made a opt_cm node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_54;
return ( (NODEPTR) _currn);
}/* Mkrule_54 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_55 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_55 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_55 _currn;
#ifdef __cplusplus
_currn = new _TPrule_55;
#else
_currn = (_TPPrule_55) TreeNodeAlloc (sizeof (struct _TPrule_55));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_55;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_55: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_cm) Mkopt_cm (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_55: root of subtree no. 2 can not be made a opt_cm node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_55;
return ( (NODEPTR) _currn);
}/* Mkrule_55 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_56 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_56 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_56 _currn;
#ifdef __cplusplus
_currn = new _TPrule_56;
#else
_currn = (_TPPrule_56) TreeNodeAlloc (sizeof (struct _TPrule_56));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_56;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_56: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_56;
return ( (NODEPTR) _currn);
}/* Mkrule_56 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_57 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_57 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_57 _currn;
#ifdef __cplusplus
_currn = new _TPrule_57;
#else
_currn = (_TPPrule_57) TreeNodeAlloc (sizeof (struct _TPrule_57));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_57;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_57: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_wn) Mkopt_wn (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_57: root of subtree no. 2 can not be made a opt_wn node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_57;
return ( (NODEPTR) _currn);
}/* Mkrule_57 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_58 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_58 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_58 _currn;
#ifdef __cplusplus
_currn = new _TPrule_58;
#else
_currn = (_TPPrule_58) TreeNodeAlloc (sizeof (struct _TPrule_58));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_58;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_58: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_58;
return ( (NODEPTR) _currn);
}/* Mkrule_58 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_59 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_59 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_59 _currn;
#ifdef __cplusplus
_currn = new _TPrule_59;
#else
_currn = (_TPPrule_59) TreeNodeAlloc (sizeof (struct _TPrule_59));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_59;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_59: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_wn) Mkopt_wn (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_59: root of subtree no. 2 can not be made a opt_wn node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_59;
return ( (NODEPTR) _currn);
}/* Mkrule_59 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_60 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_60 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_60 _currn;
#ifdef __cplusplus
_currn = new _TPrule_60;
#else
_currn = (_TPPrule_60) TreeNodeAlloc (sizeof (struct _TPrule_60));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_60;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_60: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_60;
return ( (NODEPTR) _currn);
}/* Mkrule_60 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_61 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_61 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_61 _currn;
#ifdef __cplusplus
_currn = new _TPrule_61;
#else
_currn = (_TPPrule_61) TreeNodeAlloc (sizeof (struct _TPrule_61));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_61;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_61: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_wn) Mkopt_wn (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_61: root of subtree no. 2 can not be made a opt_wn node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_61;
return ( (NODEPTR) _currn);
}/* Mkrule_61 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_62 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_62 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_62 _currn;
#ifdef __cplusplus
_currn = new _TPrule_62;
#else
_currn = (_TPPrule_62) TreeNodeAlloc (sizeof (struct _TPrule_62));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_62;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_62: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_wn) Mkopt_wn (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_62: root of subtree no. 2 can not be made a opt_wn node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_62;
return ( (NODEPTR) _currn);
}/* Mkrule_62 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_63 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_63 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_63 _currn;
#ifdef __cplusplus
_currn = new _TPrule_63;
#else
_currn = (_TPPrule_63) TreeNodeAlloc (sizeof (struct _TPrule_63));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_63;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_63: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_wn) Mkopt_wn (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_63: root of subtree no. 2 can not be made a opt_wn node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_63;
return ( (NODEPTR) _currn);
}/* Mkrule_63 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_64 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_64 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_64 _currn;
#ifdef __cplusplus
_currn = new _TPrule_64;
#else
_currn = (_TPPrule_64) TreeNodeAlloc (sizeof (struct _TPrule_64));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_64;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_64: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_64;
return ( (NODEPTR) _currn);
}/* Mkrule_64 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_65 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_65 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_65 _currn;
#ifdef __cplusplus
_currn = new _TPrule_65;
#else
_currn = (_TPPrule_65) TreeNodeAlloc (sizeof (struct _TPrule_65));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_65;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_65: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_65;
return ( (NODEPTR) _currn);
}/* Mkrule_65 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_66 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_66 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_66 _currn;
#ifdef __cplusplus
_currn = new _TPrule_66;
#else
_currn = (_TPPrule_66) TreeNodeAlloc (sizeof (struct _TPrule_66));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_66;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_66: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_wn) Mkopt_wn (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_66: root of subtree no. 2 can not be made a opt_wn node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_66;
return ( (NODEPTR) _currn);
}/* Mkrule_66 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_67 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_67 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_67 _currn;
#ifdef __cplusplus
_currn = new _TPrule_67;
#else
_currn = (_TPPrule_67) TreeNodeAlloc (sizeof (struct _TPrule_67));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_67;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_67: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPFloatVal) MkFloatVal (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_67: root of subtree no. 2 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_67;
return ( (NODEPTR) _currn);
}/* Mkrule_67 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_68 (POSITION *_coordref)
#else
NODEPTR Mkrule_68 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_68 _currn;
#ifdef __cplusplus
_currn = new _TPrule_68;
#else
_currn = (_TPPrule_68) TreeNodeAlloc (sizeof (struct _TPrule_68));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_68;
_SETCOORD(_currn)
_TERMACT_rule_68;
return ( (NODEPTR) _currn);
}/* Mkrule_68 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_69 (POSITION *_coordref, int _TERM1, NODEPTR _desc1)
#else
NODEPTR Mkrule_69 (_coordref, _TERM1,_desc1)
	POSITION *_coordref;
	int _TERM1;
	NODEPTR _desc1;
#endif
{	_TPPrule_69 _currn;
#ifdef __cplusplus
_currn = new _TPrule_69;
#else
_currn = (_TPPrule_69) TreeNodeAlloc (sizeof (struct _TPrule_69));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_69;
_currn->_desc1 = (_TSPopt_preserve) Mkopt_preserve (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_69: root of subtree no. 1 can not be made a opt_preserve node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_69;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_69 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_70 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_70 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_70 _currn;
#ifdef __cplusplus
_currn = new _TPrule_70;
#else
_currn = (_TPPrule_70) TreeNodeAlloc (sizeof (struct _TPrule_70));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_70;
_currn->_desc1 = (_TSPScanNumRangeName) MkScanNumRangeName (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_70: root of subtree no. 1 can not be made a ScanNumRangeName node ", 0, _coordref);
_currn->_desc2 = (_TSPIntegerPair) MkIntegerPair (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_70: root of subtree no. 2 can not be made a IntegerPair node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_70;
return ( (NODEPTR) _currn);
}/* Mkrule_70 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_71 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_71 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_71 _currn;
#ifdef __cplusplus
_currn = new _TPrule_71;
#else
_currn = (_TPPrule_71) TreeNodeAlloc (sizeof (struct _TPrule_71));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_71;
_currn->_desc1 = (_TSPIntegerPair) MkIntegerPair (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_71: root of subtree no. 1 can not be made a IntegerPair node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_71;
return ( (NODEPTR) _currn);
}/* Mkrule_71 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_72 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_72 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_72 _currn;
#ifdef __cplusplus
_currn = new _TPrule_72;
#else
_currn = (_TPPrule_72) TreeNodeAlloc (sizeof (struct _TPrule_72));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_72;
_currn->_desc1 = (_TSPIntegerPair) MkIntegerPair (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_72: root of subtree no. 1 can not be made a IntegerPair node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_72;
return ( (NODEPTR) _currn);
}/* Mkrule_72 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_73 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_73 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_73 _currn;
#ifdef __cplusplus
_currn = new _TPrule_73;
#else
_currn = (_TPPrule_73) TreeNodeAlloc (sizeof (struct _TPrule_73));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_73;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_73: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_currn->_desc2 = (_TSPopt_ppm) Mkopt_ppm (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_73: root of subtree no. 2 can not be made a opt_ppm node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_73;
return ( (NODEPTR) _currn);
}/* Mkrule_73 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_74 (POSITION *_coordref, int _TERM1, int _TERM2)
#else
NODEPTR Mkrule_74 (_coordref, _TERM1, _TERM2)
	POSITION *_coordref;
	int _TERM1;
	int _TERM2;
#endif
{	_TPPrule_74 _currn;
#ifdef __cplusplus
_currn = new _TPrule_74;
#else
_currn = (_TPPrule_74) TreeNodeAlloc (sizeof (struct _TPrule_74));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_74;
_SETCOORD(_currn)
_TERMACT_rule_74;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer[1]", _TERM1);
#endif

#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer[2]", _TERM2);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_74 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_75 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_75 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_75 _currn;
#ifdef __cplusplus
_currn = new _TPrule_75;
#else
_currn = (_TPPrule_75) TreeNodeAlloc (sizeof (struct _TPrule_75));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_75;
_currn->_desc1 = (_TSPFloatVal) MkFloatVal (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_75: root of subtree no. 1 can not be made a FloatVal node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_75;
return ( (NODEPTR) _currn);
}/* Mkrule_75 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_76 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_76 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_76 _currn;
#ifdef __cplusplus
_currn = new _TPrule_76;
#else
_currn = (_TPPrule_76) TreeNodeAlloc (sizeof (struct _TPrule_76));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_76;
_SETCOORD(_currn)
_TERMACT_rule_76;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Integer", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_76 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_77 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_77 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_77 _currn;
#ifdef __cplusplus
_currn = new _TPrule_77;
#else
_currn = (_TPPrule_77) TreeNodeAlloc (sizeof (struct _TPrule_77));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_77;
_SETCOORD(_currn)
_TERMACT_rule_77;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Float", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_77 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_030 (POSITION *_coordref)
#else
NODEPTR Mkrule_030 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_030 _currn;
#ifdef __cplusplus
_currn = new _TPrule_030;
#else
_currn = (_TPPrule_030) TreeNodeAlloc (sizeof (struct _TPrule_030));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_030;
_SETCOORD(_currn)
_TERMACT_rule_030;
return ( (NODEPTR) _currn);
}/* Mkrule_030 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_029 (POSITION *_coordref)
#else
NODEPTR Mkrule_029 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_029 _currn;
#ifdef __cplusplus
_currn = new _TPrule_029;
#else
_currn = (_TPPrule_029) TreeNodeAlloc (sizeof (struct _TPrule_029));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_029;
_SETCOORD(_currn)
_TERMACT_rule_029;
return ( (NODEPTR) _currn);
}/* Mkrule_029 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_028 (POSITION *_coordref)
#else
NODEPTR Mkrule_028 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_028 _currn;
#ifdef __cplusplus
_currn = new _TPrule_028;
#else
_currn = (_TPPrule_028) TreeNodeAlloc (sizeof (struct _TPrule_028));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_028;
_SETCOORD(_currn)
_TERMACT_rule_028;
return ( (NODEPTR) _currn);
}/* Mkrule_028 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_027 (POSITION *_coordref)
#else
NODEPTR Mkrule_027 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_027 _currn;
#ifdef __cplusplus
_currn = new _TPrule_027;
#else
_currn = (_TPPrule_027) TreeNodeAlloc (sizeof (struct _TPrule_027));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_027;
_SETCOORD(_currn)
_TERMACT_rule_027;
return ( (NODEPTR) _currn);
}/* Mkrule_027 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_026 (POSITION *_coordref)
#else
NODEPTR Mkrule_026 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_026 _currn;
#ifdef __cplusplus
_currn = new _TPrule_026;
#else
_currn = (_TPPrule_026) TreeNodeAlloc (sizeof (struct _TPrule_026));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_026;
_SETCOORD(_currn)
_TERMACT_rule_026;
return ( (NODEPTR) _currn);
}/* Mkrule_026 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_025 (POSITION *_coordref)
#else
NODEPTR Mkrule_025 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_025 _currn;
#ifdef __cplusplus
_currn = new _TPrule_025;
#else
_currn = (_TPPrule_025) TreeNodeAlloc (sizeof (struct _TPrule_025));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_025;
_SETCOORD(_currn)
_TERMACT_rule_025;
return ( (NODEPTR) _currn);
}/* Mkrule_025 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_024 (POSITION *_coordref)
#else
NODEPTR Mkrule_024 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_024 _currn;
#ifdef __cplusplus
_currn = new _TPrule_024;
#else
_currn = (_TPPrule_024) TreeNodeAlloc (sizeof (struct _TPrule_024));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_024;
_SETCOORD(_currn)
_TERMACT_rule_024;
return ( (NODEPTR) _currn);
}/* Mkrule_024 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_023 (POSITION *_coordref)
#else
NODEPTR Mkrule_023 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_023 _currn;
#ifdef __cplusplus
_currn = new _TPrule_023;
#else
_currn = (_TPPrule_023) TreeNodeAlloc (sizeof (struct _TPrule_023));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_023;
_SETCOORD(_currn)
_TERMACT_rule_023;
return ( (NODEPTR) _currn);
}/* Mkrule_023 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_022 (POSITION *_coordref)
#else
NODEPTR Mkrule_022 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_022 _currn;
#ifdef __cplusplus
_currn = new _TPrule_022;
#else
_currn = (_TPPrule_022) TreeNodeAlloc (sizeof (struct _TPrule_022));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_022;
_SETCOORD(_currn)
_TERMACT_rule_022;
return ( (NODEPTR) _currn);
}/* Mkrule_022 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_021 (POSITION *_coordref)
#else
NODEPTR Mkrule_021 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_021 _currn;
#ifdef __cplusplus
_currn = new _TPrule_021;
#else
_currn = (_TPPrule_021) TreeNodeAlloc (sizeof (struct _TPrule_021));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_021;
_SETCOORD(_currn)
_TERMACT_rule_021;
return ( (NODEPTR) _currn);
}/* Mkrule_021 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_020 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_020 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_020 _currn;
#ifdef __cplusplus
_currn = new _TPrule_020;
#else
_currn = (_TPPrule_020) TreeNodeAlloc (sizeof (struct _TPrule_020));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_020;
_SETCOORD(_currn)
_TERMACT_rule_020;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "PathStr", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_020 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_019 (POSITION *_coordref, int _TERM1)
#else
NODEPTR Mkrule_019 (_coordref, _TERM1)
	POSITION *_coordref;
	int _TERM1;
#endif
{	_TPPrule_019 _currn;
#ifdef __cplusplus
_currn = new _TPrule_019;
#else
_currn = (_TPPrule_019) TreeNodeAlloc (sizeof (struct _TPrule_019));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_019;
_SETCOORD(_currn)
_TERMACT_rule_019;
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
_dapto_term_int((_currn)->_uid, "Ident", _TERM1);
#endif

return ( (NODEPTR) _currn);
}/* Mkrule_019 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_018 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_018 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_018 _currn;
#ifdef __cplusplus
_currn = new _TPrule_018;
#else
_currn = (_TPPrule_018) TreeNodeAlloc (sizeof (struct _TPrule_018));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_018;
_currn->_desc1 = (_TSPPTE_opts) MkPTE_opts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_018: root of subtree no. 1 can not be made a PTE_opts node ", 0, _coordref);
_currn->_desc2 = (_TSPPTE_opt) MkPTE_opt (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_018: root of subtree no. 2 can not be made a PTE_opt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_018;
return ( (NODEPTR) _currn);
}/* Mkrule_018 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_017 (POSITION *_coordref)
#else
NODEPTR Mkrule_017 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_017 _currn;
#ifdef __cplusplus
_currn = new _TPrule_017;
#else
_currn = (_TPPrule_017) TreeNodeAlloc (sizeof (struct _TPrule_017));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_017;
_SETCOORD(_currn)
_TERMACT_rule_017;
return ( (NODEPTR) _currn);
}/* Mkrule_017 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_016 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_016 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_016 _currn;
#ifdef __cplusplus
_currn = new _TPrule_016;
#else
_currn = (_TPPrule_016) TreeNodeAlloc (sizeof (struct _TPrule_016));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_016;
_currn->_desc1 = (_TSPLines) MkLines (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_016: root of subtree no. 1 can not be made a Lines node ", 0, _coordref);
_currn->_desc2 = (_TSPLine) MkLine (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_016: root of subtree no. 2 can not be made a Line node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_016;
return ( (NODEPTR) _currn);
}/* Mkrule_016 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_015 (POSITION *_coordref)
#else
NODEPTR Mkrule_015 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_015 _currn;
#ifdef __cplusplus
_currn = new _TPrule_015;
#else
_currn = (_TPPrule_015) TreeNodeAlloc (sizeof (struct _TPrule_015));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_015;
_SETCOORD(_currn)
_TERMACT_rule_015;
return ( (NODEPTR) _currn);
}/* Mkrule_015 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_014 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_014 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_014 _currn;
#ifdef __cplusplus
_currn = new _TPrule_014;
#else
_currn = (_TPPrule_014) TreeNodeAlloc (sizeof (struct _TPrule_014));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_014;
_currn->_desc1 = (_TSPLines) MkLines (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_014: root of subtree no. 1 can not be made a Lines node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_014;
return ( (NODEPTR) _currn);
}/* Mkrule_014 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_013 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_013 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_013 _currn;
#ifdef __cplusplus
_currn = new _TPrule_013;
#else
_currn = (_TPPrule_013) TreeNodeAlloc (sizeof (struct _TPrule_013));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_013;
_currn->_desc1 = (_TSPLineOpts) MkLineOpts (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_013: root of subtree no. 1 can not be made a LineOpts node ", 0, _coordref);
_currn->_desc2 = (_TSPLineOpt) MkLineOpt (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_013: root of subtree no. 2 can not be made a LineOpt node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_013;
return ( (NODEPTR) _currn);
}/* Mkrule_013 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_012 (POSITION *_coordref)
#else
NODEPTR Mkrule_012 (_coordref)
	POSITION *_coordref;
#endif
{	_TPPrule_012 _currn;
#ifdef __cplusplus
_currn = new _TPrule_012;
#else
_currn = (_TPPrule_012) TreeNodeAlloc (sizeof (struct _TPrule_012));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_012;
_SETCOORD(_currn)
_TERMACT_rule_012;
return ( (NODEPTR) _currn);
}/* Mkrule_012 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_011 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_011 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_011 _currn;
#ifdef __cplusplus
_currn = new _TPrule_011;
#else
_currn = (_TPPrule_011) TreeNodeAlloc (sizeof (struct _TPrule_011));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_011;
_currn->_desc1 = (_TSPThreshold) MkThreshold (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_011: root of subtree no. 1 can not be made a Threshold node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_011;
return ( (NODEPTR) _currn);
}/* Mkrule_011 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_010 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_010 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_010 _currn;
#ifdef __cplusplus
_currn = new _TPrule_010;
#else
_currn = (_TPPrule_010) TreeNodeAlloc (sizeof (struct _TPrule_010));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_010;
_currn->_desc1 = (_TSPPosition) MkPosition (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_010: root of subtree no. 1 can not be made a Position node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_010;
return ( (NODEPTR) _currn);
}/* Mkrule_010 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_09 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_09 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_09 _currn;
#ifdef __cplusplus
_currn = new _TPrule_09;
#else
_currn = (_TPPrule_09) TreeNodeAlloc (sizeof (struct _TPrule_09));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_09;
_currn->_desc1 = (_TSPGroupSpec) MkGroupSpec (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_09: root of subtree no. 1 can not be made a GroupSpec node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_09;
return ( (NODEPTR) _currn);
}/* Mkrule_09 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_08 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_08 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_08 _currn;
#ifdef __cplusplus
_currn = new _TPrule_08;
#else
_currn = (_TPPrule_08) TreeNodeAlloc (sizeof (struct _TPrule_08));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_08;
_currn->_desc1 = (_TSPFixLineParam) MkFixLineParam (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_08: root of subtree no. 1 can not be made a FixLineParam node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_08;
return ( (NODEPTR) _currn);
}/* Mkrule_08 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_07 (POSITION *_coordref, NODEPTR _desc1, NODEPTR _desc2)
#else
NODEPTR Mkrule_07 (_coordref,_desc1,_desc2)
	POSITION *_coordref;
	NODEPTR _desc1;
	NODEPTR _desc2;
#endif
{	_TPPrule_07 _currn;
#ifdef __cplusplus
_currn = new _TPrule_07;
#else
_currn = (_TPPrule_07) TreeNodeAlloc (sizeof (struct _TPrule_07));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_07;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_07: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_currn->_desc2 = (_TSPConfigLine) MkConfigLine (_coordref, _desc2);	
if (((NODEPTR)_currn->_desc2) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_07: root of subtree no. 2 can not be made a ConfigLine node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_07;
return ( (NODEPTR) _currn);
}/* Mkrule_07 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_06 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_06 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_06 _currn;
#ifdef __cplusplus
_currn = new _TPrule_06;
#else
_currn = (_TPPrule_06) TreeNodeAlloc (sizeof (struct _TPrule_06));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_06;
_currn->_desc1 = (_TSPConfigLine) MkConfigLine (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_06: root of subtree no. 1 can not be made a ConfigLine node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_06;
return ( (NODEPTR) _currn);
}/* Mkrule_06 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_05 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_05 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_05 _currn;
#ifdef __cplusplus
_currn = new _TPrule_05;
#else
_currn = (_TPPrule_05) TreeNodeAlloc (sizeof (struct _TPrule_05));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_05;
_currn->_desc1 = (_TSPConfigCmd) MkConfigCmd (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_05: root of subtree no. 1 can not be made a ConfigCmd node ", 0, _coordref);
_SETCOORD(_currn)
_TERMACT_rule_05;
return ( (NODEPTR) _currn);
}/* Mkrule_05 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_04 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_04 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_04 _currn;
#ifdef __cplusplus
_currn = new _TPrule_04;
#else
_currn = (_TPPrule_04) TreeNodeAlloc (sizeof (struct _TPrule_04));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_04;
_currn->_desc1 = (_TSPG1) MkG1 (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_04: root of subtree no. 1 can not be made a G1 node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_04;
return ( (NODEPTR) _currn);
}/* Mkrule_04 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_03 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_03 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_03 _currn;
#ifdef __cplusplus
_currn = new _TPrule_03;
#else
_currn = (_TPPrule_03) TreeNodeAlloc (sizeof (struct _TPrule_03));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_03;
_currn->_desc1 = (_TSPThreshold) MkThreshold (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_03: root of subtree no. 1 can not be made a Threshold node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_03;
return ( (NODEPTR) _currn);
}/* Mkrule_03 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_02 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_02 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_02 _currn;
#ifdef __cplusplus
_currn = new _TPrule_02;
#else
_currn = (_TPPrule_02) TreeNodeAlloc (sizeof (struct _TPrule_02));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_02;
_currn->_desc1 = (_TSPLinedef) MkLinedef (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_02: root of subtree no. 1 can not be made a Linedef node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_02;
return ( (NODEPTR) _currn);
}/* Mkrule_02 */

#if defined(__STDC__) || defined(__cplusplus)
NODEPTR Mkrule_01 (POSITION *_coordref, NODEPTR _desc1)
#else
NODEPTR Mkrule_01 (_coordref,_desc1)
	POSITION *_coordref;
	NODEPTR _desc1;
#endif
{	_TPPrule_01 _currn;
#ifdef __cplusplus
_currn = new _TPrule_01;
#else
_currn = (_TPPrule_01) TreeNodeAlloc (sizeof (struct _TPrule_01));
#endif
#ifdef MONITOR
_currn->_uid=MONTblStackSize; MONTblStackPush(((NODEPTR)_currn));
#endif
_currn->_prod = RULErule_01;
_currn->_desc1 = (_TSPFixLineParam) MkFixLineParam (_coordref, _desc1);	
if (((NODEPTR)_currn->_desc1) == NULLNODEPTR)	
	message (DEADLY, "RULE rule_01: root of subtree no. 1 can not be made a FixLineParam node ", 0, _coordref);
_COPYCOORD(_currn)
_TERMACT_rule_01;
return ( (NODEPTR) _currn);
}/* Mkrule_01 */
