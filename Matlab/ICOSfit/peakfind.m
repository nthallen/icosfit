function [ vpeak, vb ] = peakfind( f, hlF, mfhw, threshold )
% [ vpeak, vb ] = peakfind(f [, hlF [, mfhw [, th ] ] ]);
% Locate peaks in f
% hlF is the half-width of the peak filter and should be
%  roughly the half-width at the base of the widest line
%  in samples. Defaults to 25.
% mfhw is the half-width of the median filter used to
%  smooth f before the other filters are applied. Defaults
%  to 1.
% th is the threshold for peak detection, defaults to .3
%
% vpeak is of size n_peaks x 3. The columns are left, peak and right
% index.
% vb is a logical vector that is true for points that are nominally
% on the baseline, false for points in a peak.
%
% peakfind will not detect peaks less than hlF samples from either end of
% the scan.

if nargin < 4
  threshold = .3;
  if nargin < 3
    mfhw = 1;
    if nargin < 2
      hlF = 25;
    end
  end
end
% threshold = .005; % this is an absolute override. not to be committed.
N = length(f);
xx = hlF+1:N-hlF;
if isempty(xx)
  vpeak = [-hlF 0 hlF] + (N+1)/2;
  vb = ones(size(f))==0;
  return;
end
mf = fmedianf(f,mfhw);
% mf = mf/max(mf);
ff = -mf(xx) + .5 * mf(xx-hlF) + .5 * mf(xx+hlF);
if max(ff) > 0 % switched from max(mf) > 0, which seemed wrong
  ff = ff/max(ff);
end

% Identify peaks by locating contiguous regions of ff
% greater than threshold
v = [ 0; ff; 0 ] > threshold;
vup = find(diff(v) > 0); % index into ff
vdn = find(diff(v) < 0) - 1; % index into ff
if length(vup) ~= length(vdn)
  fprintf(1,'vup(%d) and vdn(%d) are different lengths\n', ...
    length(vup), length(vdn) );
end

% could then throw out spikes by requiring that these
% regions have a minimum width
vw = (vdn-vup) > hlF/3;
vup = vup(vw);
vdn = vdn(vw);

% Now locate each peak
vpk = zeros(size(vup));
vlft = vpk;
vrt = vpk;
df = mf(xx+1) - mf(xx);
xxx = (1:length(ff))';
vbase = ones(size(f)) > 0;
for i = 1:length(vup)
  %fprintf(1,'i = %d\n',i);
  vx = vup(i):vdn(i);
  pkht = max(ff(vx));
  vpk(i) = vx(find(ff(vx) == pkht, 1, 'first'));
  vlft(i) = max([1;find(ff < pkht/2 & xxx<vpk(i))]);
  vrt(i) = min([length(ff);find(ff < pkht/2 & xxx>vpk(i))]);
  % hwhm = (vrt(i)-vlft(i))/2;
  hwhm = max([ vrt(i)-vpk(i) vpk(i)-vlft(i) ]);
  fw = floor(hwhm*4.5);
  vlft(i) = max([ 1-hlF vpk(i)-fw ]);
  vrt(i) = min([ length(ff)+hlF vpk(i)+fw]);
  vbase((vlft(i)+1:vrt(i)-1)+hlF) = 0;
end

if nargout >= 1
  vpeak = [ vlft vpk vrt ]+xx(1)-1;
  if nargout >= 2
    vb = vbase;
  end
  return;
end

figure;
fb = f; fb(~vbase) = NaN;
fl = f; fl(vbase) = NaN;
  sample = 1:length(f);
  nsubplot(3,1,1,1); plot(sample, fb, sample, fl, 'r'); grid; ylabel('f');
  set(gca,'XTickLabel',[]);
  xl = xlim;
  nsubplot(3,1,2,1); plot(sample(xx),df); grid; ylabel('df');
  set(gca,'XTickLabel',[],'YAxisLocation','right');
  xlim(xl);
  nsubplot(3,1,3,1);
  plot(sample(xx),ff,sample([min(xx) max(xx)]),[threshold;threshold]);
  grid; ylabel('ff');
  xlim(xl);
  addzoom;
return;
