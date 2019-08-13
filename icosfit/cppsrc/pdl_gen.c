#include "pdl_gen.h"

#ifdef MONITOR
#include "pdl_dapto.h"
#endif

#define PRESENT find(key, _property, (Entry *)&_Item, 0)
#define VALUE (_Item->PropVal)

#define TYPE int

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct intElt))

typedef struct intElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *intProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getint (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getint (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  intProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setint (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setint (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetint (int _property, DefTableKey key, TYPE _val)
#else
void
Resetint (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  intProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Hasint (int _property, DefTableKey key)
#else
int
Hasint (_property, key)
int _property;
DefTableKey key;
#endif
{  intProperty _Item;
{
  return(PRESENT);
}
}

#undef ACCESS
#undef TYPE
#define TYPE double

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct doubleElt))

typedef struct doubleElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *doubleProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getdouble (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getdouble (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  doubleProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setdouble (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setdouble (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  doubleProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetdouble (int _property, DefTableKey key, TYPE _val)
#else
void
Resetdouble (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  doubleProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#if defined(__STDC__) || defined(__cplusplus)
int
Hasdouble (int _property, DefTableKey key)
#else
int
Hasdouble (_property, key)
int _property;
DefTableKey key;
#endif
{  doubleProperty _Item;
{
  return(PRESENT);
}
}

#undef ACCESS
#undef TYPE
#define TYPE func_parameter_p

#define ACCESS find(key, _property, (Entry *)&_Item, sizeof(struct func_parameter_pElt))

typedef struct func_parameter_pElt {
	Entry next;
	int selector;
	TYPE PropVal;
} *func_parameter_pProperty;

#if defined(__STDC__) || defined(__cplusplus)
TYPE
Getfunc_parameter_p (int _property, DefTableKey key, TYPE deflt)
#else
TYPE
Getfunc_parameter_p (_property, key, deflt)
int _property;
DefTableKey key;
TYPE deflt;
#endif
{  func_parameter_pProperty _Item;
{ if (key == NoKey) return deflt;
  if (PRESENT) return VALUE;
  else return deflt;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Setfunc_parameter_p (int _property, DefTableKey key, TYPE _add, TYPE _replace)
#else
void
Setfunc_parameter_p (_property, key, _add, _replace)
int _property;
DefTableKey key;
TYPE _add;
TYPE _replace;
#endif
{  func_parameter_pProperty _Item;
{ if (key == NoKey) return;
  if (ACCESS) VALUE = _replace;
  else VALUE = _add;
}
}

#if defined(__STDC__) || defined(__cplusplus)
void
Resetfunc_parameter_p (int _property, DefTableKey key, TYPE _val)
#else
void
Resetfunc_parameter_p (_property, key, _val)
int _property;
DefTableKey key;
TYPE _val;
#endif
{  func_parameter_pProperty _Item;
{ if (key == NoKey) return;
  ACCESS; VALUE = _val;
}
}

#undef ACCESS
#undef TYPE

static struct PropElt PDLe0 = {(Entry)0, 0};

DefTableKey
#if defined(__STDC__) || defined(__cplusplus)
CloneKey (DefTableKey key)
#else
CloneKey (key)
    DefTableKey key;
#endif
{
  DefTableKey k;
  Entry e;

  if (key == NoKey) return NoKey;
  k = NewKey ();
  for (e = key->List; (e != (Entry)0) && (e->selector != 0);
       e = e->next) {
    switch (e->selector) {
      case 1:
         ResetClpValue (k, ((intProperty)e)->PropVal);
         break;
      case 2:
         ResetThreshold (k, ((doubleProperty)e)->PropVal);
         break;
      case 3:
         ResetPosition (k, ((intProperty)e)->PropVal);
         break;
      case 4:
         ResetFixDoppler (k, ((intProperty)e)->PropVal);
         break;
      case 5:
         ResetFixLorentz (k, ((intProperty)e)->PropVal);
         break;
      case 6:
         ResetFixFinePosition (k, ((intProperty)e)->PropVal);
         break;
      case 7:
         ResetNparameter (k, ((func_parameter_pProperty)e)->PropVal);
         break;
      case 8:
         ResetGroupRefUnique (k, ((intProperty)e)->PropVal);
         break;
      }
  }
  return k;
}

#ifdef MONITOR
static CONST char *pdl_names[] = {
    (char *)0,
    "ClpValue",
    "Threshold",
    "Position",
    "FixDoppler",
    "FixLorentz",
    "FixFinePosition",
    "Nparameter",
    "GroupRefUnique",
};
static CONST char *pdl_types[] = {
    (char *)0,
    "int",
    "double",
    "int",
    "int",
    "int",
    "int",
    "func_parameter_p",
    "int",
};

void
#if defined(__STDC__) || defined(__cplusplus)
pdl_mon_properties(DefTableKey k)
#else
pdl_mon_properties(k) DefTableKey k;
#endif
{
    Entry e;
    if (k == NoKey) return;
    for (e = k->List; (e != (Entry)0) && (e->selector != 0);
         e = e->next) {
        DAPTO_RESULT_STR (pdl_names[e->selector]);
        DAPTO_RESULT_STR (pdl_types[e->selector]);
        switch (e->selector) {
            case 1:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 2:
#ifdef DAPTO_RESULTdouble
                DAPTO_RESULTdouble (((doubleProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((doubleProperty)e)->PropVal);
#endif
                break;
            case 3:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 4:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 5:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 6:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            case 7:
#ifdef DAPTO_RESULTfunc_parameter_p
                DAPTO_RESULTfunc_parameter_p (((func_parameter_pProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((func_parameter_pProperty)e)->PropVal);
#endif
                break;
            case 8:
#ifdef DAPTO_RESULTint
                DAPTO_RESULTint (((intProperty)e)->PropVal);
#else
                DAPTO_RESULT_OTHER (((intProperty)e)->PropVal);
#endif
                break;
            default: DAPTO_RESULT_STR ("unknown property");
        }
    }
}
#endif
