function sampleno = trackline( scans, sample, n_samples, base )
% sampleno = trackline( scans, sample, n_samples[, base] );
% scans: scan numbers to through which to track. If empty, uses listscans()
% sample: starting sample number of desired line
% n_samples: half-width of region around last known line position to search
% base: if specified, base directory for raw scans.
% 
% Returns: sampleno of line position for each scan. Interactive displays
% scans to verify that the line was in fact correctly tracked. Output
% can be used with PTEtrackline to correct a PTE file for rapid line drift.
if nargin < 4
  base = '';
end
if isempty(scans)
  scans = listscans();
end
AppData.base = find_scans_dir(base);
AppData.sample = sample;
AppData.n_samples = n_samples;
wv = waves_used(scans);
if length(wv) > 1
    error('More than one waveform in scan region');
end
SignalRegion = get_waveform_params( wv.Name, ...
  'SignalRegion', wv.TzSamples+100:wv.NetSamples-wv.TzSamples-20 );

nscans = length(scans);
sn = zeros(nscans,1);
for i=1:nscans
    scan = scans(i);
    new_sample = current_pos(AppData.base, scan, AppData.sample, ...
        n_samples, SignalRegion);
    sn(i) = new_sample;
    AppData.sample = new_sample;
end
AppData.sampleno = sn;

Axes = [
    60    45    60     1    20    30    60     1    0
    ];
scan_viewer('Scans', scans, 'Axes', Axes, 'Name', 'Track Line', ...
    'Callback', @trackline_callback, 'AppData', AppData);
if nargout > 0
    sampleno = sn;
end

function trackline_callback(handles, sv_axes)
if nargin < 2
    sv_axes = handles.Axes;
end
scan = handles.data.Scans(handles.data.Index);
%i = find(scan == handles.data.Scans);
new_sample = handles.data.AppData.sampleno(handles.data.Index);
fe = scanload(scan);
% [new_sample,fe] = current_pos(handles.data.AppData.base, scan, ...
%     handles.data.AppData.sample, handles.data.AppData.n_samples);
data_ok = (~isempty(fe));
if data_ok
    nsamples = size(fe,1);
    plot(sv_axes(1),1:nsamples,fe(:,1),new_sample,fe(new_sample,1),'*r');
    title(sv_axes(1),sprintf('Scan %d: %s', scan, ...
        getrun(0,handles.scan_viewer)));
    xlabel(sv_axes(1),'Samples');
    handles.data.AppData.sample = new_sample;
    guidata(handles.scan_viewer,handles);
end

function [new_sample, fe_out] = current_pos(base, scan, sample, n_samples, SignalRegion)
path = mlf_path( base, scan, '.dat');
fe = loadbin( path );
data_ok = (~isempty(fe));
if data_ok
    range = sample + n_samples*[-1 1];
    range(1) = max([range(1) min(SignalRegion)]);
    range(2) = min([range(2) max(SignalRegion)]);
    idx = range(1):range(2);
    new_sample = idx(find(fe(idx,1) == min(fe(idx,1)),1));
else
    new_sample = [];
end
if nargout > 1
    fe_out = fe;
end
