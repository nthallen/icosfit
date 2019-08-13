function [line_pos, Sout, unshifted] = get_line_position(region, suffix, PTEfile)
% [line_pos, S] = get_line_position(base);
% [line_pos, S] = get_line_position(region, suffix);
% [line_pos, S] = get_line_position(base, [], PTEfile);
% [line_pos, S] = get_line_position(region, suffix, PTEfile);
% [line_pos, Sout, unshifted] = get_line_position(...)
%
% Inputs:
%  base: directory name for base
%  region, suffix: For specifying base ICOSout.region.suffix
%  PTEfile: defaults to S.PTEfile
% Outputs:
%  linepos: sample number of line centers
%  S: ICOS_setup Output structure
%  unshifted: sample number of line position without pressure shift

if (nargin < 2 || isempty(suffix))
    if exist(region,'dir')
        base = region;
    else
        base = ['ICOSout.' region];
    end
else
    base = ['ICOSout.' region '.' suffix ];
end
S = ICOS_setup(base);
if S.ICOSfit_format_ver < 2
    error('get_line_position only works with ICOSfit_format_ver >= 2 (icosfit v1.17)');
end
if nargin < 3 || isempty(PTEfile)
    PTEfile = S.PTEfile;
end

if S.ICOS_debug
  scans = ones(size(S.scannum))*S.ICOS_debug_scan;
else
  scans = S.scannum;
end
FSR = S.EtalonFSR;
PTE = load(PTEfile);
[SS,I] = unique(PTE(:,1));
PI = interp1(SS,I,scans,'nearest');
%wv = waves_used(scans);
%if length(wv) > 1
%    error('More than one waveform in scan region');
%end
%SignalRegion = get_waveform_params( wv.Name, ...
%    'SignalRegion', wv.TzSamples+100:wv.NetSamples-wv.TzSamples-20 );
%nu = get_nu(region, suffix, SignalRegion, PTEfile);
line_pos = zeros(size(S.nu_P));
line_pos2 = line_pos;
for i=1:length(scans)
    if PTE(PI(i),1) ~= scans(i)
        line_pos(i,:) = NaN;
    else
        x = S.fitdata(i,5):S.fitdata(i,6);
        Y = PTE(PI(i),5:11);
        xx = (x-PTE(PI(i),4)+1)*1e-3;
        nu = S.nu0 + S.nu_F0(i) - FSR*etln_evalJ(Y,xx);
        line_pos(i,:) = interp1(nu,x,S.nu_P(i,:));
        if nargout > 2
            line_pos2(i,:) = interp1(nu,x,S.nu);
        end
    end
end
if nargout > 1
    Sout = S;
    if nargout > 2
        unshifted = line_pos2;
    end
end
