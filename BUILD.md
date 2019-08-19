# ICOSfit Build Options Summary:

## Prerequisites
Building icosfit requires the following:
  * gcc/g++
  * Gnu Make
  * cmake
  * liblapack and libblas
cmake is not a hard requirement, although the author has not actually tried
to build liblevmar without it. Levmar requires liblapack and libblas, but
can be configured to build without them at a significant loss of performance.

All of the following options start in the root directory of the source tree.

## Preferred build method:
Use cmake to build entire project using icosfit/cppsrc directory
  * mkdir ../build-icosfit
  * cd ../build-icosfit
  * cmake ../git  [ -DQTDIR_DEFAULT= \<path\> ] [ -DCMAKE_INSTALL_PREFIX=/usr/local ] &&
  * make
  * make install [ DESTDIR=tmp ]

## Build using make in cppsrc:
First need to build the levmar library in ../build-levmar. If levmar is built elsewhere
(like in the source directory), you must pass LEVMARBUILDDIR=\<path\> to make, where
LEVMARBUILDDIR is the path relative to cppsrc. All the make options can be given for
both build and install, but QTDIR is only relevant during build while PREFIX and DESTDIR
are only relevant during install. Not specifying QTDIR during install is a risk only if
changes will cause rebuilding before install.
  * cd icosfit/cppsrc
  * make \<options\>
  * make install \<options\>

## Build using eli in elisrc:
This option requires that you have the [Eli Compiler Construction suite](http://eli-project.sourceforge.net/)
installed. The Makefile will run cmake to build the levmar library in ../build-levmar.
If levmar is manually built elsewhere (like in the source directory), you must
pass LEVMARBUILDDIR=\<path\> to make.
  * cd icosfit/elisrc
  * make \<options\>
  * make install \<options\>

### To propagate changes form elisrc to cppsrc:
Note that this is a crucial step before release!
  * cd icosfit/elisrc
  * make cppsrc

## Make \<options\> for both elisrc and cppsrc
  * QTDIR=/usr/local/share/icosfit/Matlab/ICOSfit/QT
    * Where the QT files willl ultimately be installed
  * LEVMARBUILDDIR=../../../build-levmar
    * Path relative to the source/build directory where liblevmar.a can be found
  * PREFIX=/usr/local
    * The base directory for the ultimate installation
  * DESTDIR=
    * A prefix to $PREFIX for where files are installed. Used for staging and testing installation
