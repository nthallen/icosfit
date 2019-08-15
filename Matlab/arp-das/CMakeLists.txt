cmake_policy(SET CMP0048 NEW)
project(icosfit_arp_das VERSION 4.0.0)

install(FILES
  addzoom.m binavg.m dft.m fastavg.m findinpath.m fmedianf.m getrun.m 
  getrundir.m isdigit.m lightspeed.m matchx.m nanmean.m normalize.m 
  nsubplot.m time2d.m 
  DESTINATION share/icosfit/Matlab/arp-das)

