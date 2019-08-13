function [drift,scannum] = laser_drift(base, ptefile)
% [drift,scannum] = laser_drift(base, ptefile);
if nargin < 2 || isempty(ptefile)
  ptefile = 'PTE.txt';
end
P = load(ptefile);
ca = P(:,1);
cellparams = load_cell_cfg;
EtalonFSR = cellparams.fsr;
fn = P(:,5) * EtalonFSR;
S = ICOS_setup(base);
fnb = interp1(ca,fn,S.scannum);
drift = fnb - S.nu_F0;
drift = drift-drift(1);
if nargout > 1
  scannum = S.scannum;
end
