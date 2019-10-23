SHELL   = /bin/sh

CC	= g++
CFLAGS	= -g \
	-I../../levmar-2.6 \
	-DQTDIR_DEFAULT=$(QTDIR)
LIBS	= -L../../../build-levmar -lm -llevmar -llapack \
	-lblas

OBJS	= driver.o clpintf.o clp.o csm.o obstack.o obsave.o deftbl.o \
	err.o source.o coord.o pdl_gen.o VoidPtrList.o clplib.o \
	envmod.o BitSet.o treecon.o nodecode.o ICOSmain.o ptread.o \
	f_vector.o nl_error.o nl_verr.o nldbg.o mlf.o newmem.o \
	nlresp.o strdup.o global.o fitfunc.o vector.o evalorder.o \
	funceval.o funcline.o funcparam.o QTdata.o levmar_func.o \
	funcbase.o funcnoskew.o funcskew.o treebuild.o parser.o \
	glahead.o auxNUL.o auxEOF.o dflteot.o tabsize.o idn.o \
	Cint.o auxScanEOL.o str.o Ccomment.o pgs_gen.o treestack.o \
	dfltrepar.o attrmain.o visitprocs.o funcabs.o humdev.o \
	visitmap.o CScope.o

EXE	= icosfit.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h coord.h \
		clp.h envmod.h deftbl.h BitSet.h Strings.h CScope.h \
		pdl_gen.h treecon.h DefTableKeyList.h VoidPtrList.h csm.h \
		global.h clplib.h funceval.h config.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h nodeptr.h

clpintf.o:	clpintf.c clplib.h clpintf.h eliproto.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h funceval.h config.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h obstack.h

csm.o:	csm.c csm.h csmtbl.h obsave.h obstack.h eliproto.h

obstack.o:	obstack.c obstack.h gettext.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h \
		coord.h

err.o:	err.c err.h source.h eliproto.h coord.h

source.o:	source.c source.h

coord.o:	coord.c coord.h eliproto.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h funceval.h eliproto.h config.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h coord.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h eliproto.h \
		coord.h deftbl.h BitSet.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h coord.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h \
		coord.h clp.h envmod.h deftbl.h BitSet.h Strings.h CScope.h \
		pdl_gen.h treecon.h DefTableKeyList.h VoidPtrList.h csm.h \
		global.h clplib.h funceval.h config.h VoidPtr.h \
		VoidPtrFunctionTypes.h

nodecode.o:	nodecode.c nodecode.h

ICOSmain.o:	ICOSmain.c ICOSfit.h clp.h mlf.h global.h config.h nl.h \
		funceval.h levmar_func.h ptread.h f_vector.h clplib.h \
		pdl_gen.h DefTableKeyList.h eliproto.h deftbl.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h

ptread.o:	ptread.c config.h ptread.h nl.h global.h mlf.h f_vector.h \
		funceval.h

f_vector.o:	f_vector.c f_vector.h nl.h config.h

nl_error.o:	nl_error.c nl.h

nl_verr.o:	nl_verr.c nl.h

nldbg.o:	nldbg.c nl.h

mlf.o:	mlf.c mlf.h nl.h

newmem.o:	newmem.c nl.h

nlresp.o:	nlresp.c nl.h

strdup.o:	strdup.c nl.h

global.o:	global.c global.h config.h funceval.h

fitfunc.o:	fitfunc.c ICOSfit.h global.h clp.h vector.h nl_assert.h \
		config.h nl.h funceval.h levmar_func.h ptread.h mlf.h \
		f_vector.h clplib.h pdl_gen.h DefTableKeyList.h eliproto.h \
		deftbl.h VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h

vector.o:	vector.c vector.h nl.h config.h

evalorder.o:	evalorder.c config.h funceval.h nl.h

funceval.o:	funceval.c config.h nl.h funceval.h global.h ptread.h mlf.h \
		f_vector.h

funcline.o:	funcline.c config.h nl.h funceval.h global.h ptread.h mlf.h \
		f_vector.h

funcparam.o:	funcparam.c config.h nl.h funceval.h global.h ptread.h \
		nl_assert.h mlf.h f_vector.h

QTdata.o:	QTdata.c ICOSfit.h global.h nl_assert.h config.h nl.h \
		funceval.h levmar_func.h ptread.h mlf.h f_vector.h

levmar_func.o:	levmar_func.c ICOSfit.h config.h nl.h funceval.h \
		levmar_func.h ptread.h mlf.h f_vector.h

funcbase.o:	funcbase.c ICOSfit.h global.h config.h nl.h funceval.h \
		levmar_func.h ptread.h mlf.h f_vector.h

funcnoskew.o:	funcnoskew.c funceval.h global.h nl.h config.h

funcskew.o:	funcskew.c funceval.h ptread.h global.h nl.h config.h mlf.h \
		f_vector.h

treebuild.o:	treebuild.c eliproto.h pdl_gen.h source.h csm.h clp.h \
		clpintf.h deftbl.h funceval.h config.h obstack.h clplib.h \
		DefTableKeyList.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h

parser.o:	parser.c err.h gla.h gsdescr.h reparatur.h pgs_gen.h \
		eliproto.h coord.h parsops.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h \
		coord.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h coord.h

Cint.o:	Cint.c err.h eliproto.h coord.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h \
		coord.h

str.o:	str.c csm.h obstack.h eliproto.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h coord.h

pgs_gen.o:	pgs_gen.c gsdescr.h treestack.h HEAD.h err.h parsops.h \
		eliproto.h coord.h nodeptr.h clp.h envmod.h deftbl.h \
		BitSet.h Strings.h CScope.h pdl_gen.h treecon.h \
		DefTableKeyList.h VoidPtrList.h csm.h global.h clplib.h \
		funceval.h config.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h

treestack.o:	treestack.c err.h treestack.h eliproto.h coord.h nodeptr.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h coord.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h err.h \
		eliproto.h coord.h HEAD.h node.h treecon.h clp.h envmod.h \
		deftbl.h BitSet.h Strings.h CScope.h pdl_gen.h \
		DefTableKeyList.h VoidPtrList.h csm.h global.h clplib.h \
		funceval.h config.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		CScope.h pdl_gen.h treecon.h DefTableKeyList.h \
		VoidPtrList.h csm.h global.h clplib.h eliproto.h funceval.h \
		config.h VoidPtr.h VoidPtrFunctionTypes.h obstack.h coord.h \
		nodeptr.h

funcabs.o:	funcabs.c ICOSfit.h global.h nl_assert.h config.h nl.h \
		funceval.h levmar_func.h ptread.h mlf.h f_vector.h

humdev.o:	humdev.c config.h funceval.h ptread.h nl.h global.h mlf.h \
		f_vector.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h envmod.h deftbl.h BitSet.h Strings.h \
		CScope.h err.h pdl_gen.h DefTableKeyList.h VoidPtrList.h \
		csm.h global.h clplib.h funceval.h config.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h coord.h nodeptr.h

CScope.o:	CScope.c CScope.h envmod.h deftbl.h obstack.h BitSet.h \
		eliproto.h

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
BINTGT=icosfit.exe
DATADIR=$(PREFIX)/share/icosfit
MLSRC=../../Matlab
MLDEST=$(DATADIR)/Matlab
QTDIR=$(MLDEST)/ICOSfit/QT
.PHONY : install

install : icosfit.exe
	[ -d $(DESTDIR)$(BINDIR) ] || mkdir -p $(DESTDIR)$(BINDIR)
	cp -vf icosfit.exe $(DESTDIR)$(BINDIR)/$(BINTGT)
	[ -d $(DESTDIR)$(MLDEST)/ICOSfit/QT ] || mkdir -p $(DESTDIR)$(MLDEST)/ICOSfit/QT
	cp $(MLSRC)/ICOSfit/*.m $(MLSRC)/ICOSfit/*.fig $(DESTDIR)$(MLDEST)/ICOSfit
	cp $(MLSRC)/ICOSfit/QT/*.dat $(DESTDIR)$(QTDIR)
	[ -d $(DESTDIR)$(MLDEST)/arp-das ] || mkdir $(DESTDIR)$(MLDEST)/arp-das
	cp $(MLSRC)/arp-das/*.m $(DESTDIR)$(MLDEST)/arp-das
