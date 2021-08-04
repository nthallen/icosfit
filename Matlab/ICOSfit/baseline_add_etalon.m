function pmax_out = baseline_add_etalon(base, oname, scans, periods, maxf, outputdir, k)
% baseline_add_etalon(base, oname[, scans[,periods[,maxf[,outputdir]]]])
% base is the output directory of an icosfit run
% oname is the baseline name fragment. Output is written to
%   'sbase.oname.ptb'.
% scans optionally specifies which scan numbers should be included in the
%   analysis of the baseline parameter values. If specified, the scans must
%   be included in the specified icosfit run.
%
% The scans in the icosfit run must be numbered monitonically, either
% increasing or decreasing.
%
% The 'frequency' is in cm and the period is in cm-1. The cm-1 values are
% most readily 'readable' in an rrfit plot, so that is what I will return.
S = ICOS_setup(base);
n_scans = length(S.scannum);
scani = 1:n_scans;
if nargin < 2, oname = ''; end
if nargin >= 3 && ~isempty(scans)
  scani = interp1(S.scannum,scani,scans,'nearest');
end
if nargin < 4
  periods = [];
elseif ~isempty(periods)
  if ~isvector(periods)
    error('periods input must be a vector or empty');
  elseif iscolumn(periods)
    periods = periods';
  end
end
if nargin < 5, maxf = 0; end
if nargin < 6, outputdir = ''; end
if nargin < 7, k = 1; end

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
if endsWith(S.output_cols{S.n_input_params+1},' Value: k_input')
  n_base_params = n_base_params + 1;
end
if n_base_params ~= S.n_base_params
  error('n_base_params do not agree');
end

n_scans = length(scani);
D = load(mlf_path(base,S.scannum(1)));
min_freq = 1/abs(D(1,2)-D(end,2));
max_freq = min(1/mean(abs(diff(D(:,2))))/2, ...
  2/min(mean(S.Gv)));
if maxf > 0
  max_freq = min(max_freq, maxf);
end
f = linspace(min_freq,max_freq,1024);
% DFT = zeros(length(f),n_scans);
DFT = zeros(length(f),1);
for i=1:n_scans
  D = load(mlf_path(base,S.scannum(i)));
  % DFT(:,i) = abs(dft(D(:,2),(D(:,4)-D(:,3)),f));
  DFT = DFT + abs(dft(D(:,2),(D(:,4)-D(:,3)),f));
end

% mDFT = mean(DFT,2);
DFT = DFT/n_scans;
mDFT = DFT;
fmax = f(find(mDFT==max(mDFT),1));
pmax = 1/fmax;
if isempty(oname)
  figure;
  yrange = [0 max(max(DFT))*1.1];
  plot(f,DFT,fmax*[1 1],yrange,'r');
  if ~isempty(periods)
    freqs = 1./periods;
    x = [freqs;freqs];
    y = yrange'*ones(size(periods));
    hold on;
    plot(x,y,'g');
  end
  title(sprintf('%s: Largest etalon at %.1f cm (%.2f cm^{-1})', ...
    base, fmax, 1/fmax));
  xlabel('cm');
else
  if ~isempty(vectors)
    vectors = vectors*k;
  end
  writeetlnbase(oname,PV,nu,vectors, pmax, [], outputdir);
end
if nargout > 0
  pmax_out = pmax;
end