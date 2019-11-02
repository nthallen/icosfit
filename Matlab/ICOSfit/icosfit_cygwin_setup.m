function icosfit_cygwin_setup
%%
P = getenv('PATH');
pp = { 'C:\cygwin64\usr\lib\lapack', 'C:\cygwin64\usr\local\bin', 'C:\cygwin64\bin' };
for i = 1:length(pp)
  if ~contains(P,pp{i})
    P = [ pp{i} ';' P ];
  end
end
setenv('PATH',P);
