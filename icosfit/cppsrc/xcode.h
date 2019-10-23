switch (CaseTbl[c = *p++]) {
case 0:	/* sentinel - probably EOB */
  if (c == '\0') {
    p = TokenStart = TokenEnd = auxNUL(TokenStart, 0);
    if (*p) extcode = NORETURN;
    else {
      p = TokenStart = TokenEnd = auxEOF(TokenStart, 0);
      if (*p) extcode = NORETURN;
      else { extcode = EOFTOKEN; EndOfText(p, 0, &extcode, v); }
    }
    goto done;
  } else {
    obstack_grow(Csm_obstk, "char '", 6);
    obstack_cchgrow(Csm_obstk, c);
    message(
      ERROR,
      (char *)obstack_copy0(Csm_obstk, "' is not a token", 16),
      0,
      &curpos);
    TokenEnd = p;
    continue;
  }
  
case 1:	/* space */
  while (scanTbl[c = *p++] & 1<<0) ;
  TokenEnd = p - 1;
  continue;
case 2:	/* tab */
  do { StartLine -= TABSIZE(p - StartLine); }
  while (scanTbl[c = *p++] & 1<<1);
  TokenEnd = p - 1;
  continue;
case 4:	/* carriage return */
  if (*p == '\n') { TokenEnd = p; continue; }
case 3:	/* newline */
  do { LineNum++; } while (scanTbl[c = *p++] & 1<<2);
  StartLine = (TokenEnd = p - 1) - 1;
  continue;

case 5:	/* Entered on:  J-K U W-Z b d f-j l o q-r t-z */
	St_24:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 6:	/* Entered on: 1-9 */
	St_12:
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  - / A-D F-Z _ a-d f-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_51;}
		else if( scanTbl[c+0] & 1<< 7){ /*  E e */
			goto St_52;}
		else if(c ==46) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 7:	/* Entered on: s */
	St_44:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_104;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 8:	/* Entered on: p */
	St_43:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_103;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 9:	/* Entered on: n */
	St_42:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_102;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 10:	/* Entered on: m */
	St_41:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_101;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 11:	/* Entered on: k */
	St_40:
		if( scanTbl[(c= *p++)+256] & 1<< 3){ /*  0-9 A-G I-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==72) {			goto St_100;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 12:	/* Entered on: e */
	St_39:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_99;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 13:	/* Entered on: c */
	St_38:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_98;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 14:	/* Entered on: a */
	St_37:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_97;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 15:	/* Entered on: V */
	St_34:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_96;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 16:	/* Entered on: T */
	St_33:
		if( scanTbl[(c= *p++)+256] & 1<< 7){ /*  0-9 A-Z _ a-g i-n p-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_95;}
		else if(c ==111) {			goto St_94;}
		else if(c ==104) {			goto St_93;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 17:	/* Entered on: S */
	St_32:
		if( scanTbl[(c= *p++)+512] & 1<< 0){ /*  0-9 A-Z _ b d-h j l-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==107) {			goto St_92;}
		else if(c ==105) {			goto St_91;}
		else if(c ==99) {			goto St_90;}
		else if(c ==97) {			goto St_89;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 18:	/* Entered on: R */
	St_31:
		if( scanTbl[(c= *p++)+512] & 1<< 1){ /*  0-9 A-Z _ a-d f-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_88;}
		else if(c ==101) {			goto St_87;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 19:	/* Entered on: Q */
	St_30:
		if( scanTbl[(c= *p++)+512] & 1<< 2){ /*  0-9 A-B D-S U-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==84) {			goto St_86;}
		else if(c ==67) {			goto St_85;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 20:	/* Entered on: P */
	St_29:
		if( scanTbl[(c= *p++)+512] & 1<< 3){ /*  0-9 A-S U-Z _ b-k m-n p-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_84;}
		else if(c ==111) {			goto St_83;}
		else if(c ==108) {			goto St_82;}
		else if(c ==97) {			goto St_81;}
		else if(c ==84) {			goto St_80;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 21:	/* Entered on: O */
	St_28:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_79;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 22:	/* Entered on: N */
	St_27:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Z a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==95) {			goto St_78;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 23:	/* Entered on: M */
	St_26:
		if( scanTbl[(c= *p++)+512] & 1<< 5){ /*  0-9 A-E G I-Z _ b-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_77;}
		else if(c ==97) {			goto St_76;}
		else if(c ==72) {			goto St_75;}
		else if(c ==70) {			goto St_74;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 24:	/* Entered on: L */
	St_25:
		if( scanTbl[(c= *p++)+512] & 1<< 6){ /*  0-9 A-Z _ a-d f-h j-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_73;}
		else if(c ==105) {			goto St_72;}
		else if(c ==101) {			goto St_71;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 25:	/* Entered on: I */
	St_23:
		if( scanTbl[(c= *p++)+512] & 1<< 7){ /*  0-9 A-B D-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_70;}
		else if(c ==67) {			goto St_69;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 26:	/* Entered on: H */
	St_22:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-Z _ a-y */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==122) {			goto St_68;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 27:	/* Entered on: G */
	St_21:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_67;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 28:	/* Entered on: F */
	St_20:
		if( scanTbl[(c= *p++)+768] & 1<< 2){ /*  0-9 A-Z _ a-d f-h j-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_66;}
		else if(c ==105) {			goto St_65;}
		else if(c ==101) {			goto St_64;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 29:	/* Entered on: E */
	St_19:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_63;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 30:	/* Entered on: D */
	St_18:
		if( scanTbl[(c= *p++)+768] & 1<< 3){ /*  0-9 A-R T-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_62;}
		else if(c ==83) {			goto St_61;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 31:	/* Entered on: C */
	St_17:
		if( scanTbl[(c= *p++)+768] & 1<< 4){ /*  0-9 A-O Q-Z _ b-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_60;}
		else if(c ==97) {			goto St_59;}
		else if(c ==80) {			goto St_58;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 32:	/* Entered on: B */
	St_16:
		if( scanTbl[(c= *p++)+768] & 1<< 5){ /*  0-9 A-Z _ b-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_57;}
		else if(c ==97) {			goto St_56;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 33:	/* Entered on: A */
	St_15:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-R T-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==83) {			goto St_55;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 34:	/* Entered on: 0 */
	St_11:
		if( scanTbl[(c= *p++)+768] & 1<< 7){ /*  - / A-D F-W Y-Z _ a-d f-w y-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_51;}
		else if( scanTbl[c+1024] & 1<< 0){ /*  X x */
			goto St_53;}
		else if( scanTbl[c+0] & 1<< 7){ /*  E e */
			goto St_52;}
		else if(c ==46) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}

case 35:	/* Entered on: / */
	St_10:
		if( scanTbl[(c= *p++)+1024] & 1<< 1){ /*  --9 A-Z _ a-z */
			goto St_47;}
		else if(c ==42) {			goto St_49;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 75;
			goto done;
			}

case 36:	/* Entered on: . */
	St_9:
		if( scanTbl[(c= *p++)+1024] & 1<< 2){ /*  --/ A-Z _ a-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_48;}
		else {TokenEnd=TokenStart;--p; goto fallback; }

case 37:	/* Entered on: # */
	St_4:
			TokenEnd=p=auxEOL(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;


default: TokenEnd=p; extcode=ExtCodeTbl[c]; goto done; /*  % +-- ; = [ ] { } */
}
	St_48:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 3){ /*  --/ A-D G-K M-Z _ a-d g-k m-z */
			goto St_47;}
		else if( scanTbl[c+1024] & 1<< 4){ /*  F L f l */
			goto St_106;}
		else if( scanTbl[c+0] & 1<< 7){ /*  E e */
			goto St_105;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_105:
		if( scanTbl[(c= *p++)+1024] & 1<< 5){ /*  .-/ A-Z _ a-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_170;}
		else if(c ==45) {			goto St_169;}
		else if(c ==43) {		extcode = 77;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = mkidn;
			goto St_168;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 77;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_168:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 */
			goto St_224;}
		else {--p; goto fallback; }
	St_224:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 4){ /*  F L f l */
			goto St_225;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_225:
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_169:
		if( scanTbl[(c= *p++)+1024] & 1<< 2){ /*  --/ A-Z _ a-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_170;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 77;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_170:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 6){ /*  --/ A-E G-K M-Z _ a-e g-k m-z */
			goto St_47;}
		else if( scanTbl[c+1024] & 1<< 4){ /*  F L f l */
			goto St_106;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_106:
		if( scanTbl[(c= *p++)+1024] & 1<< 1){ /*  --9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_47:
		/*  --9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+1024] & 1<< 1);--p;
			TokenEnd= p; /* FINAL, no auxscan, must set */
			extcode = 77;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
	St_49:
			TokenEnd=p=auxCComment(TokenStart, p-TokenStart);
			extcode = 15001;
			goto done;
	St_50:
		if( scanTbl[(c= *p++)+1024] & 1<< 3){ /*  --/ A-D G-K M-Z _ a-d g-k m-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_107;}
		else if( scanTbl[c+1024] & 1<< 4){ /*  F L f l */
			goto St_106;}
		else if( scanTbl[c+0] & 1<< 7){ /*  E e */
			goto St_105;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_107:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 3){ /*  --/ A-D G-K M-Z _ a-d g-k m-z */
			goto St_47;}
		else if( scanTbl[c+1024] & 1<< 4){ /*  F L f l */
			goto St_106;}
		else if( scanTbl[c+0] & 1<< 7){ /*  E e */
			goto St_105;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_52:
		if( scanTbl[(c= *p++)+1024] & 1<< 5){ /*  .-/ A-Z _ a-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_110;}
		else if(c ==45) {			goto St_109;}
		else if(c ==43) {		extcode = 77;/* remember fallback*/
		TokenEnd = p-1;

		scan = NULL;
		proc = mkidn;
			goto St_108;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 77;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_108:
		if( scanTbl[(c= *p++)+0] & 1<< 6){ /*  0-9 */
			goto St_171;}
		else {--p; goto fallback; }
	St_171:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 4){ /*  F L f l */
			goto St_225;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_109:
		if( scanTbl[(c= *p++)+1024] & 1<< 2){ /*  --/ A-Z _ a-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 6){ /*  0-9 */
			goto St_110;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 77;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_110:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 6){ /*  --/ A-E G-K M-Z _ a-e g-k m-z */
			goto St_47;}
		else if( scanTbl[c+1024] & 1<< 4){ /*  F L f l */
			goto St_106;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 57;
			mkstr(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_53:
		if( scanTbl[(c= *p++)+1024] & 1<< 7){ /*  --/ G-Z _ g-z */
			goto St_47;}
		else if( scanTbl[c+1280] & 1<< 0){ /*  0-9 A-F a-f */
			goto St_111;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_111:
		/*  0-9 A-F a-f*/
		while(scanTbl[(c= *p++)+1280] & 1<< 0);--p;
		if( scanTbl[(c= *p++)+1024] & 1<< 7){ /*  --/ G-Z _ g-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_51:
		/*  0-9*/
		while(scanTbl[(c= *p++)+0] & 1<< 6);--p;
		if( scanTbl[(c= *p++)+0] & 1<< 5){ /*  - / A-D F-Z _ a-d f-z */
			goto St_47;}
		else if( scanTbl[c+0] & 1<< 7){ /*  E e */
			goto St_52;}
		else if(c ==46) {			goto St_50;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 10;
			c_mkint(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_55:
		if( scanTbl[(c= *p++)+1280] & 1<< 1){ /*  0-9 A-B D-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==67) {			goto St_112;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_112:
		if( scanTbl[(c= *p++)+1280] & 1<< 2){ /*  0-9 A-H J-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==73) {			goto St_172;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_172:
		if( scanTbl[(c= *p++)+1280] & 1<< 2){ /*  0-9 A-H J-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==73) {			goto St_226;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_226:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 2;
			goto done;
			}
	St_54:
		/*  0-9 A-Z _ a-z*/
		while(scanTbl[(c= *p++)+0] & 1<< 3);--p;
		if( scanTbl[(c= *p++)+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_56:
		if( scanTbl[(c= *p++)+1280] & 1<< 3){ /*  0-9 A-Z _ a-b d-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_114;}
		else if(c ==99) {			goto St_113;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_113:
		if( scanTbl[(c= *p++)+1280] & 1<< 4){ /*  0-9 A-Z _ a-j l-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==107) {			goto St_173;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_173:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_227;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_227:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_278;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_278:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_321;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_321:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_363;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_363:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_402;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_402:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_434;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_434:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_460;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_460:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_481;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_481:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_499;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_499:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_512;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_512:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_523;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_523:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_531;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_531:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 3;
			goto done;
			}
	St_114:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_174;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_174:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_228;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_228:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_279;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_279:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_322;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_322:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_364;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_364:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_403;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_403:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_435;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_435:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_461;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_461:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_482;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_482:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 5;
			goto done;
			}
	St_57:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_115;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_115:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_175;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_175:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_229;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_229:
		if( scanTbl[(c= *p++)+1536] & 1<< 5){ /*  0-9 A-Z _ a-x z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==121) {			goto St_280;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_280:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 6;
			goto done;
			}
	St_58:
		if( scanTbl[(c= *p++)+1280] & 1<< 1){ /*  0-9 A-B D-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==67) {			goto St_116;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_116:
		if( scanTbl[(c= *p++)+1280] & 1<< 2){ /*  0-9 A-H J-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==73) {			goto St_176;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_176:
		if( scanTbl[(c= *p++)+1536] & 1<< 6){ /*  0 2-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==49) {			goto St_230;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_230:
		if( scanTbl[(c= *p++)+1536] & 1<< 7){ /*  0-3 5-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==52) {			goto St_281;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_281:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_323;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_323:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_365;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_365:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_404;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_404:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_436;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_436:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_462;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_462:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 83;
			goto done;
			}
	St_59:
		if( scanTbl[(c= *p++)+1792] & 1<< 0){ /*  0-9 A-Z _ a-u w-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==118) {			goto St_117;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_117:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_177;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_177:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_231;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_231:
		if( scanTbl[(c= *p++)+1536] & 1<< 5){ /*  0-9 A-Z _ a-x z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==121) {			goto St_282;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_282:
		if( scanTbl[(c= *p++)+1792] & 1<< 1){ /*  0-9 A-E G-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_325;}
		else if(c ==70) {			goto St_324;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_324:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_366;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_366:
		if( scanTbl[(c= *p++)+1792] & 1<< 2){ /*  0-9 A-Z _ a-w y-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==120) {			goto St_405;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_405:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_437;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_437:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_463;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_463:
		if( scanTbl[(c= *p++)+1792] & 1<< 3){ /*  0-9 A-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_483;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_483:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_500;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_500:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_513;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_513:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_524;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_524:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_532;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_532:
		if( scanTbl[(c= *p++)+1792] & 1<< 4){ /*  0-9 A-Z _ a-g i-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==104) {			goto St_538;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_538:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 7;
			goto done;
			}
	St_325:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_367;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_367:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_406;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_406:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_438;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_438:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_464;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_464:
		if( scanTbl[(c= *p++)+1792] & 1<< 4){ /*  0-9 A-Z _ a-g i-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==104) {			goto St_484;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_484:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 8;
			goto done;
			}
	St_60:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_118;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_118:
		if( scanTbl[(c= *p++)+1792] & 1<< 0){ /*  0-9 A-Z _ a-u w-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==118) {			goto St_178;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_178:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_232;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_232:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_283;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_283:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_326;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_326:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_368;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_368:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_407;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_407:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_439;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_439:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_465;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_465:
		if( scanTbl[(c= *p++)+1792] & 1<< 6){ /*  0-9 A-B D-R T-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==83) {			goto St_486;}
		else if(c ==67) {			goto St_485;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_485:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_501;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_501:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_514;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_514:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_525;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_525:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_533;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_533:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 9;
			goto done;
			}
	St_486:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_502;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_502:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_515;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_515:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_526;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_526:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 11;
			goto done;
			}
	St_61:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_119;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_119:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_179;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_179:
		if( scanTbl[(c= *p++)+1792] & 1<< 3){ /*  0-9 A-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_233;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_233:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_284;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_284:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_327;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_327:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_369;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_369:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_408;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_408:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_440;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_440:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 12;
			goto done;
			}
	St_62:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_120;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_120:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_180;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_180:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_234;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_234:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_285;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_285:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_328;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_328:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 65;
			goto done;
			}
	St_63:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_121;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_121:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_181;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_181:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_235;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_235:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_286;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_286:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_329;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_329:
		if( scanTbl[(c= *p++)+2048] & 1<< 0){ /*  0-9 A-R T-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_371;}
		else if(c ==83) {			goto St_370;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_370:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_409;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_409:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 20;
			goto done;
			}
	St_371:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_410;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_410:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_441;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_441:
		if( scanTbl[(c= *p++)+2048] & 1<< 1){ /*  0-9 A-Z _ a c-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==98) {			goto St_466;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_466:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_487;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_487:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_503;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_503:
		if( scanTbl[(c= *p++)+1280] & 1<< 4){ /*  0-9 A-Z _ a-j l-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==107) {			goto St_516;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_516:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 19;
			goto done;
			}
	St_64:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_122;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_122:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_182;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_182:
		if( scanTbl[(c= *p++)+2048] & 1<< 1){ /*  0-9 A-Z _ a c-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==98) {			goto St_236;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_236:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_287;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_287:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_330;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_330:
		if( scanTbl[(c= *p++)+1280] & 1<< 4){ /*  0-9 A-Z _ a-j l-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==107) {			goto St_372;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_372:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 79;
			goto done;
			}
	St_65:
		if( scanTbl[(c= *p++)+2048] & 1<< 2){ /*  0-9 A-Z _ a-m o-s u-w y-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==120) {			goto St_125;}
		else if(c ==116) {			goto St_124;}
		else if(c ==110) {			goto St_123;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_123:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_183;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_183:
		if( scanTbl[(c= *p++)+2048] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==80) {			goto St_237;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_237:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_288;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_288:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_331;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_331:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_373;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_373:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_411;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_411:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_442;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_442:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_467;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_467:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_488;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_488:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 66;
			goto done;
			}
	St_124:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_184;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_184:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_238;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_238:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_289;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_289:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_332;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_332:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_374;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_374:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_412;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_412:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_443;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_443:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_468;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_468:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 21;
			goto done;
			}
	St_125:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 54;
			goto done;
			}
	St_66:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_126;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_126:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_185;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_185:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_239;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_239:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 55;
			goto done;
			}
	St_67:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_127;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_127:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_186;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_186:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_240;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_240:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 61;
			goto done;
			}
	St_68:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 58;
			goto done;
			}
	St_69:
		if( scanTbl[(c= *p++)+2048] & 1<< 4){ /*  0-9 A-N P-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==79) {			goto St_128;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_128:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-R T-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==83) {			goto St_187;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_187:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_241;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_241:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_290;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_290:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_333;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_333:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 23;
			goto done;
			}
	St_70:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_129;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_129:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_188;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_188:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_242;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_242:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 69;
			goto done;
			}
	St_71:
		if( scanTbl[(c= *p++)+2048] & 1<< 5){ /*  0-9 A-Z _ a-e g-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==102) {			goto St_130;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_130:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_189;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_189:
		if( scanTbl[(c= *p++)+1792] & 1<< 3){ /*  0-9 A-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_243;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_243:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_291;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_291:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_334;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_334:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_375;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_375:
		if( scanTbl[(c= *p++)+2048] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==77) {			goto St_413;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_413:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_444;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_444:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_469;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_469:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_489;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_489:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_504;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_504:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_517;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_517:
		if( scanTbl[(c= *p++)+2048] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==77) {			goto St_527;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 24;
			goto done;
			}
	St_527:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_534;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_534:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_539;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_539:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_543;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_543:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_547;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_547:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_551;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_551:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_555;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_555:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_557;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_557:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_559;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_559:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_561;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_561:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 25;
			goto done;
			}
	St_72:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_131;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_131:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_190;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_190:
		if( scanTbl[(c= *p++)+2048] & 1<< 7){ /*  0-9 A-L N-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_245;}
		else if(c ==77) {			goto St_244;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_244:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_292;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_292:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_335;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_335:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_376;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_376:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_414;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_414:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_445;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_445:
		if( scanTbl[(c= *p++)+2048] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==77) {			goto St_470;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 26;
			goto done;
			}
	St_470:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_490;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_490:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_505;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_505:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_518;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_518:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_528;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_528:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_535;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_535:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_540;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_540:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_544;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_544:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_548;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_548:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_552;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_552:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 27;
			goto done;
			}
	St_245:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 62;
			goto done;
			}
	St_73:
		if( scanTbl[(c= *p++)+2304] & 1<< 0){ /*  0-9 A-Z _ a-f h-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_133;}
		else if(c ==103) {			goto St_132;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_132:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_191;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_191:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_246;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_246:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_293;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_293:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_336;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_336:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 28;
			goto done;
			}
	St_133:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_192;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_192:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_247;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_247:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_294;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_294:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-Z _ a-y */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==122) {			goto St_337;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_337:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 67;
			goto done;
			}
	St_74:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_134;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_134:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_193;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_193:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_248;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_248:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 30;
			goto done;
			}
	St_75:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-Z _ a-y */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==122) {			goto St_135;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_135:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 60;
			goto done;
			}
	St_76:
		if( scanTbl[(c= *p++)+1792] & 1<< 2){ /*  0-9 A-Z _ a-w y-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==120) {			goto St_136;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_136:
		if( scanTbl[(c= *p++)+1280] & 1<< 2){ /*  0-9 A-H J-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==73) {			goto St_194;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_194:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_249;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_249:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_295;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_295:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_338;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_338:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_377;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_377:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_415;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_415:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_446;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_446:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_471;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_471:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_491;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_491:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_506;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_506:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 29;
			goto done;
			}
	St_77:
		if( scanTbl[(c= *p++)+2304] & 1<< 1){ /*  0-9 A-Z _ a-m o-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_138;}
		else if(c ==110) {			goto St_137;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_137:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_195;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_195:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_250;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_250:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_296;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_296:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_339;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_339:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_378;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_378:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_416;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_416:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_447;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_447:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_472;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_472:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_492;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_492:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_507;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_507:
		if( scanTbl[(c= *p++)+768] & 1<< 6){ /*  0-9 A-R T-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==83) {			goto St_519;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_519:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_529;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_529:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_536;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_536:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_541;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_541:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_545;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_545:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_549;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_549:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_553;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_553:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 31;
			goto done;
			}
	St_138:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_196;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_196:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_251;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_251:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_297;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_297:
		if( scanTbl[(c= *p++)+1792] & 1<< 3){ /*  0-9 A-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_340;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_340:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_379;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_379:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_417;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_417:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_448;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_448:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 32;
			goto done;
			}
	St_78:
		if( scanTbl[(c= *p++)+2048] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==80) {			goto St_139;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_139:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_197;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_197:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_252;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_252:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_298;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_298:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_341;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_341:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_380;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_380:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 34;
			goto done;
			}
	St_79:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_140;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_140:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_198;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_198:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_253;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_253:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_299;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_299:
		if( scanTbl[(c= *p++)+2304] & 1<< 2){ /*  0-9 A-C E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_343;}
		else if(c ==68) {			goto St_342;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_342:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_381;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_381:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_418;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_418:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 36;
			goto done;
			}
	St_343:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_382;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_382:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_419;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_419:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_449;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_449:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 37;
			goto done;
			}
	St_80:
		if( scanTbl[(c= *p++)+2304] & 1<< 3){ /*  0-9 A-D G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_142;}
		else if(c ==69) {			goto St_141;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_141:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_199;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_199:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_254;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_254:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_300;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_300:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_344;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_344:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 39;
			goto done;
			}
	St_142:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_200;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_200:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_255;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_255:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_301;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_301:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 40;
			goto done;
			}
	St_81:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_143;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_143:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_201;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_201:
		if( scanTbl[(c= *p++)+2304] & 1<< 4){ /*  0-9 A-S U-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==84) {			goto St_256;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_256:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_302;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_302:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_345;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_345:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_383;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_383:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_420;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_420:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 38;
			goto done;
			}
	St_82:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_144;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_144:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_202;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_202:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_257;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_257:
		if( scanTbl[(c= *p++)+1792] & 1<< 4){ /*  0-9 A-Z _ a-g i-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==104) {			goto St_303;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_303:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_346;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_346:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_384;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_384:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_421;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_421:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_450;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_450:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_473;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_473:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 81;
			goto done;
			}
	St_83:
		if( scanTbl[(c= *p++)+2304] & 1<< 5){ /*  0-9 A-Z _ a-r t-v x-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==119) {			goto St_146;}
		else if(c ==115) {			goto St_145;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_145:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_203;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_203:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_258;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_258:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_304;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_304:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_347;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_347:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_385;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_385:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 78;
			goto done;
			}
	St_146:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_204;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_204:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_259;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_259:
		if( scanTbl[(c= *p++)+2048] & 1<< 3){ /*  0-9 A-O Q-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==80) {			goto St_305;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_305:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_348;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_348:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_386;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_386:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_422;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_422:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_451;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_451:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_474;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_474:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 82;
			goto done;
			}
	St_84:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_147;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_147:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_205;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_205:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_260;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_260:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_306;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_306:
		if( scanTbl[(c= *p++)+1792] & 1<< 0){ /*  0-9 A-Z _ a-u w-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==118) {			goto St_349;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_349:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_387;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_387:
		if( scanTbl[(c= *p++)+2048] & 1<< 4){ /*  0-9 A-N P-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==79) {			goto St_423;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_423:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_452;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_452:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_475;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_475:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_493;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_493:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_508;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_508:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_520;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_520:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 73;
			goto done;
			}
	St_85:
		if( scanTbl[(c= *p++)+1792] & 1<< 3){ /*  0-9 A-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_148;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_148:
		if( scanTbl[(c= *p++)+1280] & 1<< 2){ /*  0-9 A-H J-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==73) {			goto St_206;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_206:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Z a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==95) {			goto St_261;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_261:
		if( scanTbl[(c= *p++)+2304] & 1<< 6){ /*  0-9 A-V X-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==87) {			goto St_307;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_307:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_350;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_350:
		if( scanTbl[(c= *p++)+1792] & 1<< 0){ /*  0-9 A-Z _ a-u w-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==118) {			goto St_388;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_388:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_424;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_424:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 41;
			goto done;
			}
	St_86:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_149;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_149:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_207;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_207:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_262;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_262:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 42;
			goto done;
			}
	St_87:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_150;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_150:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_208;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_208:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_263;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_263:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_308;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_308:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_351;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_351:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 43;
			goto done;
			}
	St_88:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_151;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_151:
		if( scanTbl[(c= *p++)+1792] & 1<< 4){ /*  0-9 A-Z _ a-g i-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==104) {			goto St_209;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_209:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_264;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_264:
		if( scanTbl[(c= *p++)+1792] & 1<< 3){ /*  0-9 A-K M-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==76) {			goto St_309;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_309:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_352;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_352:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_389;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_389:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_425;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_425:
		if( scanTbl[(c= *p++)+2048] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==77) {			goto St_453;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_453:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_476;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_476:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_494;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_494:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_509;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_509:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_521;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_521:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_530;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_530:
		if( scanTbl[(c= *p++)+2048] & 1<< 6){ /*  0-9 A-L N-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==77) {			goto St_537;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 45;
			goto done;
			}
	St_537:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_542;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_542:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_546;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_546:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_550;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_550:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_554;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_554:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_556;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_556:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_558;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_558:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_560;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_560:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_562;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_562:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_563;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_563:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 46;
			goto done;
			}
	St_89:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_152;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_152:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_210;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_210:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_265;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_265:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_310;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_310:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_353;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_353:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_390;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_390:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_426;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_426:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_454;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_454:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 47;
			goto done;
			}
	St_90:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_153;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_153:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_211;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_211:
		if( scanTbl[(c= *p++)+2304] & 1<< 7){ /*  0-9 A-M O-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==78) {			goto St_266;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_266:
		if( scanTbl[(c= *p++)+256] & 1<< 2){ /*  0-9 A-Z _ a-t v-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==117) {			goto St_311;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_311:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_354;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_354:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_391;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_391:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_427;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_427:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_455;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_455:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_477;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_477:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_495;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_495:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 84;
			goto done;
			}
	St_91:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_154;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_154:
		if( scanTbl[(c= *p++)+2560] & 1<< 0){ /*  0-9 A-Z _ a-l o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_213;}
		else if(c ==109) {			goto St_212;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_212:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_267;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_267:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 48;
			goto done;
			}
	St_213:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_268;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_268:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_312;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_312:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_355;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_355:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_392;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_392:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_428;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_428:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_456;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_456:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_478;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_478:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_496;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_496:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 86;
			goto done;
			}
	St_92:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_155;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_155:
		if( scanTbl[(c= *p++)+2560] & 1<< 1){ /*  0-9 A-Z _ a-v x-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==119) {			goto St_214;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_214:
		if( scanTbl[(c= *p++)+2304] & 1<< 4){ /*  0-9 A-S U-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==84) {			goto St_269;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_269:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_313;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_313:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_356;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_356:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_393;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_393:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_429;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_429:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_457;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_457:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_479;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_479:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_497;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_497:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_510;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_510:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 49;
			goto done;
			}
	St_93:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_156;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_156:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_215;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_215:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_270;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_270:
		if( scanTbl[(c= *p++)+1792] & 1<< 4){ /*  0-9 A-Z _ a-g i-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==104) {			goto St_314;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_314:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_357;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_357:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_394;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_394:
		if( scanTbl[(c= *p++)+1536] & 1<< 0){ /*  0-9 A-Z _ a-c e-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==100) {			goto St_430;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_430:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 85;
			goto done;
			}
	St_94:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_157;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_157:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_216;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_216:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_271;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_271:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_315;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_315:
		if( scanTbl[(c= *p++)+2048] & 1<< 1){ /*  0-9 A-Z _ a c-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==98) {			goto St_358;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_358:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_395;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_395:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_431;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_431:
		if( scanTbl[(c= *p++)+2560] & 1<< 2){ /*  0-9 A-C E-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==68) {			goto St_458;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_458:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_480;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_480:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_498;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_498:
		if( scanTbl[(c= *p++)+2048] & 1<< 5){ /*  0-9 A-Z _ a-e g-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==102) {			goto St_511;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_511:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_522;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_522:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 50;
			goto done;
			}
	St_95:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_158;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_158:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_217;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_217:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_272;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_272:
		if( scanTbl[(c= *p++)+1280] & 1<< 5){ /*  0-9 A-Z _ a-f h-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==103) {			goto St_316;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_316:
		if( scanTbl[(c= *p++)+1536] & 1<< 1){ /*  0-9 A-Q S-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==82) {			goto St_359;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_359:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_396;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_396:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_432;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_432:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_459;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_459:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 51;
			goto done;
			}
	St_96:
		if( scanTbl[(c= *p++)+768] & 1<< 1){ /*  0-9 A-Z _ a-q s-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==114) {			goto St_159;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_159:
		if( scanTbl[(c= *p++)+2048] & 1<< 1){ /*  0-9 A-Z _ a c-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==98) {			goto St_218;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_218:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_273;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_273:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_317;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_317:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_360;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_360:
		if( scanTbl[(c= *p++)+256] & 1<< 5){ /*  0-9 A-Z _ a-s u-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==116) {			goto St_397;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_397:
		if( scanTbl[(c= *p++)+1536] & 1<< 5){ /*  0-9 A-Z _ a-x z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==121) {			goto St_433;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_433:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 52;
			goto done;
			}
	St_97:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 44;
			goto done;
			}
	St_98:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+2560] & 1<< 3){ /*  .-/ */
			goto St_47;}
		else if(c ==45) {			goto St_160;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 70;
			goto done;
			}
	St_160:
		if( scanTbl[(c= *p++)+2560] & 1<< 4){ /*  --0 2-9 A-Z _ a-z */
			goto St_47;}
		else if(c ==49) {			goto St_219;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 77;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_219:
		if( scanTbl[(c= *p++)+1024] & 1<< 1){ /*  --9 A-Z _ a-z */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 74;
			goto done;
			}
	St_99:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_161;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_161:
		if( scanTbl[(c= *p++)+1536] & 1<< 2){ /*  0-9 A-Z _ a-h j-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==105) {			goto St_220;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_220:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_274;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_274:
		if( scanTbl[(c= *p++)+1280] & 1<< 6){ /*  0-9 A-Z _ a-n p-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==111) {			goto St_318;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_318:
		if( scanTbl[(c= *p++)+1280] & 1<< 7){ /*  0-9 A-Z _ a-m o-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==110) {			goto St_361;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_361:
		if( scanTbl[(c= *p++)+2560] & 1<< 5){ /*  0 4-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==51) {			goto St_400;}
		else if(c ==50) {			goto St_399;}
		else if(c ==49) {			goto St_398;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_398:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 16;
			goto done;
			}
	St_399:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 17;
			goto done;
			}
	St_400:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 18;
			goto done;
			}
	St_100:
		if( scanTbl[(c= *p++)+768] & 1<< 0){ /*  0-9 A-Z _ a-y */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==122) {			goto St_162;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_162:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 59;
			goto done;
			}
	St_101:
		if( scanTbl[(c= *p++)+512] & 1<< 4){ /*  0-9 A-Z a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==95) {			goto St_163;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_163:
		if( scanTbl[(c= *p++)+1792] & 1<< 7){ /*  0-9 A-Z _ a-r t-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==115) {			goto St_221;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_221:
		if( scanTbl[(c= *p++)+1792] & 1<< 5){ /*  0-9 A-Z _ a-b d-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==99) {			goto St_275;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_275:
		if( scanTbl[(c= *p++)+256] & 1<< 0){ /*  0-9 A-Z _ b-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==97) {			goto St_319;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_319:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_362;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_362:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_401;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_401:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 33;
			goto done;
			}
	St_102:
		if( scanTbl[(c= *p++)+2560] & 1<< 6){ /*  1-9 A-Z a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==95) {			goto St_165;}
		else if(c ==48) {			goto St_164;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_164:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 35;
			goto done;
			}
	St_165:
		if( scanTbl[(c= *p++)+1536] & 1<< 4){ /*  0-9 A-E G-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==70) {			goto St_222;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_222:
		if( scanTbl[(c= *p++)+2560] & 1<< 7){ /*  1-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==48) {			goto St_276;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_276:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 80;
			goto done;
			}
	St_103:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_166;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_166:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 72;
			goto done;
			}
	St_104:
		if( scanTbl[(c= *p++)+256] & 1<< 4){ /*  0-9 A-Z _ a-l n-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==109) {			goto St_167;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_167:
		if( scanTbl[(c= *p++)+256] & 1<< 1){ /*  0-9 A-Z _ a-o q-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==112) {			goto St_223;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_223:
		if( scanTbl[(c= *p++)+1536] & 1<< 3){ /*  0-9 A-Z _ a-k m-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==108) {			goto St_277;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_277:
		if( scanTbl[(c= *p++)+256] & 1<< 6){ /*  0-9 A-Z _ a-d f-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else if(c ==101) {			goto St_320;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 22;
			mkidn(TokenStart, TokenEnd-TokenStart,&extcode,v);
			goto done;
			}
	St_320:
		if( scanTbl[(c= *p++)+0] & 1<< 3){ /*  0-9 A-Z _ a-z */
			goto St_54;}
		else if( scanTbl[c+0] & 1<< 4){ /*  --/ */
			goto St_47;}
		else {
			TokenEnd= (--p); /* FINAL, no auxscan, must set */
			extcode = 76;
			goto done;
			}
