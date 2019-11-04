function icosfit_cygwin_setup
%%
P = getenv('PATH');
ppre = { 'C:\cygwin64\usr\local\bin', 'C:\cygwin64\bin' };
ppost = { 'C:\cygwin64\usr\lib\lapack' };
for i = length(ppre):-1:1
  if ~contains(P,ppre{i})
    P = [ ppre{i} ';' P ];
  end
end
for i = 1:length(ppost)
  if ~contains(P,ppost{i})
    if P(end) == ';'
      sep = '';
    else
      sep = ';';
    end
    P = [ P sep ppost{i} ];
  end
end
setenv('PATH',P);
