function varargout = edit_ICOSfit_cfg(varargin)
% EDIT_ICOSFIT_CFG M-file for edit_ICOSfit_cfg.fig
%      EDIT_ICOSFIT_CFG, by itself, creates a new EDIT_ICOSFIT_CFG or raises the existing
%      singleton*.
%
%      H = EDIT_ICOSFIT_CFG returns the handle to a new EDIT_ICOSFIT_CFG or the handle to
%      the existing singleton*.
%
%      EDIT_ICOSFIT_CFG('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in EDIT_ICOSFIT_CFG.M with the given input arguments.
%
%      EDIT_ICOSFIT_CFG('Property','Value',...) creates a new EDIT_ICOSFIT_CFG or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before edit_ICOSfit_cfg_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to edit_ICOSfit_cfg_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help edit_ICOSfit_cfg

% Last Modified by GUIDE v2.5 24-Jul-2013 15:52:18

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @edit_ICOSfit_cfg_OpeningFcn, ...
                   'gui_OutputFcn',  @edit_ICOSfit_cfg_OutputFcn, ...
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


% --- Executes just before edit_ICOSfit_cfg is made visible.
function edit_ICOSfit_cfg_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to edit_ICOSfit_cfg (see VARARGIN)

% Choose default command line output for edit_ICOSfit_cfg
if length(varargin) >= 2 && strcmp(varargin{1},'Config')
  ICOSfit_cfg = varargin{2};
else
  ICOSfit_cfg = load_ICOSfit_cfg(1);
end
set(handles.WavesFile,'String', ICOSfit_cfg.WavesFile);
set(handles.Matlab_Path,'String',ICOSfit_cfg.Matlab_Path);
set(handles.ICOSfit_Path,'String',ICOSfit_cfg.ICOSfit_Path);
set(handles.ScanDir,'String',ICOSfit_cfg.ScanDir);
S{1} = pwd;
cd ..
S{2} = pwd;
cd ..
S{3} = pwd;
cd(S{1});
set(handles.SaveDir, 'String', S, 'value', 1);
handles.output = ICOSfit_cfg;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes edit_ICOSfit_cfg wait for user response (see UIRESUME)
uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = edit_ICOSfit_cfg_OutputFcn(~, ~, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
delete(handles.figure1);

function Matlab_Path_Callback(hObject, ~, handles)
% hObject    handle to Matlab_Path (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Matlab_Path as text
%        str2double(get(hObject,'String')) returns contents of Matlab_Path as a double
oldpath = get(hObject,'string');
newpath = uigetdir(oldpath,'Selected Data Directory');
if isstr(newpath)
    set(hObject,'string',newpath);
    if length(newpath) > 2 && newpath(2) == ':'
        cwp = '';
        for cp = { 'C:\cygwin', 'C:\cygwin.hide', 'C:\cygwin64' }
            cwpt = [cp{1} '\bin\cygpath.exe'];
            if exist(cwpt,'file')
                cwp = cwpt;
                break;
            end
        end
        if ~isempty(cwp)
            [status, icosfit_path] = unix([cwp ' -u ' newpath]);
            if status == 0
                if icosfit_path(end) == 10
                    icosfit_path = icosfit_path(1:end-1);
                end
                set(handles.ICOSfit_Path, 'string', icosfit_path);
            else
                error('Bad status from cygpath: %d', status);
            end
        else
            warning('Unable to locate cygpath: guessing');
            icosfit_path = ['/cygdrive/' newpath(1) newpath(3:end) ];
            set(handles.ICOSfit_Path, 'string', icosfit_path);
        end
    else
        set(handles.ICOSfit_Path, 'string', newpath);
    end
end

% --- Executes during object creation, after setting all properties.
function Matlab_Path_CreateFcn(hObject, ~, ~)
% hObject    handle to Matlab_Path (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ICOSfit_Path_Callback(~, ~, ~)
% hObject    handle to ICOSfit_Path (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ICOSfit_Path as text
%        str2double(get(hObject,'String')) returns contents of ICOSfit_Path as a double


% --- Executes during object creation, after setting all properties.
function ICOSfit_Path_CreateFcn(hObject, ~, ~)
% hObject    handle to ICOSfit_Path (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function WavesFile_Callback(~, ~, ~)
% hObject    handle to WavesFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of WavesFile as text
%        str2double(get(hObject,'String')) returns contents of WavesFile as a double


% --- Executes during object creation, after setting all properties.
function WavesFile_CreateFcn(hObject, ~, ~)
% hObject    handle to WavesFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ScanDir_Callback(~, ~, ~)
% hObject    handle to ScanDir (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ScanDir as text
%        str2double(get(hObject,'String')) returns contents of ScanDir as a double


% --- Executes during object creation, after setting all properties.
function ScanDir_CreateFcn(hObject, ~, ~)
% hObject    handle to ScanDir (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(~, ~, ~)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, ~, ~)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Save_btn.
function Save_btn_Callback(hObject, ~, handles)
% hObject    handle to Save_btn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
ICOSfit_cfg.WavesFile = get(handles.WavesFile,'String');
ICOSfit_cfg.Matlab_Path = get(handles.Matlab_Path,'String');
ICOSfit_cfg.ICOSfit_Path = get(handles.ICOSfit_Path,'String');
ICOSfit_cfg.ScanDir = get(handles.ScanDir,'String');
handles.output = ICOSfit_cfg;
guidata(hObject, handles);
SaveDirs = get(handles.SaveDir,'String');
SaveDir = SaveDirs{get(handles.SaveDir,'value')};
fd = fopen([ SaveDir '/ICOSfit_Config.m'], 'w');
fprintf(fd, 'function ICOSfit_cfg = ICOSfit_Config\n');
fprintf(fd, '% ICOSfit_Config defines local configuration\n');
fprintf(fd, 'ICOSfit_cfg.Matlab_Path = ''%s'';\n', ICOSfit_cfg.Matlab_Path );
fprintf(fd, 'ICOSfit_cfg.ICOSfit_Path = ''%s'';\n', ICOSfit_cfg.ICOSfit_Path );
fprintf(fd, 'ICOSfit_cfg.WavesFile = ''%s'';\n', ICOSfit_cfg.WavesFile );
fprintf(fd, 'ICOSfit_cfg.ScanDir = ''%s'';\n', ICOSfit_cfg.ScanDir );
fclose(fd);
clear ICOSfit_Config
uiresume(handles.figure1);


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(~, ~, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
uiresume(handles.figure1);
