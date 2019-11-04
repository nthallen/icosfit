function baseline_add_etalon(base, oname, scans)
% baseline_add_etalon(base, oname[, scans])
% base is the output directory of an icosfit run
% oname is the baseline name fragment. Output is written to
%   'sbase.oname.ptb'.
% scans optionally specifies which scan numbers should be included in the
%   analysis of the baseline parameter values. If specified, the scans must
%   be included in the specified icosfit run.
%
% The scans in the icosfit run must be numbered monitonically, either
% increasing or decreasing.
S = ICOS_setup(base);
n_scans = length(S.scannum);
scani = 1:n_scans;
if nargin < 3 || isempty(scans)
  scans = S.scannum;
else
  scani = interp1(S.scannum,scani,scans,'nearest');
end
if nargin < 2, oname = ''; end

% Load the existing baseline and perform sanity checks
[nu, vectors,p_coeffs,Ptype,PV,~] = readetlnbase(S.BaselineFile);
if Ptype ~= 0
  error('Cannot currently rescale polynomials of nu');
end
if p_coeffs ~= length(PV)
  error('p_coeffs ~= length(PV)');
end
n_base_params = p_coeffs;
if ~isempty(vectors)
  n_base_params = n_base_params + 1 + size(vectors,2);
end
if n_base_params ~= S.n_base_params
  error('n_base_params do not agree');
end

n_scans = length(scani);
f = 1:0.1:40;
DFT = zeros(length(f),n_scans);
for i=1:n_scans
  D = load(mlf_path(base,S.scannum(i)));
  DFT(:,i) = abs(dft(D(:,2),(D(:,4)-D(:,3)),f));
end

mDFT = mean(DFT,2);
fmax = f(find(mDFT==max(mDFT),1));
figure;
plot(f,DFT,fmax*[1 1],[0 max(max(DFT))*1.1],'r');
if isempty(oname)
  title(sprintf('%s: Largest etalon at %.1f cm^{-1}', ...
    base, fmax));
else
  title(sprintf('%s: Adding largest etalon at %.1f cm^{-1} as %s', ...
    base, fmax, oname));
end
xlabel('cm^{-1}');

pmax = 1/fmax;
if ~isempty(oname)
  writeetlnbase(oname,PV,nu,vectors, [pmax 1]);
end
% writeetlnbase(oname,oPV,nu,vectors);
