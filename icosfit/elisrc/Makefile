CC      = g++
CFLAGS  = -Wall -O2
LIBS    = -L/usr/local/lib -lm
.PHONY : all test cppsrc cppsrcexe
all :
	eli '%dtarget >icosfit.exe'
test :
	eli '%dtarget >/usr/local/bin/icosfit_test.exe'
cppsrc :
	./gen_cppsrc.sh
cppsrcexe :
	cd ../cppsrc && make

include Makefile.tail
