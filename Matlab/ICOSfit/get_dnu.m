function dnu = get_dnu( PTEfile, x )
% dnu_rel = get_nu(PTEfile, x);
%  Returns the tuning rate (cm-1/sample) determined from the
%  etalon fit. Since the absolute wavenumber
%  is equal to nu_rel + nu_F0 + nu0, where nu_F0 and nu0 are
%  constants, we do not need to refer to the fit to determine
%  the tuning rate.
if isempty(PTEfile)
  PTEfile = 'PTE.txt';
end
PTE = load(PTEfile);
scannums = PTE(:,1);
dnu = zeros(length(scannums),length(x));
cellparams=load_cell_cfg;
FSR = cellparams.fsr; % 0.0198;
if iscolumn(x)
  x = x';
end
xrow = ones(1,length(x));
X = ones(length(scannums),1) * x;
X = (X - PTE(:,4)*xrow)/1000;
dnu = PTE(:,6)*xrow + 2*(PTE(:,7)*xrow).*X ...
  - ((PTE(:,8)./PTE(:,9))*xrow).*exp(-X./(PTE(:,9)*xrow)) ...
  - ((PTE(:,10)./PTE(:,11))*xrow).*exp(-X./(PTE(:,11)*xrow));
dnu = dnu*FSR / 1000; % convert from cm-1/Ksample to cm-1/sample
