cmake_policy(SET CMP0048 NEW)
project(icosfit_src VERSION 4.2.6)

SET(FITSRCS  BitSet.c CScope.c Ccomment.c Cint.c ICOSmain.c QTdata.c
  VoidPtrList.c attrmain.c auxEOF.c auxNUL.c auxScanEOL.c clp.c
  clpintf.c clplib.c coord.c csm.c deftbl.c dflteot.c dfltrepar.c
  driver.c envmod.c err.c evalorder.c f_vector.c fitfunc.c funcabs.c
  funcbase.c funceval.c funcline.c funcnoskew.c funcparam.c funcskew.c
  glahead.c global.c humdev.c idn.c levmar_func.c mlf.c newmem.c
  nl_error.c nl_verr.c nldbg.c nlresp.c nodecode.c obsave.c obstack.c
  parser.c pdl_gen.c pgs_gen.c ptread.c source.c str.c strdup.c
  tabsize.c treebuild.c treecon.c treestack.c vector.c visitmap.c
  visitprocs.c)

add_executable(icosfit ${FITSRCS})
set_source_files_properties(${FITSRCS} PROPERTIES LANGUAGE CXX )
target_link_libraries(icosfit levmar lapack blas)
target_include_directories(icosfit PRIVATE ${icosfit_SOURCE_DIR}/levmar-2.6)
install(TARGETS icosfit RUNTIME DESTINATION bin)
set(QTDIR_DEFAULT ${CMAKE_INSTALL_PREFIX}/share/icosfit/Matlab/ICOSfit/QT CACHE PATH "Path to default QTdir location")
# add_definitions could be rewritten with add_compile_definitions but
# only if we can require cmake 3.12.4:
add_definitions( -DQTDIR_DEFAULT=${QTDIR_DEFAULT} )
