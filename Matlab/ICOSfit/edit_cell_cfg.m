function varargout = edit_cell_cfg(varargin)
% edit_cell_cfg;
% edit_cell_cfg('Config','Cell_Config.m');
%
% edit_cell_cfg M-file for edit_cell_cfg.fig
%      edit_cell_cfg, by itself, creates a new edit_cell_cfg or raises the existing
%      singleton*.
%
%      H = edit_cell_cfg returns the handle to a new edit_cell_cfg or the handle to
%      the existing singleton*.
%
%      edit_cell_cfg('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in edit_cell_cfg.M with the given input arguments.
%
%      edit_cell_cfg('Property','Value',...) creates a new edit_cell_cfg or raises the
%      existing singleton.  Starting from the left, property value pairs are
%      applied to the GUI before edit_cell_cfg_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to edit_cell_cfg_OpeningFcn via varargin.
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help edit_cell_cfg

% Last Modified by GUIDE v2.5 28-Nov-2012 10:01:10

% Begin initialization code - DO NOT EDIT
gui_Singleton = 0;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @edit_cell_cfg_OpeningFcn, ...
                   'gui_OutputFcn',  @edit_cell_cfg_OutputFcn, ...
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


% --- Executes just before edit_cell_cfg is made visible.
function edit_cell_cfg_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to edit_cell_cfg (see VARARGIN)

% Choose default command line output for edit_cell_cfg
loaded = 0;
for i=1:2:length(varargin)-1
  if strcmpi(varargin{i},'Config')
      cell_cfg = varargin{i+1};
      loaded = 1;
  else
      errordlg(sprintf('Unrecognized property: %s', varargin{i}));
      close(handles.figure1);
      return;
  end
end
if ~loaded
  cell_cfg = load_cell_cfg(1);
end
set(handles.N_Passes,'String', cell_cfg.N_Passes);
set(handles.CavityLength,'String',cell_cfg.CavityLength);
set(handles.fsr,'String',cell_cfg.fsr);
set(handles.MirrorLoss,'String',cell_cfg.MirrorLoss);
S{1} = pwd;
cd ..
S{2} = pwd;
cd ..
S{3} = pwd;
cd(S{1});
set(handles.SaveDir, 'String', S, 'value', 1);
handles.output = cell_cfg;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes edit_cell_cfg wait for user response (see UIRESUME)
uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = edit_cell_cfg_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
delete(handles.figure1);

function CavityLength_Callback(hObject, eventdata, handles)
% hObject    handle to CavityLength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CavityLength as text
%        str2double(get(hObject,'String')) returns contents of CavityLength as a double


% --- Executes during object creation, after setting all properties.
function CavityLength_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CavityLength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function fsr_Callback(hObject, eventdata, handles)
% hObject    handle to fsr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of fsr as text
%        str2double(get(hObject,'String')) returns contents of fsr as a double


% --- Executes during object creation, after setting all properties.
function fsr_CreateFcn(hObject, eventdata, handles)
% hObject    handle to fsr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function N_Passes_Callback(hObject, eventdata, handles)
% hObject    handle to N_Passes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N_Passes as text
%        str2double(get(hObject,'String')) returns contents of N_Passes as a double


% --- Executes during object creation, after setting all properties.
function N_Passes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N_Passes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function MirrorLoss_Callback(hObject, eventdata, handles)
% hObject    handle to MirrorLoss (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of MirrorLoss as text
%        str2double(get(hObject,'String')) returns contents of MirrorLoss as a double


% --- Executes during object creation, after setting all properties.
function MirrorLoss_CreateFcn(hObject, eventdata, handles)
% hObject    handle to MirrorLoss (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function CavityFixedLength_Callback(hObject, eventdata, handles)
% hObject    handle to CavityFixedLength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of CavityFixedLength as text
%        str2double(get(hObject,'String')) returns contents of CavityFixedLength as a double


% --- Executes during object creation, after setting all properties.
function CavityFixedLength_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CavityFixedLength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in Save_btn.
function Save_btn_Callback(hObject, eventdata, handles)
% hObject    handle to Save_btn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
cell_cfg.fsr = get(handles.fsr,'String');
cell_cfg.CavityLength = get(handles.CavityLength,'String');
cell_cfg.MirrorLoss = get(handles.MirrorLoss,'String');
cell_cfg.N_Passes = get(handles.N_Passes,'String');
cell_cfg.CavityFixedLength = get(handles.CavityFixedLength,'String');
handles.output = cell_cfg;
guidata(hObject, handles);
SaveDirs = get(handles.SaveDir,'String');
SaveDir = SaveDirs{get(handles.SaveDir,'value')};
fd = fopen([ SaveDir '/Cell_Config.m'], 'w');
fprintf(fd, 'function cell_cfg = Cell_Config\n');
fprintf(fd, '% ICOSfit_Config defines local configuration\n');
fprintf(fd, 'cell_cfg.fsr = %s;\n', cell_cfg.fsr );
fprintf(fd, 'cell_cfg.CavityLength = %s;\n', cell_cfg.CavityLength );
fprintf(fd, 'cell_cfg.MirrorLoss = %s;\n', cell_cfg.MirrorLoss );
fprintf(fd, 'cell_cfg.N_Passes = %s;\n', cell_cfg.N_Passes );
fprintf(fd, 'cell_cfg.CavityFixedLength = %s;\n', cell_cfg.CavityFixedLength );
fclose(fd);
uiresume(handles.figure1);


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
uiresume(handles.figure1);
