function [ wvsused, ranges ] = waves_used(ScanNum)
% waves_used( [ScanNum] );
%   Lists waveforms used in the current run.
% wvs = waves_used([ScanNum]);
%   Returns a struct array of waveform definitions
% [wvs,ranges] = waves_used([ScanNum]);
%   Returns two struct arrays of the same length
%   ranges has 'wvno' and 'ranges' fields.
%   The ranges field is an n x 2 matrix where the two columns
%   are starting and ending Scan numbers for each region
WaveSpecs = load_waves;
PT = load_mat_files('PT');
dcpi = find(diff(PT.ScanNum)>0)+1; % index of new scan numbers
if nargin > 0
  dcpi = dcpi(max(1,ceil(interp1(PT.ScanNum(dcpi),1:length(dcpi),ScanNum,'linear','extrap'))));
  dcpi = dcpi(find(~isnan(dcpi)));
else
  ScanNum = PT.ScanNum;
end
wvs = PT.QCLI_Wave(dcpi);
wvnos = unique(wvs)';
if nargout > 0
  wvsused = WaveSpecs(wvnos+1);
end
if nargout == 1; return; end
if nargout >= 2; ranges = []; end
for wvno=wvnos
  dw = diff([-1;wvs;-1] == wvno);
  wvbeg = PT.ScanNum(dcpi((find(dw > 0)))-1)+1;
  wvend = PT.ScanNum(dcpi(find(dw < 0)-1));
  if length(wvbeg) ~= length(wvend)
    error('Different lengths');
  end
  wvrng = struct('wvno',wvno,'ranges', [ wvbeg wvend ]);
  if nargout >= 2
    if isempty(ranges)
      ranges = wvrng;
    else
      ranges(end+1) = wvrng;
    end
  else
    fprintf( 1, '%d %s:', wvno, WaveSpecs(wvno+1).Name );
    for i = 1:length(wvbeg)
      fprintf( 1, ' %d-%d', wvbeg(i), wvend(i) );
    end
    fprintf( 1, '\n' );
  end
end
