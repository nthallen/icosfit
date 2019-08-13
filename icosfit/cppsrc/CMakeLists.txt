cmake_policy(SET CMP0048 NEW)
project(icosfit_src VERSION 4.0.0)

SET(FITSRCS  attrmain.c auxEOF.c auxNUL.c auxScanEOL.c BitSet.c
  Ccomment.c Cint.c clp.c clpintf.c clplib.c coord.c CScope.c csm.c
  deftbl.c dflteot.c dfltrepar.c driver.c envmod.c err.c evalorder.c
  f_vector.c fitfunc.c funcabs.c funcbase.c funceval.c funcline.c
  funcnoskew.c funcparam.c funcskew.c glahead.c global.c humdev.c
  ICOSmain.c idn.c levmar_func.c mlf.c newmem.c nl_error.c nl_verr.c
  nldbg.c nlresp.c nodecode.c obsave.c obstack.c parser.c pdl_gen.c
  pgs_gen.c ptread.c QTdata.c source.c str.c strdup.c tabsize.c
  treebuild.c treecon.c treestack.c vector.c visitmap.c visitprocs.c
  VoidPtrList.c)

add_executable(icosfit ${FITSRCS})
set_source_files_properties(${FITSRCS} PROPERTIES LANGUAGE CXX )
target_link_libraries(icosfit levmar lapack blas)
target_include_directories(icosfit PRIVATE /levmar-2.6)
install(icosfit RUNTIME DESTINATION bin)
