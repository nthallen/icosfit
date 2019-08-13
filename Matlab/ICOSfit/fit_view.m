function fit_view( base, varargin )
% fit_view( base[, options]);
%   Display fitted scans.
% fit_view( base, 'scannum', scans)
%   Limit display to specified scan range
if nargin < 1
  disp('Error: Must define base. eg ''ICOSout.R1.3p''')
  return
end
RC = icosfit_recalculate(base, varargin{:});
AppData.RC = RC;

AppData.Xopt = 0;
AppData.Yopt = 0;
AppData.plotbase = 0;
AppData.Axes_A = [
    60    45    60     1    20    15     0     .5   0
    60    45    60     1     0    45    60     1    0
    ];
AppData.Axes_B = [
    60    45    60     1    20    15     0     .5    0
    60    45    60     1     0    45     0     1     0
    60    45    60     1     0    30     0     .5    0
    60    45    60     1     0    30    60     .5    0
    ];
scan_viewer('Scans', RC.Scans, 'Axes', AppData.Axes_A, 'Name', 'Fit Viewer', ...
    'Callback', @fit_view_callback, 'AppData', AppData);

function fit_view_callback(handles, sv_axes)
if nargin < 2
    sv_axes = handles.Axes;
end
AppData = handles.data.AppData;
if ~isfield(AppData,'menus')
    top_menu = uimenu(handles.scan_viewer,'Tag','rrfit','Label','rrfit');
    cb = @rrfit_menu_callback;
    AppData.menus.Y = uimenu(top_menu,'Tag','Ymenu','Label','Y');
    AppData.menus.Y_signal = uimenu(AppData.menus.Y,'Tag','Y_signal','Label','Signal','Checked','on','Callback',cb);
    AppData.menus.Y_detrend = uimenu(AppData.menus.Y,'Tag','Y_detrend','Label','Detrend','Callback',cb);
    AppData.menus.Y_transmission = uimenu(AppData.menus.Y,'Tag','Y_trans','Label','Transmission','Callback',cb);
    AppData.menus.Y_strength = uimenu(AppData.menus.Y,'Tag','Y_strength','Label','Strength','Callback',cb);
    AppData.menus.X = uimenu(top_menu,'Tag','Ymenu','Label','X');
    AppData.menus.X_wavenumber = uimenu(AppData.menus.X,'Tag','X_wavenumber','Label','Wavenumber','Checked','on','Callback',cb);
    AppData.menus.X_sample = uimenu(AppData.menus.X,'Tag','X_sample','Label','Sample','Callback',cb);
    AppData.menus.Baselines = uimenu(top_menu,'Tag','Baselines','Label','Baselines','Callback',cb);
    handles.data.AppData = AppData;
    guidata(handles.scan_viewer,handles);
end
scan = handles.data.Scans(handles.data.Index);
if AppData.RC.S.ICOS_debug
    error('Need to discover the real source path');
    path = sprintf( '%s/%04d.dat', AppData.RC.S.base, scan);
else
    path = mlf_path( AppData.RC.S.base, scan, '.dat');
end
fe = icosfit_recalculate(AppData.RC, handles.data.Index);
data_ok = (~isempty(fe));
if data_ok
    % AppData.plotbase = strcmp(get(AppData.menus.Baselines,'Checked'),'on');
    i=find(AppData.RC.S.scannum==scan);
    lpos = AppData.RC.S.nu + AppData.RC.S.delta*(AppData.RC.S.P_vec(i)/760.) ...
              - AppData.RC.S.fitdata(i,AppData.RC.S.v);
    if AppData.RC.S.nu0 ~= 0
      lpos = lpos + AppData.RC.S.nu_F0(i);
    end
    lgd = AppData.RC.S.fitdata(i,AppData.RC.S.v+1);
    % lst = AppData.RC.S.Scorr.*AppData.RC.S.CavLen.*AppData.RC.S.Nfit./(AppData.RC.S.Ged*sqrt(pi));
    lgl = AppData.RC.S.fitdata(i,AppData.RC.S.v+3);
    lwid = (lgd+lgl); % fitdata(i,v+1)+fitdata(i,v+3);
     if AppData.Xopt == 0
        nux = fe(:,2);
        if min(nux) < 2
            nux = nux+AppData.RC.S.nu_F0(i)+AppData.RC.S.nu0; % This may change
        end
        xdir = 'reverse';
        ttlx = 'Wavenumber (cm-1)';
     else
        nux = fe(:,1);
        xdir = 'normal';
        ttlx = 'Sample Number';
    end
    dataX = nux;
    resX = nux;
    if AppData.Yopt == 0
        dataY = fe(:,3:5);
        resY = fe(:,3)-fe(:,4);
        reslbl = 'Fit Res';
        sdev = sqrt(mean((resY).^2));
        ttltext = [ 'Scan:' num2str(AppData.RC.S.scannum(i)) ...
            ' \sigma = ' num2str(sdev)  ' '  path ];
        basep = interp1(nux,fe(:,5),lpos,'nearest');
        fitp =  interp1(nux,fe(:,4),lpos,'nearest');
        meanp = (basep+fitp)/2;
        % threw in maxp to see the position of small lines
        maxp = ones(size(lpos))*max(fe(:,5));
    elseif AppData.Yopt == 1
        dataY = [fe(:,3)./fe(:,5)*100, fe(:,4)./fe(:,5)*100];
        resY = (fe(:,3)-fe(:,4))./fe(:,5)*100;
        reslbl = 'Fit Res (%)';
        sdev = sqrt(mean((resY).^2));
        ttltext = [ 'Scan:' num2str(AppData.RC.S.scannum(i)) ...
            ' \sigma = ' num2str(sdev)  ' '  path ];
        basep = interp1(nux,fe(:,5)./fe(:,5)*100,lpos,'nearest');
        fitp =  interp1(nux,fe(:,4)./fe(:,5)*100,lpos,'nearest');
        meanp = (basep+fitp)/2;
        % threw in maxp to see the position of small lines
        maxp = ones(size(lpos))*100;
    elseif AppData.Yopt == 2
        dataY = fe(:,6);
        resY = fe(:,3)-fe(:,4);
        reslbl = 'Fit Res';
        sdev = sqrt(mean((resY).^2));
        ttltext = [ 'Scan:' num2str(AppData.RC.S.scannum(i)) ...
            ' \sigma = ' num2str(sdev)  ' '  path ];
        basep = interp1(nux,fe(:,6),lpos,'nearest');
        fitp =  interp1(nux,fe(:,6),lpos,'nearest');
        meanp = (basep+fitp)/2;
        % threw in maxp to see the position of small lines
        maxp = ones(size(lpos))*max(fe(:,6));
    elseif AppData.Yopt == 3
        dataY = fe(:,3:5);
        trend = fe(1,5)+(0:size(fe,1)-1)'*(fe(end,5)-fe(1,5))/(size(fe,1)-1);
        dataY = dataY - trend*[1 1 1];
        resY = fe(:,3)-fe(:,4);
        reslbl = 'Fit Res';
        sdev = sqrt(mean((resY).^2));
        ttltext = [ 'Scan:' num2str(AppData.RC.S.scannum(i)) ...
            ' \sigma = ' num2str(sdev)  ' '  path ];
        basep = interp1(nux,dataY(:,3),lpos,'nearest');
        fitp =  interp1(nux,dataY(:,2),lpos,'nearest');
        meanp = (basep+fitp)/2;
        % threw in maxp to see the position of small lines
        maxp = ones(size(lpos))*max(dataY(:,3));
    end
   
    X = [ lpos lpos-lwid; lpos lpos+lwid ];
    % Y = [ basep meanp; fitp meanp ];
    Y = [ maxp meanp; fitp meanp ];
      
    plot(sv_axes(1),resX, resY);
    set(sv_axes(1),'XDir',xdir,'xticklabel',[],'Xgrid','on','Ygrid','on');
    ylabel(sv_axes(1),reslbl);
    title(sv_axes(1),ttltext);

    if AppData.Xopt == 0
        plot(sv_axes(2), dataX,dataY, X, Y, 'r');
    else
        plot(sv_axes(2), dataX,dataY);
    end
    set(sv_axes(2),'XDir', xdir,'YAxisLocation','right','Xgrid','on','Ygrid','on');
    if AppData.plotbase == 1
          set(sv_axes(2),'XTickLabel',[]);
          plot(sv_axes(3),dataX,fe(:,5),'r'); 
          set(sv_axes(3),'XTickLabel',[],'XDir',xdir,'Xgrid','on','Ygrid','on');
          ylabel(sv_axes(3),'Baseline');
          plot(sv_axes(4),dataX,detrend(fe(:,5)),'r');
          set(sv_axes(4),'XDir',xdir,'YAxisLocation','right','Xgrid','on','Ygrid','on');
          ylabel(sv_axes(4),'Detrended Baseline'); 
          xlabel(sv_axes(4),ttlx);
    else
          xlabel(sv_axes(2),ttlx);
    end
    linkaxes(sv_axes,'x');
end

function rrfit_menu_callback(hObject,eventdata)
handles = guidata(hObject);
AppData = handles.data.AppData;
Tag = get(hObject,'Tag');
switch Tag(1)
    case 'Y'
        sig = 'off';
        dt = 'off';
        trans = 'off';
        stren = 'off';
        switch hObject
            case AppData.menus.Y_signal
                sig = 'on';
                handles.data.AppData.Yopt = 0;
            case AppData.menus.Y_detrend
                dt = 'on';
                handles.data.AppData.Yopt = 3;
            case AppData.menus.Y_transmission
                trans = 'on';
                handles.data.AppData.Yopt = 1;
            case AppData.menus.Y_strength
                stren = 'on';
                handles.data.AppData.Yopt = 2;
        end
        set(AppData.menus.Y_signal,'checked',sig);
        set(AppData.menus.Y_detrend,'checked',dt);
        set(AppData.menus.Y_transmission,'checked',trans);
        set(AppData.menus.Y_strength,'checked',stren);
        handles.data.ylim{2} = [];
        guidata(hObject,handles);
        scan_viewer('scan_display',handles);
    case 'X'
        wvno = 'off';
        samp = 'off';
        switch hObject
            case AppData.menus.X_wavenumber
                wvno = 'on';
                handles.data.AppData.Xopt = 0;
            case AppData.menus.X_sample
                samp = 'on';
                handles.data.AppData.Xopt = 1;
        end
        for i = 1:length(handles.data.xlim)
            handles.data.xlim{i} = [];
        end
        set(AppData.menus.X_wavenumber,'checked',wvno);
        set(AppData.menus.X_sample,'checked',samp);
        guidata(hObject,handles);
        scan_viewer('scan_display',handles);
    case 'B'
        if strcmp(get(AppData.menus.Baselines,'checked'),'on')
            set(AppData.menus.Baselines,'checked','off');
            handles.data.AppData.plotbase = 0;
            handles.data.Axes = AppData.Axes_A;
        else
            set(AppData.menus.Baselines,'checked','on');
            handles.data.AppData.plotbase = 1;
            handles.data.Axes = AppData.Axes_B;
        end
        guidata(hObject,handles);
        scan_viewer('scan_viewer_ResizeFcn',hObject,eventdata,handles);
        handles = guidata(hObject);
        scan_viewer('scan_display',handles);
end
