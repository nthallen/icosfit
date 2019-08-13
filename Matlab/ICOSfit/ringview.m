function hh = ringview( scannum, wavenum, basepath)
% ringview( [ scannum [, wavenum[, basepath]]]] );
% Reviews ringdown data.
if nargin < 3
    basepath = '';
end
PT = load('PT');
[Waves,WaveRange] = waves_used;
cell_cfg=load_cell_cfg;
v = find(diff(PT.ScanNum))+1; % index of new ScanNum values
if nargin < 1
  scannum = [];
end
if isempty(scannum)
  scannum = PT.ScanNum;
  scannum = min(scannum(scannum > 0)):max(scannum);
else
  % constrain to within the range of defined values
  scannum = scannum(scannum > 0 & scannum >= min(PT.ScanNum) & ...
    scannum <= max(PT.ScanNum));
end
% Now locate each specified scannum as an index into v, the
% unique PT.ScanNum entry indexes
idx = v(ceil(interp1( PT.ScanNum(v), 1:length(v), scannum )));
% idx is now an array as long as scannum
% PT.ScanNum(idx) should be equal to scannum except where skipping
% occurs, and then it should be greater than scannum.
wavenums = unique(PT.QCLI_Wave(idx));
wavenumi = struct2cell(WaveRange);
wavenumi = cell2mat(squeeze(wavenumi(1,:,:)));

roris = ~[ Waves(wavenums==wavenumi).ISICOS ];
if nargin < 2 || isempty(wavenum)
  % now find(roris) has the ringdown entries
  % scannum(find(roris)) are the ones we want
  % PT.QCLI_Wave(idx(find(roris))) is the wavenum
  wavenum = wavenums(roris);
end
if length(wavenum) > 1
    error('More than one ringdown waveform (%d%s) implicated: choose one', ...
        wavenum(1), sprintf(', %d', wavenum(2:end)));
elseif isempty(wavenum)
    error('No ringdown waveforms found');
end

AppData.WaveRange = WaveRange(wavenum==wavenumi).ranges;
iring=find(PT.QCLI_Wave(idx)==wavenum);
scannum=scannum(iring);
idx=idx(iring);
AppData.Waves = Waves(wavenum==wavenumi);
AppData.base = find_scans_dir(basepath);
AppData.binary = 1;
if size(scannum,1) > 1; scannum = scannum'; end
AppData.scannum = scannum;
AppData.CavityLength = cell_cfg.CavityLength;
AppData.QCLI_Wave = PT.QCLI_Wave;
path = mlf_path( AppData.base, AppData.WaveRange(1), '.dat');
[~, hdr] = loadbin(path);
AppData.StartSerNum = hdr.SerialNum;
AppData.idx = idx;
AppData.wavenum = wavenum;
%Setup x vector in microsec, correlation shift, and delay.
%Need to get first scan in range in case x changed.
path = mlf_path( AppData.base, AppData.scannum(1), '.dat');
[fe, ~] = loadbin(path);
AppData.Tdata = (AppData.Waves.NAverage/AppData.Waves.RawRate) * ...
    (1:length(fe(:,1)));
AppData.dt =  AppData.Tdata(1); % mean(diff(xdata));
AppData.n = 2; % Correlation shift
TzDelay = AppData.Waves.TzSamples * AppData.Waves.NAverage / ...
    AppData.Waves.RawRate;
AppData.delay = TzDelay + 4.5e-6 + 4e-6; %Delay in seconds of the VtoI/electronics
AppData.FitDisplay = 2;
AppData.TauDisplay = 1;
AppData.DerivativeSkip = 10;
AppData.ResidualDisplay = 0;
AppData.FitLength = 40e-6; % in seconds
AppData = ringview_init_taus(AppData);

AppData.Axes = [
    60    45    60     1    20    15    35     .5   0
    60    45    60     1     0    45    50     1    1
    ];

hh_int = scan_viewer('Scans', scannum, 'Axes', AppData.Axes, 'Name', 'Ringdown Viewer', ...
    'Callback', @ringview_callback, 'AppData', AppData);
if nargout > 0
    hh = hh_int;
end

function AppData = ringview_init_taus(AppData)
AppData.tauwindow.x = [];
AppData.tauwindow.y = [];
AppData.skip = ceil(AppData.delay * AppData.Waves.RawRate / ...
    AppData.Waves.NAverage); %number of points to skip
if AppData.skip > length(AppData.Tdata)
    AppData.skip = 1;
end
AppData.xdata = AppData.Tdata - AppData.Tdata(AppData.skip);
FitSamples = ceil(AppData.FitLength * AppData.Waves.RawRate / ...
    AppData.Waves.NAverage);
if length(AppData.xdata) > AppData.skip+FitSamples
    AppData.fitv = (AppData.skip:AppData.skip+FitSamples)';
else
    AppData.fitv = (AppData.skip:length(AppData.xdata))';
end
nscans = length(AppData.scannum);
nansc = zeros(1,nscans)*NaN;
nsamples = length(AppData.fitv);
nanscsam = zeros(nsamples,nscans)*NaN;
AppData.taus = struct('Name',{'auto','nonlin'}, ...
    'Tau',{nansc,nansc}, ...
    'Std',{nansc,nansc}, ...
    'Amp',{nansc,nansc}, ...
    'Fit',{nanscsam,nanscsam}, ...
    'MeanTau',{[],[]}, ...
    'ScanNum',{AppData.scannum,AppData.scannum}, ...
    'SerialNum',{nansc}, ...
    'CurrentOffset',{nansc}, ...
    'Etalon',{nansc}, ...
    'Status',{nansc}, ...
    'fitv', AppData.fitv );

%-------------------------------------------------------------
% ringview_callback() where the real work is done
%-------------------------------------------------------------
function ringview_callback(handles, sv_axes)
if nargin < 2
    sv_axes = handles.Axes;
end
AppData = handles.data.AppData;
if ~isfield(AppData,'menus')
    top_menu = uimenu(handles.scan_viewer,'Tag','ringview','Label','ringview');
    cb = @ringview_menu_callback;
    
    % Tau Display Menu
    AppData.menus.Tau = uimenu(top_menu,'Tag','taumenu','Label','Tau Display');
    if AppData.Waves.NetSamples > 1
        AppData.menus.Tau_current = ...
            uimenu(AppData.menus.Tau,'Tag','Tau_current','Label', ...
            'Current','Callback',cb);
    end
    AppData.menus.Tau_sample = ...
        uimenu(AppData.menus.Tau,'Tag','Tau_sample','Label','Sample', ...
        'Checked','on','Callback',cb);

    % Fit Display Menu
    AppData.menus.Fit = ...
        uimenu(top_menu,'Tag','fitmenu','Label','Fit Display');
    AppData.menus.Fit_derivative = ...
        uimenu(AppData.menus.Fit,'Tag','Fit_derivative', ...
        'Label','Derivative','Callback',cb);
    AppData.menus.Fit_nonlin = ...
        uimenu(AppData.menus.Fit,'Tag','Fit_nonlin', ...
        'Label','Non-linear lsq','Separator','on','Callback',cb);
    AppData.menus.Fit_auto = ...
        uimenu(AppData.menus.Fit,'Tag','Fit_auto', ...
        'Label','Autocorrelation','Callback',cb);
    AppData.menus.Fit_both = ...
        uimenu(AppData.menus.Fit,'Tag','Fit_both','Label','Both', ...
        'Checked','on','Callback',cb);
    AppData.menus.Fit_residuals = ...
        uimenu(AppData.menus.Fit,'Tag','Residuals', ...
        'Label','Residuals','Separator','on','Callback',cb);

    AppData.menus.Export = ...
        uimenu(top_menu,'Tag','Export','Label','Export Tau Struct', ...
        'Callback',cb);
    AppData.menus.Select = ...
        uimenu(top_menu,'Tag','Select','Label', ...
        'Select Base Tau Region','Callback',cb);
    AppData.menus.Write = ...
        uimenu(top_menu,'Tag','Write','Label','Write to Cell_Config', ...
        'Callback',cb);
    AppData.menus.Properties = ...
        uimenu(top_menu,'Tag','Properties','Label','Properties...', ...
        'Callback',cb);
    
    handles.data.AppData = AppData;
    guidata(handles.scan_viewer,handles);
end
scan = handles.data.Scans(handles.data.Index); %scan number
iscan = find(AppData.scannum == scan,1); %index for scan into scannum and idx
if AppData.QCLI_Wave(AppData.idx(iscan)) == AppData.wavenum
    path = mlf_path( AppData.base, scan, '.dat');
    data_ok = 0;
    if AppData.binary
      [fe,hdr] = loadbin( path );
      data_ok = 1;
    elseif exist(path,'file')
      fe = load(path);
      data_ok = 1;
    end
    if data_ok
      if any(~isnan(fe(:,1)))
        %Fit data if not already fit    
        if AppData.FitDisplay >= 0 && AppData.FitDisplay <= 2 && ...
                isnan(AppData.taus(1).Tau(iscan)) && ...
                hdr.SerialNum ~= AppData.StartSerNum
            AppData.taus(1).CurrentOffset(iscan) = ...
                mod(hdr.SerialNum-AppData.StartSerNum, ...
                    AppData.Waves.NetSamples * AppData.Waves.NCoadd) / ...
                       AppData.Waves.NCoadd;
            AppData.taus(2).CurrentOffset(iscan) = ...
                mod(hdr.SerialNum-AppData.StartSerNum, ...
                    AppData.Waves.NetSamples * AppData.Waves.NCoadd) / ...
                       AppData.Waves.NCoadd;

            AppData.taus(1).SerialNum(iscan) = hdr.SerialNum;
            AppData.taus(2).SerialNum(iscan) = hdr.SerialNum;

            AppData.taus(1).Etalon(iscan) = fe(50,2) - min(fe(:,2));
            AppData.taus(2).Etalon(iscan) = fe(50,2) - min(fe(:,2));

            AppData.taus(1).Status = hdr.Status;
            AppData.taus(2).Status = hdr.Status;

            %Do linear auto-correlation fit:
            V = fitlin(fe(AppData.fitv,1), AppData.n);
            b = V(2);
            a = V(5);
            tau = AppData.n*AppData.dt./log(V(1:3));
            trialx = exp(-AppData.xdata(AppData.fitv)/tau(2));
            z = a/(1-b);
            k = sum((fe(AppData.fitv,1)'-z).*trialx)./sum(trialx.*trialx);
            % V = polyfit(trialx, fe(AppData.fitv,1)', 1);
            % z = V(2);
            % k = V(1);
            fit = z+k*trialx;
            %std1 = 1e6 * (tau(1)-tau(3))/2;
            %std1 = sqrt(V(4));
            std1 = std(fe(AppData.fitv,1)'-fit);
            AppData.taus(1).Tau(iscan) = tau(2);
            AppData.taus(1).Std(iscan) = std1;
            AppData.taus(1).Amp(iscan) = k;
            AppData.taus(1).Fit(:,iscan) = fit;
            tau = tau(2);
            
            % Now do a non-linear logarithmic fit
            V = [ k tau z ];
            V = fminsearch('logchi', V, [], AppData.xdata(AppData.fitv)', fe(AppData.fitv,1) );
            k2 = V(1);
            tau2 = V(2);
            z2 = V(3);
            fit2 = k2*exp(-AppData.xdata(AppData.fitv)/tau2) + z2;
            std2 = std(fe(AppData.fitv,1)'-fit2);
            AppData.taus(2).Tau(iscan) = tau2;
            AppData.taus(2).Std(iscan) = std2;
            AppData.taus(2).Fit(:,iscan) = fit2;
            AppData.taus(2).Amp(iscan) = k2;
            handles.data.AppData = AppData;
            guidata(handles.scan_viewer,handles)
        end
        %Set x units for tau display 
        if AppData.TauDisplay == 1
            xlab = 'Scan Number';
            xtau = AppData.taus.ScanNum;
        elseif AppData.TauDisplay == 0
            xlab = 'Current Number';
            xtau = AppData.taus.CurrentOffset;
        end
        
        %Plot fitted taus
        if AppData.FitDisplay < 3
            newplot(sv_axes(1))
            xlabel(sv_axes(1),xlab)
            ylabel(sv_axes(1),'Tau (\musec)')
            title(sv_axes(1),getrun(0,handles.scan_viewer))
            if AppData.FitDisplay == 1 || AppData.FitDisplay == 2
                line(xtau,AppData.taus(1).Tau*1e6,'Parent',sv_axes(1),'Color','b','LineStyle','none','Marker','.')
                text(0.02,0.98, ...
                    sprintf('Tau_{auto} = %.2f \\musec (R = %.1f ppm)',nanmedian(AppData.taus(1).Tau)*1e6,AppData.CavityLength/nanmedian(AppData.taus(1).Tau)/2.998e10*1e6), ...
                    'Parent',sv_axes(1),'Color','b','Units','Normalized','VerticalAlignment','top');
            end
            if AppData.FitDisplay == 0 || AppData.FitDisplay == 2
                line(xtau,AppData.taus(2).Tau*1e6,'Parent',sv_axes(1),'Color','g','LineStyle','none','Marker','.')
                text(0.98,0.98, ...
                    sprintf('Tau_{nonlin} = %.2f \\musec (R = %.1f ppm)',nanmedian(AppData.taus(2).Tau)*1e6,AppData.CavityLength/nanmedian(AppData.taus(2).Tau)/2.998e10*1e6), ...
                    'Parent',sv_axes(1),'Color','g','Units','Normalized','VerticalAlignment','top','HorizontalAlignment','right');
            end
            if isempty(handles.data.xlim{1})
                xlim(sv_axes(1),'auto')
            end
            yl=ylim(sv_axes(1));
            if yl(1) < 0; yl(1) = 0; end
            if yl(2) <= yl(1); yl(2) = yl(1) + 1; end
            if yl(1) > 50; yl(1) = 50; end
            if yl(2) > 50; yl(2) = 51; end
            ylim(sv_axes(1),yl);
            %Calculate mean tau in select box region
            if ~isempty(AppData.tauwindow.x)
               line(AppData.tauwindow.x,AppData.tauwindow.y, ...
                   'Color','k','LineWidth',2,'Parent',sv_axes(1)) 
               x = AppData.tauwindow.x;
               y = AppData.tauwindow.y;
               itauauto = xtau>=min(x) & xtau<=max(x) & ...
                   AppData.taus(1).Tau>=min(y)*1e-6 & ...
                   AppData.taus(1).Tau<=max(y)*1e-6;
               itaunonlin = xtau>=min(x) & xtau<=max(x) & ....
                   AppData.taus(2).Tau>=min(y)*1e-6 & ...
                   AppData.taus(2).Tau<=max(y)*1e-6;
               AppData.taus(1).MeanTau = nanmean(AppData.taus(1).Tau(itauauto));
               AppData.taus(2).MeanTau = nanmean(AppData.taus(2).Tau(itaunonlin));
               handles.data.AppData = AppData;
               guidata(handles.scan_viewer,handles);
            end
            %Display mean tau
            if ~isempty(AppData.taus(1).MeanTau)
                if AppData.FitDisplay == 1 || AppData.FitDisplay == 2
                    text(0.02,0.85, ...
                        sprintf('Tau_{auto} = %.2f \\musec (R = %.1f ppm)', ...
                        AppData.taus(1).MeanTau*1e6, ...
                        AppData.CavityLength/AppData.taus(1).MeanTau/2.998e10*1e6), ...
                        'Parent',sv_axes(1),'Units','Normalized','VerticalAlignment','top');
                end
                if AppData.FitDisplay == 0 || AppData.FitDisplay == 2
                    text(0.98,0.85, ...
                        sprintf('Tau_{nonlin} = %.2f \\musec (R = %.1f ppm)', ...
                            AppData.taus(2).MeanTau*1e6, ...
                            AppData.CavityLength/AppData.taus(2).MeanTau/2.998e10*1e6), ...
                        'Parent',sv_axes(1),'Units','Normalized', ...
                        'VerticalAlignment','top','HorizontalAlignment','right');
                end 
            end
        end
        
        %Plot individual fits
        newplot(sv_axes(2));
        if AppData.FitDisplay == 3
            sk = AppData.DerivativeSkip;
            xn = 1:length(AppData.xdata) - sk;
            der = (fe(xn+sk,1) - fe(xn,1))/sk;
            xd = (AppData.xdata(xn+sk)+AppData.xdata(xn))/2;
            plot(sv_axes(2),xd*1e6,der,'k.-');
            ylabel(sv_axes(2),'dPower/dSample');
            line(xlim(sv_axes(2)),[0 0], ...
                'Color','k','LineStyle',':','Parent',sv_axes(2));
        elseif AppData.ResidualDisplay == 0
            plot(sv_axes(2),AppData.xdata*1e6,fe(:,1),'k');
            ylabel(sv_axes(2),'Power');
            % ### This choice of baseline will break if fe is shorter
            baseline = mean(fe(end-5:end,1));
            line(xlim(sv_axes(2)),[baseline,baseline], ...
                'Color','k','LineStyle',':','Parent',sv_axes(2));
        end
        if AppData.ResidualDisplay == 0
            line([0,0],ylim(sv_axes(2)),'Color','k','LineStyle',':', ...
                'Parent',sv_axes(2));
        end
        if AppData.FitDisplay == 1 || AppData.FitDisplay == 2
            if AppData.ResidualDisplay
                line(AppData.xdata(AppData.fitv)*1e6, ...
                    fe(AppData.fitv,1) - ...
                      AppData.taus(1).Fit(:,iscan), ...
                    'Parent',sv_axes(2),'Color','b');
            else
                line(AppData.xdata(AppData.fitv)*1e6, ...
                    AppData.taus(1).Fit(:,iscan), ...
                    'Parent',sv_axes(2),'Color','b');
            end
        end
        if AppData.FitDisplay == 0 || AppData.FitDisplay == 2
            if AppData.ResidualDisplay
                line(AppData.xdata(AppData.fitv)*1e6, ...
                    fe(AppData.fitv,1) - ...
                      AppData.taus(2).Fit(:,iscan), ...
                    'Parent',sv_axes(2),'Color','g');
            else
                line(AppData.xdata(AppData.fitv)*1e6, ...
                    AppData.taus(2).Fit(:,iscan), ...
                    'Parent',sv_axes(2),'Color','g');
            end
        end
        if AppData.ResidualDisplay
            line([0,0],ylim(sv_axes(2)),'Color','k','LineStyle',':', ...
                'Parent',sv_axes(2));
            if AppData.FitDisplay < 3
                line(xlim(sv_axes(2)),[0 0], ...
                    'Color','k','LineStyle',':','Parent',sv_axes(2));
            end
        end
        xlabel(sv_axes(2),'\musec');
        tautext = sprintf('Ringdown Scan: %d', AppData.scannum(iscan));
        text(0.5,0.95, tautext, ...
            'Parent',sv_axes(2),'Units','Normalized','VerticalAlignment','top', ...
            'HorizontalAlignment','left');      
        if AppData.FitDisplay == 0 || AppData.FitDisplay == 2
            tautext = sprintf('Tau_{nonlin} = %.2f \\musec (std = %.2f)', ...
            AppData.taus(2).Tau(iscan)*1e6,AppData.taus(2).Std(iscan) );
            text(0.5,0.8, tautext, ...
                'Parent',sv_axes(2),'Color','g','Units','Normalized', ...
                'VerticalAlignment','top','HorizontalAlignment','left');      
        end
        if AppData.FitDisplay == 1 || AppData.FitDisplay == 2
            tautext = sprintf('Tau_{auto} = %.2f \\musec (std = %.2f)', ...
            AppData.taus(1).Tau(iscan)*1e6,AppData.taus(1).Std(iscan) );
            text(0.5,0.7, tautext, ...
                'Parent',sv_axes(2),'Color','b','Units','Normalized', ...
                'VerticalAlignment','top','HorizontalAlignment','left');
        end
     end
   end  
end

function ringview_menu_callback(hObject,~)
handles = guidata(hObject);
AppData = handles.data.AppData;
Tag = get(hObject,'Tag');
switch Tag(1)
    case 'F'
        derivative = 'off';
        nonlin = 'off';
        auto = 'off';
        both = 'off';
        switch hObject
            case AppData.menus.Fit_derivative
                derivative = 'on';
                AppData.FitDisplay = 3;
            case AppData.menus.Fit_nonlin
                nonlin = 'on';
                AppData.FitDisplay = 0;
            case AppData.menus.Fit_auto
                auto = 'on';
                AppData.FitDisplay = 1;
            case AppData.menus.Fit_both
                both = 'on';
                AppData.FitDisplay = 2;
        end
        set(AppData.menus.Fit_derivative,'Checked',derivative);
        set(AppData.menus.Fit_nonlin,'Checked',nonlin);
        set(AppData.menus.Fit_auto,'Checked',auto);
        set(AppData.menus.Fit_both,'Checked',both);
        handles.data.AppData = AppData;
        guidata(hObject,handles);
        scan_viewer('scan_display',handles);
    case 'R'
        res = get(AppData.menus.Fit_residuals,'Checked');
        if strcmpi(res,'On')
            res = 'Off';
            AppData.ResidualDisplay = 0;
        else
            res = 'On';
            AppData.ResidualDisplay = 1;
        end
        set(AppData.menus.Fit_residuals,'Checked',res);
        handles.data.AppData = AppData;
        handles.data.ylim{2} = [];
        guidata(hObject,handles);
        scan_viewer('scan_display',handles);
    case 'T'
        current = 'off';
        sample = 'off';
        AppData.tauwindow.x = [];
        AppData.tauwindow.y = [];
        handles.data.xlim{1} = [];
        switch hObject
            case AppData.menus.Tau_current
                current = 'on';
                AppData.TauDisplay = 0;
            case AppData.menus.Tau_sample
                sample = 'on';
                AppData.TauDisplay = 1;
        end
        set(AppData.menus.Tau_current,'checked',current);
        set(AppData.menus.Tau_sample,'checked',sample);
        handles.data.AppData = AppData;
        guidata(hObject,handles);
        scan_viewer('scan_display',handles);
    case 'S'
        if ~waitforbuttonpress
            point1 = get(gca,'CurrentPoint');    % button down detected
            finalRect = rbbox;                   % return figure units
            point2 = get(gca,'CurrentPoint');    % button up detected
            point1 = point1(1,1:2);              % extract x and y
            point2 = point2(1,1:2);
            p1 = min(point1,point2);             % calculate locations
            offset = abs(point1-point2);         % and dimensions
            AppData.tauwindow.x = [p1(1) p1(1)+offset(1) p1(1)+offset(1) p1(1) p1(1)];
            AppData.tauwindow.y = [p1(2) p1(2) p1(2)+offset(2) p1(2)+offset(2) p1(2)];
            handles.data.AppData = AppData;
            guidata(hObject,handles);
            handles = guidata(hObject);
            scan_viewer('scan_display',handles);
        end
    case 'E'
        assignin('base','tau',AppData.taus);
    case 'W'
        cell_cfg = load_cell_cfg;
        if ~isfield(cell_cfg, 'N_Passes')
            cell_cfg.N_Passes = 0;
        end
        fd = fopen('Cell_Config.m', 'w');
        fprintf(fd, 'function cell_cfg = Cell_Config\n');
        fprintf(fd, 'cell_cfg.fsr = %.6f;\n', cell_cfg.fsr );
        fprintf(fd, 'cell_cfg.CavityLength = %.2f;\n', cell_cfg.CavityLength );
        if AppData.FitDisplay == 0
            if isempty(AppData.taus(2).MeanTau)
                errordlg('Must select base tau region.', 'ringview error', 'modal');
            else
                fprintf(fd, 'cell_cfg.MirrorLoss = %.2f;\n', AppData.CavityLength/AppData.taus(2).MeanTau/2.998e10*1e6 );
            end
        elseif AppData.FitDisplay == 1 || AppData.FitDisplay == 2
            if isempty(AppData.taus(1).MeanTau)
                errordlg('Must select base tau region.', 'ringview error', 'modal');
            else
               fprintf(fd, 'cell_cfg.MirrorLoss = %.2f;\n', AppData.CavityLength/AppData.taus(1).MeanTau/2.998e10*1e6 );
            end
        end 
        fprintf(fd, 'cell_cfg.N_Passes = %i;\n', cell_cfg.N_Passes );
        fprintf(fd, 'cell_cfg.CavityFixedLength = %.2f;\n', cell_cfg.CavityFixedLength );
        fclose(fd);
    case 'P'
        answer = inputdlg( ...
            { 'Delay in usecs', ...
              'Fit Length in usecs', ...
              'Correlation Offset in samples', ...
              'Derivative Offset in samples'
            }, 'Ringview Properties', 1, ...
            { sprintf('%.1f', AppData.delay * 1e6), ...
              num2str(AppData.FitLength*1e6), ...
              num2str(AppData.n), ...
              num2str(AppData.DerivativeSkip) ...
            } );
        if ~isempty(answer)
            AppData.delay = str2double(answer{1}) * 1e-6;
            AppData.FitLength = str2double(answer{2}) * 1e-6;
            AppData.n = round(str2double(answer{3}));
            AppData.DerivativeSkip = round(str2double(answer{4}));
            AppData = ringview_init_taus(AppData);
            handles.data.AppData = AppData;
            guidata(hObject,handles);
            handles = guidata(hObject);
            scan_viewer('scan_display',handles);
        end
end
