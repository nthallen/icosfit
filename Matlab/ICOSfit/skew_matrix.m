function [A,k] = skew_matrix(region,npts,tol)
% A = skew_matrix(region,npts,tol);
% [A,k] = skew_matrix(region,npts,tol);
%   Return skew matrix and gain factor
% 
% In the absence of absorbers,
%  output = k*A*input;
% where k = sum(A(end,:))*(1-R^(2N))/(1-R^2)
% k and A are calculated by icosfit, so when generating
% input power vectors for icosfit, you would use
%  input = (A\output)/k;
%
% A is normalized
if isnumeric(region)
  scannum = region;
else
  scannum = fitline('region',region);
end
wv = waves_used(scannum);
if length(wv) > 1
  error('More than one waveform used in specified region');
end
fsam = wv.RawRate/wv.NAverage;
fprintf(1,'ScanNum: %d QCLI_Wave: %s fsam: %f\n', scannum(1), wv.Name, fsam );
if nargin < 3
  tol = 10e-6;
end
cellparams=load_cell_cfg;
CavityLength = cellparams.CavityLength;
MirrorLoss = cellparams.MirrorLoss*1e-6;
c = lightspeed; % cm/sec
R = 1-MirrorLoss;
N = c/(2*CavityLength*fsam);
M = ceil(log(tol)/(2*N*log(R)));
n = [1:M]-1;
R2N = R^(2*N);
A = spdiags( ones(npts,1)*(R2N.^n), -n, npts, npts );
wt = sum(A,2);
A = A.*((1./wt)*ones(1,npts));
if nargout > 1
  k = wt(end)*(1-R2N)/(1-R*R);
end
% fprintf(1,'N = %f\nM = %d\nk = %f\n', N, M, k );
