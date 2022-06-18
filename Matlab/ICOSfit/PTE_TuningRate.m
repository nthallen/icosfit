function [dFNdx, xout] = PTE_TuningRate(PTEFile, scan_stride, sample_stride)
if nargin < 3
  sample_stride = 1;
  if nargin < 2
    scan_stride = 1;
    if nargin < 1
      PTEFile = 'PTE.txt';
    end
  end
end
PTE = load(PTEFile);
scans_idx = 1:scan_stride:size(PTE,1);
scans = PTE(scans_idx,1);
wvs = waves_used(scans);
S0 = PTE(1,4);
S1 = wvs.NetSamples - wvs.TzSamples;
S = S0:sample_stride:S1;
x = (S - S0)/1000;
x1 = ones(1,length(x));
dFNdx = PTE(scans_idx,6)*x1 + ...
        PTE(scans_idx,7)*x + ...
        ((-PTE(scans_idx,8)./PTE(scans_idx,9))*x1).*exp(-(PTE(scans_idx,9).^(-1))*x) + ...
        ((-PTE(scans_idx,10)./PTE(scans_idx,11))*x1).*exp(-(PTE(scans_idx,11).^(-1))*x);
if nargout >= 2
  xout = x*1000+S0;
end
