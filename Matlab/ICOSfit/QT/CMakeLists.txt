cmake_policy(SET CMP0048 NEW)
project(icosfit_qt VERSION 4.0.0)

install(FILES
  QT_101.dat QT_11.dat QT_12.dat QT_13.dat QT_131.dat QT_14.dat 
  QT_15.dat QT_151.dat QT_152.dat QT_153.dat QT_154.dat QT_16.dat 
  QT_201.dat QT_202.dat QT_203.dat QT_21.dat QT_22.dat QT_23.dat 
  QT_24.dat QT_31.dat QT_41.dat QT_42.dat QT_43.dat QT_61.dat 
  QT_62.dat QT_63.dat QT_81.dat 
  DESTINATION share/icosfit/Matlab/ICOSfit/QT)
