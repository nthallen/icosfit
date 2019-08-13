function varargout = scan_viewer(varargin)
% SCAN_VIEWER MATLAB code for scan_viewer.fig
%      SCAN_VIEWER, by itself, creates a new SCAN_VIEWER
%
%      H = SCAN_VIEWER returns the handle to a new SCAN_VIEWER
%
%      SCAN_VIEWER('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SCAN_VIEWER.M with the given input arguments.
%
%      SCAN_VIEWER('Property','Value',...) creates a new SCAN_VIEWER or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before scan_viewer_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to scan_viewer_OpeningFcn via varargin.
%
%      Properties:
%        'Scans': list of scan numbers, nominally increasing.
%        'Axes': array of axes parameters, one row per axis
%           margin_left min_width margin_right stretch_w ...
%             margin_top min_height margin_bottom stretch_h ...
%             x_group
%        'Name': string to put at top of gui
%        'Callback': Callback function (cannot be first property!)
%        'AppData': Data to be stored in handles.data.AppData

% function my_callback(handles, sv_axes)
% if nargin < 2
%   sv_axes = handles.Axes;
% end

% To Do:
%   Make resize more responsive? (addlistener)

% Edit the above text to modify the response to help scan_viewer

% Last Modified by GUIDE v2.5 11-Dec-2012 14:15:23

% Begin initialization code - DO NOT EDIT
gui_Singleton = 0;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @scan_viewer_OpeningFcn, ...
                   'gui_OutputFcn',  @scan_viewer_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before scan_viewer is made visible.
function scan_viewer_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to scan_viewer
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to scan_viewer (see VARARGIN)

% Choose default command line output for scan_viewer
handles.output = hObject;

% Update handles structure
set(handles.ViewerGroup, 'SelectionChangeFcn', ...
    @ViewerGroup_SelectionChangeFcn);
handles.data.Scans = [];
handles.data.Index = 1;
FP = get(handles.scan_viewer, 'Position');
SP = get(handles.Slider, 'Position');
set(handles.Slider,'UserData', FP(3)-SP(1)-SP(3));
SP = get(handles.CrntScan,'Position');
set(handles.CrntScan,'UserData', FP(3)-SP(1)-SP(3));
set(handles.scan_viewer,'UserData',pwd);
for i=1:2:length(varargin)-1
  if strcmpi(varargin{i},'Scans')
      handles.data.Scans = varargin{i+1};
  elseif strcmpi(varargin{i},'Name')
      set(handles.scan_viewer,'Name',varargin{i+1});
  elseif strcmpi(varargin{i},'Axes')
      handles.data.Axes = varargin{i+1};
      if size(handles.data.Axes,2) ~= 9
          errordlg('Axes property has wrong dimensions');
          close(handles.scan_viewer);
          return;
      end
      Pos = Axes_Positions(handles);
      handles.Axes = zeros(size(Pos,1),1);
      figure(handles.scan_viewer);
      for j=1:size(Pos,1)
          handles.Axes(j) = axes('Units','pixels','Position',Pos(j,:));
          handles.data.xlim{j} = [];
          handles.data.ylim{j} = [];
      end
      handles.Zoom = zoom;
      handles.data.SavedPreZoomState = handles.Pause;
      set(handles.Zoom,'ActionPostCallback',@Zoom_PostCallback);
      set(handles.Zoom,'ActionPreCallback',@Zoom_PreCallback);
  elseif strcmpi(varargin{i},'AppData')
      handles.data.AppData = varargin{i+1};
  elseif strcmpi(varargin{i},'Callback')
      handles.data.Callback = varargin{i+1};
  else
      errordlg(sprintf('Unrecognized property: %s', varargin{i}));
      close(handles.scan_viewer);
      return;
  end
end
handles.data.Index_max = length(handles.data.Scans);
guidata(hObject, handles);
if isempty(handles.data.Scans)
    errordlg('No scans specified');
    close(handles.scan_viewer);
    return;
else
    set(handles.Slider,'Min',1,'Max',handles.data.Index_max,'Value',1);
    scan_display(handles);
end
handles = guidata(hObject);
handles.SliderListener = ...
    addlistener(handles.Slider,'Value','PostSet', ...
    @(hObj,eventdat)scan_viewer('Slider_Listener',hObject,eventdat));
guidata(hObject, handles);

% UIWAIT makes scan_viewer wait for user response (see UIRESUME)
% uiwait(handles.scan_viewer);


% --- Outputs from this function are returned to the command line.
function varargout = scan_viewer_OutputFcn(~, ~, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to scan_viewer
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
if isempty(handles)
    varargout{1} = 0;
else
    varargout{1} = handles.output;
end

function scan_viewer_CloseRequestFcn(hObject, ~, ~)
% hObject    handle to scan_viewer (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the scan_viewer
% set(handles.ViewerGroup,'SelectedObject',handles.Pause);
delete(hObject);

function Slider_Listener(hObject, eventdata)
% fprintf(1,'Slider_Listener event\n');
handles = guidata(hObject);
Slider_Callback(hObject,eventdata,handles);

function Slider_Callback(~, ~, handles)
NewIndex = round(get(handles.Slider,'Value'));
if handles.data.Index ~= NewIndex
    set(handles.ViewerGroup,'SelectedObject',handles.Pause);
    handles.data.Index = NewIndex;
    scan_display(handles);
end

function Slider_CreateFcn(hObject, ~, ~)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

function ViewerGroup_SelectionChangeFcn(hObject, ~)
% fprintf(1,'State change\n');
while ishandle(hObject)
    handles = guidata(hObject);
    Speed = get(handles.Speed,'UserData');
    action = get(handles.ViewerGroup,'SelectedObject');
    SIndex = round(get(handles.Slider,'Value'));
    if SIndex ~= handles.data.Index && action ~= handles.Pause
        set(handles.ViewerGroup,'SelectedObject',handles.Pause);
        handles.data.Index = SIndex;
        scan_display(handles);
    end
    if action == handles.Pause
        if handles.data.SavedPreZoomState ~= handles.Pause
            pause(.1);
        else
            break;
        end
    elseif action == handles.Play
        if handles.data.Index < handles.data.Index_max
            handles.data.Index = handles.data.Index+1;
            scan_display(handles);
        end
        set(handles.ViewerGroup,'SelectedObject',handles.Pause);
    elseif action == handles.FastFwd
        if handles.data.Index + Speed(2) < handles.data.Index_max
            handles.data.Index = handles.data.Index + Speed(2);
            scan_display(handles);
            pause(Speed(1));
        else
            set(handles.ViewerGroup,'SelectedObject',handles.Pause);
        end
    elseif action == handles.Reverse
        if handles.data.Index > 1
            handles.data.Index = handles.data.Index-1;
            scan_display(handles);
        end
        set(handles.ViewerGroup,'SelectedObject',handles.Pause);
    elseif action == handles.FastRev
        if handles.data.Index > 1
            if handles.data.Index > Speed(2)
                handles.data.Index = handles.data.Index - Speed(2);
            else
                handles.data.Index = 1;
            end
            scan_display(handles);
            pause(Speed(1));
        else
            set(handles.ViewerGroup,'SelectedObject',handles.Pause);
        end
    else
        errordlg('Unknown object');
    end
end
% fprintf(1,'Leaving state change\n');
% guidata(hObject, handles);

function CrntScan_CreateFcn(~, ~, ~)

function P = Set_Speed(hObject, handle, Pin, Pnew)
if hObject == handle
    set(handle,'checked','on');
    P = Pnew;
else
    set(handle,'checked','off');
    P = Pin;
end

function Speed_Callback(hObject, ~, handles)
P = get(handles.Speed,'UserData');
P = Set_Speed(hObject, handles.Spd_1Hz, P, [ 1, 1 ]);
P = Set_Speed(hObject, handles.Spd_3Hz, P, [ 1/3 1]);
P = Set_Speed(hObject, handles.Spd_10Hz, P, [1/10 1]);
P = Set_Speed(hObject, handles.Spd_Step_1, P, [0 1]);
P = Set_Speed(hObject, handles.Spd_Step_10, P, [0 10]);
P = Set_Speed(hObject, handles.Spd_Step_100, P, [0 100]);
set(handles.Speed, 'UserData', P);

function scan_viewer_ResizeFcn(hObject, ~, handles)
if isfield(handles,'data') % first invocation comes before open fcn
    FP = get(handles.scan_viewer,'Position');
    SP = get(handles.Slider,'Position');
    Srm = get(handles.Slider,'UserData');
    SP(3) = FP(3)-Srm-SP(1);
    delta = 0;
    if SP(3) < 60
        delta = 60-SP(3);
        SP(3) = 60;
    end
    set(handles.Slider,'Position',SP);
    SP = get(handles.CrntScan,'Position');
    Srm = get(handles.CrntScan','UserData');
    SP(1) = FP(3)-Srm-SP(3)+delta;
    set(handles.CrntScan,'Position',SP);
    if delta > 0
        FP(3) = FP(3) + delta;
        set(handles.scan_viewer,'Position',FP);
    end
    if ~isfield(handles,'Axes')
        handles.Axes = [];
    end
    if ~isfield(handles.data,'xlim')
        xl = handles.data.xlim{1};
    else
        xl = [];
    end
    Pos = Axes_Positions(handles);
    for j = 1:max(length(handles.Axes),size(Pos,1))
        if j > length(handles.Axes)
            handles.Axes(j) = axes('Units','pixels','Position',Pos(j,:));
            handles.data.xlim{j} = xl;
            handles.data.ylim{j} = [];
        elseif j > size(Pos,1)
            delete(handles.Axes(j));
        else
            set(handles.Axes(j),'Position',Pos(j,:));
        end
    end
    if size(Pos,1) < length(handles.Axes)
        handles.Axes = handles.Axes(1:size(Pos,1));
    end
    guidata(hObject,handles);
    drawnow;
end

function Pos = Axes_Positions(handles, fig)
Axes = handles.data.Axes;
if nargin < 2
    VGP = get(handles.ViewerGroup,'Position');
    cur_y = VGP(2)+VGP(4);
    fig = handles.scan_viewer;
else
    cur_y = 0;
end
min_width = sum(sum(Axes(:,1:3)));
min_height = sum(sum(Axes(:,4:7))) + cur_y;
FP = get(fig,'Position');
readjust = 0;
if (FP(3) < min_width)
    FP(3) = min_width;
    readjust = 1;
end
if (FP(4) < min_height)
    delta = min_height-FP(4);
    FP(2) = FP(2) - delta;
    FP(4) = min_height;
    readjust = 1;
end
if readjust
    set(fig,'Position',FP);
end
Pos = zeros(size(Axes,1),4);
v_stretch_wt = sum(Axes(:,8));
v_stretch_px = FP(4) - min_height;
for i = size(Pos,1):-1:1
    cur_y = cur_y + Axes(i,7);
    if v_stretch_wt > 0
        ht = round(v_stretch_px * Axes(i,8) / v_stretch_wt);
        v_stretch_px = v_stretch_px - ht;
        v_stretch_wt = v_stretch_wt - Axes(i,8);
    else
        ht = 0;
    end
    ht = ht + Axes(i,6);
    Pos(i,:) = [ Axes(i,1) cur_y FP(3)-Axes(i,1)-Axes(i,3) ht-1 ];
    cur_y = cur_y + ht + Axes(i,5);
end

% --------------------------------------------------------------------
function scan_display(handles)
% Update CrntScan, slider
if handles.data.Index_max >= 1
    guidata(handles.scan_viewer,handles);
    set(handles.CrntScan,'String',num2str(handles.data.Scans(handles.data.Index)));
    set(handles.Slider,'Value',handles.data.Index);
    if isfield(handles.data, 'Callback')
        handles.data.Callback(handles);
        % scan_viewer(handles.scan_viewer);
        zoom(handles.scan_viewer, 'reset');
        for i = 1:length(handles.Axes)
            if ~isempty(handles.data.xlim{i})
                set(handles.Axes(i),'xlim',handles.data.xlim{i});
            end
            if ~isempty(handles.data.ylim{i})
                set(handles.Axes(i),'ylim',handles.data.ylim{i});
            end
        end
    end
    drawnow;
end

function Export_Callback(~, ~, handles)
if handles.data.Index_max >= 1
    fig = figure;
    Pos = Axes_Positions(handles, fig);
    Axes = zeros(size(Pos,1),1);
    for j=1:size(Pos,1)
        Axes(j) = axes('Units','pixels','Position',Pos(j,:));
    end
    for j=1:size(Pos,1)
        set(Axes(j),'Units','normalized');
    end
    handles.data.Callback(handles, Axes);
    for i = 1:length(Axes)
        if ~isempty(handles.data.xlim{i})
            set(Axes(i),'xlim',handles.data.xlim{i});
        end
        if ~isempty(handles.data.ylim{i})
            set(Axes(i),'ylim',handles.data.ylim{i});
        end
    end
    addzoom;
end

% --------------------------------------------------------------------
function ZoomOn_Callback(~, ~, ~)
zoom on;

% --------------------------------------------------------------------
function ZoomOff_Callback(~, ~, ~)
zoom off;

% --------------------------------------------------------------------
function ZoomX_Callback(~, ~, ~)
zoom xon;

% --------------------------------------------------------------------
function ZoomY_Callback(~, ~, ~)
zoom yon;

function Zoom_PreCallback(hObject, ~)
handles = guidata(hObject);
handles.data.SavedPreZoomState = get(handles.ViewerGroup,'SelectedObject');
set(handles.ViewerGroup,'SelectedObject',handles.Pause);
guidata(hObject,handles);

function Zoom_PostCallback(hObject, eventdata)
handles = guidata(hObject);
set(handles.ViewerGroup,'SelectedObject',handles.data.SavedPreZoomState);
motion = get(handles.Zoom,'Motion');
axes_idx = find(handles.Axes == eventdata.Axes);
xlim = [];
if strcmpi(motion,'horizontal') || strcmpi(motion,'both')
    zmode = get(eventdata.Axes,'xlimmode');
    if strcmp(zmode,'manual')
        xlim = get(eventdata.Axes,'xlim');
        handles.data.xlim{axes_idx} = xlim;
    elseif strcmp(zmode,'auto')
        handles.data.xlim{axes_idx} = [];
    end
    x_group = handles.data.Axes(axes_idx,9);
    for i = 1:length(handles.Axes)
        if i ~= axes_idx && handles.data.Axes(i,9) == x_group
            if isempty(xlim)
                set(handles.Axes(i),'xlimmode','auto');
            else
                set(handles.Axes(i),'xlim',xlim);
            end
            handles.data.xlim{i} = xlim;
        end
    end
end
if strcmpi(motion,'vertical') || strcmpi(motion,'both')
    zmode = get(eventdata.Axes,'ylimmode');
    if strcmp(zmode,'manual')
        ylim = get(eventdata.Axes,'ylim');
        handles.data.ylim{axes_idx} = ylim;
    elseif strcmp(zmode,'auto')
        handles.data.ylim{axes_idx} = [];
    end
end
handles.data.SavedPreZoomState = handles.Pause;
guidata(hObject, handles);
