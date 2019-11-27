CC      = g++
QTDIR   = /usr/share/icosfit/Matlab/ICOSfit/QT
CFLAGS  = -Wall -DQTDIR_DEFAULT=$(QTDIR)

LIBS    = -L/usr/local/lib -lm
LEVMARBUILDDIR = $(PWD)/../../../build-levmar
LIBLEVMAR = $(LEVMARBUILDDIR)/liblevmar.a
.PHONY : all test cppsrc cppsrcexe
all : Odinfile $(LIBLEVMAR)
	eli '%dtarget >icosfit.exe'
Odinfile : Odinfile.in Makefile
	perl -pe "s,\@PWD\@,$(PWD),; s,\@LEVMARBUILDDIR\@,$(LEVMARBUILDDIR),; s,\@QTDIR\@,$(QTDIR)," Odinfile.in >Odinfile
test :
	eli '%dtarget >/usr/local/bin/icosfit_test.exe'
cppsrc :
	./gen_cppsrc.sh $(VERSION)
cppsrcexe :
	cd ../cppsrc && make
$(LIBLEVMAR) : $(LEVMARBUILDDIR)/Makefile
	cd $(LEVMARBUILDDIR) && make
$(LEVMARBUILDDIR)/Makefile :
	@[ -d $(LEVMARBUILDDIR) ] || mkdir $(LEVMARBUILDDIR)
	cd $(LEVMARBUILDDIR) && \
	cmake ~-/../../levmar-2.6 -DBUILD_DEMO=FALSE \
	-DCMAKE_LEGACY_CYGWIN_WIN32=0

include Makefile.tail
