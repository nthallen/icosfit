#ifndef PDL_GEN_H
#define PDL_GEN_H

#include "deftbl.h"

#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

#include "funceval.h"

#define TYPE int
extern TYPE Getint ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setint ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetint ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern int Hasint ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE double
extern TYPE Getdouble ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setdouble ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetdouble ELI_ARG((int _Property, DefTableKey key, TYPE _val));
extern int Hasdouble ELI_ARG((int _Property, DefTableKey key));
#undef TYPE
#define TYPE func_parameter_p
extern TYPE Getfunc_parameter_p ELI_ARG((int _Property, DefTableKey key, TYPE deflt));
extern void Setfunc_parameter_p ELI_ARG((int _Property, DefTableKey key, TYPE _add, TYPE _replace));
extern void Resetfunc_parameter_p ELI_ARG((int _Property, DefTableKey key, TYPE _val));
#undef TYPE

#define SetClpValue(key, _add, _replace)   \
		Setint(1, (key), (_add), (_replace))
#define ResetClpValue(key, _val)   \
		Resetint(1, (key), (_val))
#define GetClpValue(key, deflt)   \
		Getint(1, (key), (deflt))
#define HasThreshold(key)   \
		Hasdouble(2, (key))
#define SetThreshold(key, _add, _replace)   \
		Setdouble(2, (key), (_add), (_replace))
#define ResetThreshold(key, _val)   \
		Resetdouble(2, (key), (_val))
#define GetThreshold(key, deflt)   \
		Getdouble(2, (key), (deflt))
#define HasPosition(key)   \
		Hasint(3, (key))
#define SetPosition(key, _add, _replace)   \
		Setint(3, (key), (_add), (_replace))
#define ResetPosition(key, _val)   \
		Resetint(3, (key), (_val))
#define GetPosition(key, deflt)   \
		Getint(3, (key), (deflt))
#define HasFixDoppler(key)   \
		Hasint(4, (key))
#define SetFixDoppler(key, _add, _replace)   \
		Setint(4, (key), (_add), (_replace))
#define ResetFixDoppler(key, _val)   \
		Resetint(4, (key), (_val))
#define GetFixDoppler(key, deflt)   \
		Getint(4, (key), (deflt))
#define HasFixLorentz(key)   \
		Hasint(5, (key))
#define SetFixLorentz(key, _add, _replace)   \
		Setint(5, (key), (_add), (_replace))
#define ResetFixLorentz(key, _val)   \
		Resetint(5, (key), (_val))
#define GetFixLorentz(key, deflt)   \
		Getint(5, (key), (deflt))
#define HasFixFinePosition(key)   \
		Hasint(6, (key))
#define SetFixFinePosition(key, _add, _replace)   \
		Setint(6, (key), (_add), (_replace))
#define ResetFixFinePosition(key, _val)   \
		Resetint(6, (key), (_val))
#define GetFixFinePosition(key, deflt)   \
		Getint(6, (key), (deflt))
#define SetNparameter(key, _add, _replace)   \
		Setfunc_parameter_p(7, (key), (_add), (_replace))
#define ResetNparameter(key, _val)   \
		Resetfunc_parameter_p(7, (key), (_val))
#define GetNparameter(key, deflt)   \
		Getfunc_parameter_p(7, (key), (deflt))
#define SetGroupRefUnique(key, _add, _replace)   \
		Setint(8, (key), (_add), (_replace))
#define ResetGroupRefUnique(key, _val)   \
		Resetint(8, (key), (_val))
#define GetGroupRefUnique(key, deflt)   \
		Getint(8, (key), (deflt))

extern struct PropList PDLk[];


extern DefTableKey CloneKey ELI_ARG((DefTableKey key));
/* Clone a definition
 *    On entry-
 *       key=a valid definition
 *    On exit-
 *       CloneKey=Unique definition with the same properties
 *                and property values as key
 ***/

#ifdef MONITOR
extern void pdl_mon_properties ELI_ARG((DefTableKey));
#endif

#endif
