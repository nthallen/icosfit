function [ nu, mresid, nus_out, resids_out ] = rrresid( region, suffix, PTEfile )
% [ nu, mresid, nus, resids ] = rrresid( region, suffix[, PTEfile] );
% Return all the residuals for the specified fit.
base = [ 'ICOSout.' region ];
if ~isempty(suffix); base = [ base '.' suffix ]; end
lines=[];
by_molecule=0;
ICOSsetup;
xmin = [];
resids = [];
nscans = 0;
for i = scannum'
  path = mlf_path( base, i );
  f = load(path);
  nscans = nscans+1;
  if isempty(xmin)
    resids = f(:,3)-f(:,4);
    xmin = f(1,1);
  else
    if f(1,1) < xmin
      nc = xmin-f(1,1);
      resids = [ NaN*zeros(3,size(resids,2)); resids ];
      xmin = f(1,1);
    end
    if f(end,1) >= xmin + size(resids,1)
      nc = f(end,1)-xmin-size(resids,1)+1;
      resids = [ resids; NaN*zeros(nc,size(resids,2)) ];
    end
    resids(f(:,1)-xmin+1,nscans) = f(:,3)-f(:,4);
  end
end
if nargin < 3; PTEfile = ''; end
x = xmin:xmin+size(resids,1)-1;
nus = get_nu(region, suffix, x, PTEfile, scannum);
[ nu, rresid ] = icos_resample(nus,resids,1e-4);
mresid = nanmean(rresid,2);
if nargout >= 3; nus_out = nus; end
if nargout >= 4; resids_out = resids; end
