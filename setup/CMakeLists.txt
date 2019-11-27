install(PROGRAMS
  ${CMAKE_CURRENT_BINARY_DIR}/icosfit_matlab_setup.sh
  DESTINATION share/icosfit/setup
)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/icosfit_matlab_setup.sh.in
  ${CMAKE_CURRENT_BINARY_DIR}/icosfit_matlab_setup.sh
  @ONLY
)
