function PTEview( PTEfile, x )
% PTEview( PTEfile, x );
% Display raw etalon scan with fit data
base = '';
AppData.PTE = load(PTEfile);
scans = AppData.PTE(:,1);
AppData.base = find_scans_dir(base);
AppData.x = x;

AppData.Axes_1 = [
    60    45    60     1    20    30    60     1    0
    ];
AppData.Axes_2 = [
    60    45    60     1    20    30     0     1    0
    60    45    60     1     0    30    60     1    0
    ];
AppData.Axes_3 = [
    60    45    60     1    20    30     0     1    0
    60    45    60     1     0    30     0     1    0
    60    45    60     1     0    30    60     1    0
    ];
scan_viewer('Scans', scans, 'Axes', AppData.Axes_1, 'Name', 'PTE View', ...
    'Callback', @PTEview_callback, 'AppData', AppData);
end

function PTEview_callback(handles, sv_axes)
    if nargin < 2
    sv_axes = handles.Axes;
    end
    i = handles.data.Index;
    scan = handles.data.Scans(i);
    PTEfitcols = [5:11 13:17];
    PTE = handles.data.AppData.PTE(i,:);
    x = handles.data.AppData.x;
    [~,etln] = loadscans(handles.data.AppData.base, scan, x);
    emdl = etln_evalJ(PTE(PTEfitcols),(x-PTE(4))/1000);
    plot(sv_axes, x, etln, x, emdl);
    title(sv_axes(1),sprintf('Scan %d: %s %s', scan, ...
      getrunaxis(handles.scan_viewer), ...
      getrun(0,handles.scan_viewer)));
    xlabel(sv_axes(1),'Sample');
end