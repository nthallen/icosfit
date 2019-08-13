function scanview( scans, base )
% scanview( scans [, base] );
% Display raw scan with etalon, optionally limited to a range
% of Scan values.
if nargin < 1
  base = '';
  scans = listscans();
elseif nargin == 1
  base = '';
end
AppData.base = find_scans_dir(base);

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
scan_viewer('Scans', scans, 'Axes', AppData.Axes_2, 'Name', 'Scan View', ...
    'Callback', @scanview_callback, 'AppData', AppData);

function scanview_callback(handles, sv_axes)
if nargin < 2
    sv_axes = handles.Axes;
end
scan = handles.data.Scans(handles.data.Index);
path = mlf_path( handles.data.AppData.base, scan, '.dat');
fe = loadbin( path );
data_ok = (~isempty(fe));
if data_ok
    ncols = size(fe,2);
    if ncols ~= length(sv_axes)
        if ncols == 1
            handles.data.Axes = handles.data.AppData.Axes_1;
        elseif ncols == 2
            handles.data.Axes = handles.data.AppData.Axes_2;
        elseif ncols == 3
            handles.data.Axes = handles.data.AppData.Axes_3;
        else
            error('Unexpected number of columns: %d', ncols);
        end
        guidata(handles.scan_viewer,handles);
        scan_viewer('scan_viewer_ResizeFcn',handles.scan_viewer,[],handles);
        handles = guidata(handles.scan_viewer);
        scan_viewer('scan_display',handles);
    else
        nsamples = size(fe,1);
        plot(sv_axes(1),1:nsamples,fe(:,1));
        title(sv_axes(1),sprintf('Scan %d: %s %s', scan, ...
            getrunaxis(handles.scan_viewer), ...
            getrun(0,handles.scan_viewer)));
        
        if ncols >= 2
            set(sv_axes(1),'xticklabel',[]);
            plot(sv_axes(2), 1:nsamples, fe(:,2));
            set(sv_axes(2),'YAxisLocation','right');
            if ncols >= 3
                set(sv_axes(2),'xticklabel',[]);
                plot(sv_axes(3), 1:nsamples, fe(:,3));
            end
        end
        xlabel(sv_axes(ncols),'Samples');
    end
end
