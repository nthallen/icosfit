function [ nu_out, icos_out ] = icos_resample( nu, icos, dnu )
% [nu_out, icos_out ] = icos_resample( nu, icos, dnu );
% The columns of nu and icos are scans.
% dnu is the desired resolution. dnu must be small enough
% so all of the input nu for any scan will fall into
% unique bins.
nuii = round(nu/dnu);
nuii0 = min(min(nuii));
nuii1 = max(max(nuii));
nu_out = (nuii0:nuii1)'*dnu;
% nu_out = (min(min(nu))+dnu/3:dnu:max(max(nu))+dnu/2)';
% nui = round((nu-min(nu_out))/dnu)+1;
nui = nuii - nuii0 + 1;
if min(min(nui)) ~= 1 | max(max(nui)) > length(nu_out)
  error('Messed up on defining nu_out');
end
dnui = diff(nui);
if any(any(dnui==0))
  error('dnu not small enough (or nu is not changing enough)');
end
icos_out = NaN*zeros(length(nu_out),size(icos,2));
for i=1:size(icos,2)
  icos_out(nui(:,i),i) = icos(:,i);
  v = isnan(icos_out(:,i));
  icos_out(v,i) = interp1(nu_out(~v),icos_out(~v,i),nu_out(v));
end
