function pmax_out = baseline_add_etalon(base, oname, scans, periods, maxf, outputdir, k)
% baseline_add_etalon(base, oname[, scans[,periods[,maxf[,outputdir]]]])
% Analyzes the fit specified by base, performing a DFT on the fit residuals
% and generating a plot to help identify key frequencies that should be
% fit. Optionally generates a new baseline file incorporating the largest
% frequency component.
%
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
% periods is empty or a vector of etalon periods in cm-1. These are used to
% indicate in the DFT plot where etalons have previously been added. Note
% that the 'frequency' is in cm and the period is in cm-1. The cm-1 values
% are most readily 'readable' in an rrfit plot, so that is what I will
% use.
%
% maxf is an optional limit on the maximum frequency for the DFT. This
% could be informed by the minimum line widths, although I don't yet know
% what the exact relations ship should be. Presumably 1/(4*min(HWHM)) would
% be the frequency that most closely matches the narrowest line, but
% somewhat higher frequencies are still likely to affect a line. Perhaps 5X
% or 10X higher would be a good guess.
%
% outputdir is used when the baseline is being written to another
% directory, as is true in baseline_optimizer.
%
% k is the skew matrix scale factor.
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

% Identify line widths and consider limiting the maxf to an order of
% magnitude beyond the minimum width. (That is only a valid limitation if
% the run explores the full range of pressures.)
lfreq =  1./(4*[max(S.Gvcalc);min(S.Gvcalc)]);
mfreq = mean(lfreq);
dfreq = diff(lfreq)/2;

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
  % Display line widths
  Yvals = linspace(yrange(2),0,length(lfreq)+2);
  hold on;
  errorbar(mfreq,Yvals(2:end-1),dfreq,'horizontal','og');
  hold off;
  grid on;

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