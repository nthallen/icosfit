#include "gsdescr.h"
#include "treestack.h"
#include "HEAD.h"

#define TokenStack(i)	(ZAttributKeller[(i)])

#ifdef RIGHTCOORD
extern POSITION rightpos;
#endif

#if defined(__cplusplus) || defined(__STDC__) 
void
StrukturAnknuepfung(unsigned PR, GRUNDSYMBOLDESKRIPTOR *ZAttributKeller)
#else
void
StrukturAnknuepfung(PR, ZAttributKeller)
unsigned  PR;
register GRUNDSYMBOLDESKRIPTOR  *ZAttributKeller;
#endif
{
  curpos = ZAttributKeller->Pos;
#ifdef RIGHTCOORD
  RLineOf (curpos) = RLineOf (rightpos);
  RColOf (curpos) = RColOf (rightpos);
#ifdef MONITOR
  RCumColOf (curpos) = RCumColOf (rightpos);
#endif
#endif
  switch (PR) {
  case 1: _nst[_nsp]=Mkrule_01(&curpos, _nst[_nsp+0]); break;
  case 2: _nst[_nsp]=Mkrule_02(&curpos, _nst[_nsp+0]); break;
  case 3: _nst[_nsp]=Mkrule_03(&curpos, _nst[_nsp+0]); break;
  case 4: _nst[_nsp]=Mkrule_06(&curpos, _nst[_nsp+0]); break;
  case 5: _nsp -= 1;_nst[_nsp]=Mkrule_17(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 6: _nsp -= 1;_nst[_nsp]=Mkrule_07(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 7: _nst[_nsp]=Mkrule_67(&curpos, _nst[_nsp+0]); break;
  case 8: _nsp -= 1;_nst[_nsp]=Mkrule_65(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 9: _nst[_nsp]=Mkrule_66(&curpos, _nst[_nsp+0]); break;
  case 10: _nst[_nsp]=Mkrule_45(&curpos, _nst[_nsp+0]); break;
  case 11: _nst[_nsp]=Mkrule_60(&curpos, _nst[_nsp+0]); break;
  case 12: _nst[_nsp]=Mkrule_38(&curpos, _nst[_nsp+0]); break;
  case 13: _nst[_nsp]=Mkrule_54(&curpos, _nst[_nsp+0]); break;
  case 14: _nst[_nsp]=Mkrule_56(&curpos, _nst[_nsp+0]); break;
  case 15: _nst[_nsp]=Mkrule_25(&curpos, _nst[_nsp+0]); break;
  case 16: _nst[_nsp]=Mkrule_24(&curpos, _nst[_nsp+0]); break;
  case 17: _nst[_nsp]=Mkrule_59(&curpos, _nst[_nsp+0]); break;
  case 18: _nst[_nsp]=Mkrule_27(&curpos, _nst[_nsp+0]); break;
  case 19: _nst[_nsp]=Mkrule_26(&curpos, _nst[_nsp+0]); break;
  case 20: _nst[_nsp]=Mkrule_37(&curpos, _nst[_nsp+0]); break;
  case 21: _nst[_nsp]=Mkrule_36(&curpos, _nst[_nsp+0]); break;
  case 22: _nst[_nsp]=Mkrule_23(&curpos, _nst[_nsp+0]); break;
  case 23: _nst[_nsp]=Mkrule_52(&curpos, _nst[_nsp+0]); break;
  case 24: _nst[_nsp]=Mkrule_49(&curpos, _nst[_nsp+0]); break;
  case 25: _nst[_nsp]=Mkrule_19(&curpos, _nst[_nsp+0]); break;
  case 26: _nsp -= 1;_nst[_nsp]=Mkrule_28(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 27: _nst[_nsp]=Mkrule_70(&curpos, _nst[_nsp+0]); break;
  case 28: _nsp -= 1;_nst[_nsp]=Mkrule_50(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 29: _nsp -= 1;_nst[_nsp]=Mkrule_51(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 30: _nsp -= 1;_nst[_nsp]=Mkrule_61(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 31: _nsp -= 1;_nst[_nsp]=Mkrule_55(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 32: _nsp -= 1;_nst[_nsp]=Mkrule_57(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 33: _nsp -= 1;_nst[_nsp]=Mkrule_68(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 34: _nst[_nsp]=Mkrule_64(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2))), _nst[_nsp+0]); break;
  case 35: _nsp -= 1;_nst[_nsp]=Mkrule_53(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 36: _nsp -= 1;_nst[_nsp]=Mkrule_47(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 37: _nsp -= 1;_nst[_nsp]=Mkrule_46(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 38: _nsp -= 1;_nst[_nsp]=Mkrule_58(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 39: _nsp -= 1;_nst[_nsp]=Mkrule_48(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 40: _nsp -= 1;_nst[_nsp]=Mkrule_016(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 41: _nsp -= 1;_nst[_nsp]=Mkrule_028(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 42: _nst[_nsp]=Mkrule_09(&curpos, _nst[_nsp+0]); break;
  case 43: _nst[_nsp]=Mkrule_012(&curpos, _nst[_nsp+0]); break;
  case 44: _nst[_nsp]=Mkrule_010(&curpos, _nst[_nsp+0]); break;
  case 45: _nsp -= 1;_nst[_nsp]=Mkrule_014(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 46: _nst[_nsp]=Mkrule_011(&curpos, _nst[_nsp+0]); break;
  case 47: _incrnodestack();_nst[_nsp]=Mkrule_40(&curpos); break;
  case 48: _incrnodestack();_nst[_nsp]=Mkrule_41(&curpos); break;
  case 49: _incrnodestack();_nst[_nsp]=Mkrule_16(&curpos); break;
  case 50: _incrnodestack();_nst[_nsp]=Mkrule_15(&curpos); break;
  case 51: _incrnodestack();_nst[_nsp]=Mkrule_029(&curpos); break;
  case 52: _incrnodestack();_nst[_nsp]=Mkrule_030(&curpos); break;
  case 53: _incrnodestack();_nst[_nsp]=Mkrule_14(&curpos); break;
  case 54: _incrnodestack();_nst[_nsp]=Mkrule_12(&curpos); break;
  case 55: _incrnodestack();_nst[_nsp]=Mkrule_13(&curpos); break;
  case 56: _nst[_nsp]=Mkrule_05(&curpos, _nst[_nsp+0]); break;
  case 57: _nst[_nsp]=Mkrule_04(&curpos, _nst[_nsp+0]); break;
  case 59: _incrnodestack();_nst[_nsp]=Mkrule_025(&curpos, MkIdent(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 60: _incrnodestack();_nst[_nsp]=Mkrule_026(&curpos, MkPathStr(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 61: _incrnodestack();_nst[_nsp]=Mkrule_71(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 62: _incrnodestack();_nst[_nsp]=Mkrule_72(&curpos, MkFloat(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0)))); break;
  case 63: _incrnodestack();_nst[_nsp]=Mkrule_44(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 64: _incrnodestack();_nst[_nsp]=Mkrule_39(&curpos, MkIdent(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 65: _incrnodestack();_nst[_nsp]=Mkrule_43(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 66: _incrnodestack();_nst[_nsp]=Mkrule_20(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 67: _incrnodestack();_nst[_nsp]=Mkrule_42(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 68: _incrnodestack();_nst[_nsp]=Mkrule_21(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 69: _incrnodestack();_nst[_nsp]=Mkrule_22(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  case 70: _incrnodestack();_nst[_nsp]=Mkrule_015(&curpos); break;
  case 71: _incrnodestack();_nst[_nsp]=Mkrule_017(&curpos); break;
  case 72: _incrnodestack();_nst[_nsp]=Mkrule_018(&curpos); break;
  case 73: _incrnodestack();_nst[_nsp]=Mkrule_019(&curpos); break;
  case 74: _incrnodestack();_nst[_nsp]=Mkrule_023(&curpos); break;
  case 75: _incrnodestack();_nst[_nsp]=Mkrule_024(&curpos); break;
  case 76: _incrnodestack();_nst[_nsp]=Mkrule_10(&curpos); break;
  case 77: _incrnodestack();_nst[_nsp]=Mkrule_9(&curpos); break;
  case 78: _incrnodestack();_nst[_nsp]=Mkrule_8(&curpos); break;
  case 79: _incrnodestack();_nst[_nsp]=Mkrule_027(&curpos); break;
  case 80: _incrnodestack();_nst[_nsp]=Mkrule_020(&curpos); break;
  case 81: _incrnodestack();_nst[_nsp]=Mkrule_63(&curpos); break;
  case 82: _incrnodestack();_nst[_nsp]=Mkrule_7(&curpos); break;
  case 83: _incrnodestack();_nst[_nsp]=Mkrule_6(&curpos); break;
  case 84: _incrnodestack();_nst[_nsp]=Mkrule_5(&curpos); break;
  case 85: _incrnodestack();_nst[_nsp]=Mkrule_4(&curpos); break;
  case 86: _incrnodestack();_nst[_nsp]=Mkrule_021(&curpos); break;
  case 87: _nst[_nsp]=Mkrule_08(&curpos, _nst[_nsp+0]); break;
  case 88: _incrnodestack();_nst[_nsp]=Mkrule_3(&curpos); break;
  case 89: _nsp -= 1;_nst[_nsp]=Mkrule_35(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 90: _incrnodestack();_nst[_nsp]=Mkrule_32(&curpos); break;
  case 91: _incrnodestack();_nst[_nsp]=Mkrule_30(&curpos); break;
  case 92: _incrnodestack();_nst[_nsp]=Mkrule_33(&curpos); break;
  case 93: _incrnodestack();_nst[_nsp]=Mkrule_29(&curpos); break;
  case 94: _incrnodestack();_nst[_nsp]=Mkrule_31(&curpos); break;
  case 95: _incrnodestack();_nst[_nsp]=Mkrule_022(&curpos); break;
  case 96: _incrnodestack();_nst[_nsp]=Mkrule_69(&curpos, MkInteger(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))), MkInteger(&(T_POS(TokenStack(3))), T_ATTR(TokenStack(3)))); break;
  case 97: _nsp -= 1;_nst[_nsp]=Mkrule_62(&curpos, _nst[_nsp+0], _nst[_nsp+1]); break;
  case 98: _incrnodestack();_nst[_nsp]=Mkrule_013(&curpos); break;
  case 99: _nsp -= 6;_nst[_nsp]=Mkrule_11(&curpos, MkInteger(&(T_POS(TokenStack(0))), T_ATTR(TokenStack(0))), MkInteger(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))), _nst[_nsp+0], _nst[_nsp+1], _nst[_nsp+2], _nst[_nsp+3], _nst[_nsp+4], _nst[_nsp+5], MkInteger(&(T_POS(TokenStack(8))), T_ATTR(TokenStack(8))), _nst[_nsp+6]); break;
  case 100: _incrnodestack();_nst[_nsp]=Mkrule_1(&curpos, Mkrule_2(&(T_POS(TokenStack(1))), MkIdent(&(T_POS(TokenStack(1))), T_ATTR(TokenStack(1))))); break;
  case 101: _incrnodestack();_nst[_nsp]=Mkrule_18(&curpos, MkInteger(&(T_POS(TokenStack(2))), T_ATTR(TokenStack(2)))); break;
  } /* end switch */
}
