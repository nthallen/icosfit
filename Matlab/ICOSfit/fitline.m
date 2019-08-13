function lo_out = fitline( varargin )
% fitline; start up the gui
% line_obj = fitline('load'); 
% fitline('update_regions', name, scan[, ...]);
% fitline('show_regions');
% fitline(args) various callback functions

% Update to support suffixes
%  Add 'suffix' to line_obj
%  On 'Save' save to fitline.mat and to fitline.$suffix.mat
%  List options for suffix from dir fitline.*.mat
%  Provide menu item to create a new suffix. This writes
%  fitline.$suffix.mat and recalculates the suffix options
%  Selecting a suffix from the menu loads the info from
%  fitline.$suffix.mat. This does *not* modify regions
%  or cur_region but does affect lines and all the other
%  modifiable parameters

filename = 'fitline.mat';
load_only = 0;
updt_regions = 0;
show_regions = 0;
if nargin > 0
  if strcmp(varargin{1},'load')
      load_only = 1;
      if nargin > 1
        filename = varargin{2};
      end
  elseif strcmp(varargin{1},'update_regions')
      load_only = 1;
      updt_regions = 1;
  elseif strcmp(varargin{1},'show_regions')
      load_only = 1;
      show_regions = 1;
  end
end
if nargin == 0 || load_only
  % initialize the GUI
  % Could check to see if the GUI is already running, but
  % we might actually want more than one open at a time.
  % Look for fitline.mat in the current directory or the
  % parent directory
  if exist( filename, 'file' )
    load(filename); % defines line_obj
  elseif exist(['../' filename], 'file')
    load(['../' filename]); % defines line_obj
    if exist('line_obj', 'var')
      line_obj.Regions = [];
      line_obj.Regions.name = 'all';
      line_obj.Regions.scan = [];
      line_obj.CurRegion = 1;
      line_obj.Suffix = '';
    end
  end
  if exist( 'line_obj', 'var' )
    if iscell(line_obj.lines)
      line_obj.lines = line_obj.lines{1};
    end
    % This is for backwards compatibility:
    if ~isfield(line_obj.Regions,'scan')
        if isfield(line_obj.Regions,'cpci')
            for i=1:length(line_obj.Regions)
                line_obj.Regions(i).scan = line_obj.Regions(i).cpci;
            end
            line_obj.Regions = rmfield(line_obj.Regions,'cpci');
        else
            line_obj.Regions(1).scan = [];
        end
    end
  else
    fl = { 'fitline.dat', '../fitline.dat' };
    for i=1:length(fl)
      if exist( fl{i}, 'file' )
        lines = load(fl{i});
        break;
      end
    end
    if ~exist( 'lines', 'var' )
      error('Unable to locate fitline.dat');
    end
    hitran = cell(size(lines,1),1);
    for i=1:size(lines,1)
      hitran{i} = lines(i,:);
    end
    line_obj.lines = struct('hitran', hitran, ...
        'en', 1, 'fd', 1, 'fl', 1, 'ml', 1, 'fp', 0, 'te', 0, 'th', 0 );
%      line_st(i) = struct('hitran', {lines(i,:)}, ...
%        'en', 1, 'fd', 1, 'fl', 1, 'ml', 1, 'fp', 0, 'te', 0, 'th', 0 );
%    end
%    line_obj.lines = line_st; % was { line_st };
    line_obj.Threshold = 1e-6;
    line_obj.PTEFile = 'PTE.txt';
    line_obj.Baseline = 'sbase.cubic';
    line_obj.Regions.name = 'all';
    line_obj.Regions.scan = [];
    line_obj.CurRegion = 1;
    save fitline.mat line_obj
  end
  if ~isfield(line_obj,'Suffix')
    line_obj.Suffix = '';
  end
  if isfield(line_obj,'Filename')
    line_obj = rmfield(line_obj,'Filename');
  end
  line_obj.reg_fig = 0;
  if updt_regions
      line_obj = update_regions(line_obj, varargin{2:end});
  elseif show_regions
      for i = 1:length(line_obj.Regions)
          R = line_obj.Regions(i);
          if isempty(R.scan)
              fprintf(1,'%6s: [ ]\n', R.name);
          else
              fprintf(1,'%6s: [ %5d %5d ]\n', R.name, R.scan(1), R.scan(2));
          end
      end
  end
  if load_only
      if nargout > 0
        lo_out = line_obj;
      end
      return;
  end
  lines = line_obj.lines;
  f = figure('visible','off');
  set(f,'UserData',line_obj,'tag','fitline');
  set(f, 'Name', [ 'fitline' line_obj.Suffix ], 'Numbertitle', 'off');
  h = zeros(length(lines),1);
  height = 100; % Height of the buttons at the bottom
  width = 0;
  for i=1:length(lines)
    mol = isovals(lines(i).hitran(1)*10+lines(i).hitran(2),'name');
    name = sprintf('%.4f: %s', lines(i).hitran(3), mol{1});
    name = strrep( name, '{','');
    name = strrep( name, '}','');
    h(i) = uicontrol( f, 'Style','checkbox','tag','en','UserData',i,'string',name,'value',lines(i).en);
    pos = get(h(i),'extent');
    height = height + pos(4);
    width = max(width,pos(3));
  end
  height = max(height,300); % Height required by righthand buttons
  maxheight = height;
  height = height-20;
  uicontrol(f,'style','text','string','fd','position',[40 height 20 20]);
  uicontrol(f,'style','text','string','fl','position',[60 height 20 20]);
  uicontrol(f,'style','text','string','fp','position',[80 height 20 20]);
  uicontrol(f,'style','text','string','ml','position',[100 height 20 20]);
  uicontrol(f,'style','text','string','en','position',[120 height 20 20]);
  te_x = 220+width;
  uicontrol(f,'style','text','string','Threshold', ...
    'tag','thlbl','position',[te_x height 90 20]);
  for i=1:length(lines)
    pos = get(h(i),'extent');
    height = height - pos(4);
    uicontrol(f,'style','checkbox','tag','fd','UserData',i,'position',[40 height 20 20],'value',lines(i).fd);
    uicontrol(f,'style','checkbox','tag','fl','UserData',i,'position',[60 height 20 20],'value',lines(i).fl);
    uicontrol(f,'style','checkbox','tag','fp','UserData',i,'position',[80 height 20 20],'value',lines(i).fp);
    uicontrol(f,'style','checkbox','tag','ml','UserData',i,'position',[100 height 20 20],'value',lines(i).ml);
    set(h(i),'position',[ 120 height pos(3)+20 pos(4)]);
    uicontrol(f,'style','text','position', [ 140+width height 75 15 ], ...
      'string', sprintf('%.2e', lines(i).hitran(4)));
    te = uicontrol(f,'style','checkbox','tag','te','UserData',i,'position', ...
      [te_x height 20 20],'value',lines(i).te,'Callback','fitline(''te'')');
    if lines(i).te
      add_th(te,0);
    end
  end
  height = height - 40;
  lpos = 40;
  b = uicontrol(f,'style','pushbutton','string','Save','Callback','fitline(''save'')');
  pos = get(b,'extent');
  pos(3) = pos(3)+10;
  set(b,'position',[lpos height pos([3 4]) ]);
  lpos = lpos + pos(3) + 10;
  b = uicontrol(f,'style','pushbutton','string','Save Default','Callback','fitline(''default'')');
  pos = get(b,'extent');
  pos(3) = pos(3)+10;
  set(b,'position',[lpos height pos([3 4]) ]);
  lpos = lpos + pos(3) + 10;
  b = uicontrol(f,'style','pushbutton','string','Enable All','Callback','fitline(''enable'')');
  pos = get(b,'extent');
  pos(3) = pos(3)+10;
  set(b,'position',[lpos height pos([3 4]) ]);
  lpos = lpos + pos(3) + 10;
  b = uicontrol(f,'style','pushbutton','string','Disable All','Callback','fitline(''disable'')');
  pos = get(b,'extent');
  pos(3) = pos(3)+10;
  set(b,'position',[lpos height pos([3 4]) ]);
  % lpos = lpos + pos(3) + 10;

  height = maxheight-40;
  br_x = te_x + 130;
  % width = 0;
  width = max([uitext(f,'Suffix:',br_x, height,'fontweight','bold')
     uitext(f,'PTEFile:',br_x, height-30,'fontweight','bold')
     uitext(f,'BaselineFile:', br_x, height-60,'fontweight','bold')
     uitext(f,'Region:', br_x, height-90,'fontweight','bold' ) ]);
  br_xx = br_x + width;
  line_obj = add_suffix(f,line_obj, [br_xx height 150 20]);
  line_obj = add_browse(f,line_obj,'PTEFile','PTE*.txt','pte',[br_xx height-30 150 20]);
  line_obj = add_browse(f,line_obj,'Baseline','*base*','base',[br_xx height-60 150 20], 1);
  Regions = { line_obj.Regions.name };
  uicontrol(f,'style','popupmenu','string',Regions,'value',line_obj.CurRegion, ...
    'tag','region','position', [br_xx height-90 150 20]);
  uicontrol(f,'style','pushbutton','string','Edit Regions', ...
    'Callback','fitline(''editregions'')', 'position', [br_xx height-130 150 20]);
  uicontrol(f,'style','pushbutton','string','Add Suffix', ...
    'Callback','fitline(''addsuffix'')', 'position', [br_xx height-160 150 20]);
  uicontrol(f,'style','pushbutton','string','Matchline', ...
    'Callback','fitline(''matchline'')', 'position', [br_xx height-190 150 20]);
  % height = height - 220;
  pos = get(f,'position');
  pos(3) = br_xx + 170;
  pos(4) = maxheight + 10;
  set(f,'position', pos, 'resize', 'off', 'Menubar','none',...
    'UserData',line_obj,'visible','on');
  
elseif strcmp(varargin{1},'enable')
  f = get(gcbo,'parent');
  h = findobj(f,'tag','en');
  set(h,'value',1);
elseif strcmp(varargin{1},'disable')
  f = get(gcbo,'parent');
  h = findobj(f,'tag','en');
  set(h,'value',0);
elseif strcmp(varargin{1},'te')
  te = gcbo;
  val = get(te,'value');
  if val
    add_th(te,1);
  else
    rm_th(te);
  end
elseif strcmp(varargin{1},'save') || strcmp(varargin{1},'default')
  f = get(gcbo,'parent');
  line_obj = update_line_obj(f);
  svdir = '';
  if strcmp(varargin{1},'default')
      svdir = '../';
      line_obj.Regions = line_obj.Regions(1);
      line_obj.Regions.name = 'all';
      line_obj.Regions.scan = [];
  end
  if ~isempty(line_obj)
    f_sav = line_obj.reg_fig;
    line_obj.reg_fig = 0;
    save( [svdir 'fitline.mat'], 'line_obj');
    suff = line_obj.Suffix;
    if ~isempty(suff)
      fname = [ svdir 'fitline' suff '.mat' ];
      save( fname, 'line_obj' );
    end
    line_obj.reg_fig = f_sav;
  end
  return
elseif strcmp(varargin{1},'matchline')
  fitline('save');
  f = get(gcbo,'parent');
  line_obj = update_line_obj(f);
  if ~isempty(line_obj)
    matchline('init',line_obj);
  end
  return
elseif strcmp(varargin{1},'editregions')
  f = get(gcbo,'parent');
  line_obj = update_line_obj(f);
  % Create a new figure (or make the current regions figure active)
  if ~isempty(line_obj)
    if (line_obj.reg_fig ~= 0) && ishandle(line_obj.reg_fig)
      set(line_obj.reg_fig,'visible','on');
      figure(line_obj.reg_fig);
      fitline('reg_select',line_obj.reg_fig,line_obj.CurRegion);
    else
      if ~exist(line_obj.PTEFile,'file')
        errordlg(sprintf('PTEFile "%s" not found',line_obj.PTEFile));
        return
      end
      % New figure includes:
      %   two axes to display pressure and dT vs scan
      %   should probably show Y(:,1) as well
      %   'Region:' and popupmenu
      %   'Apply' and 'Save' buttons
      %   uimenus for Region->Create,Delete,Rename
      %   Methods for selecting ranges and zooming
      %     left-clicking in the axes moves the closest boundary
      %     right-clicking zooms out
      %     'Zoom' button zooms in to the current boundary +/- 5%
      % Data needed includes:
      %   Parent figure for callback
      %   Region definitions, current region
      %   data.scan,P,dT
      ro.parent = f;
      line_obj.reg_fig = figure('visible','off','MenuBar','none',...
        'DeleteFcn','fitline(''reg_deletefig'')','UserData',ro);
      set(f,'UserData',line_obj,'DeleteFcn','fitline(''deletefig'')');
      ro.Regions = line_obj.Regions;
      ro.CurRegion = line_obj.CurRegion;
      PTE = load(line_obj.PTEFile);
      ro.data.scan = PTE(:,1);
      ro.data.P = PTE(:,2);
      T = scantime(ro.data.scan);
      ro.data.dT = [0;diff(T)];
      y = 60;
      uicontrol(line_obj.reg_fig,'style','popupmenu','string',{ ro.Regions.name },'value',ro.CurRegion, ...
        'tag','region','position', [30 y 150 20],'Callback','fitline(''reg_select'')');
      x = 200;
      x = x + uitext(line_obj.reg_fig,'[', x, y);
      x = x + uitext(line_obj.reg_fig,'000000', x, y, 'tag','reg_start');
      x = x + uitext(line_obj.reg_fig,':', x, y);
      x = x + uitext(line_obj.reg_fig,'000000', x, y, 'tag', 'reg_end');
      x = x + uitext(line_obj.reg_fig,']', x, y) + 20;
      h = uimenu(line_obj.reg_fig,'Label','Region');
      uimenu(h,'Label','Create','Callback','fitline(''reg_create'')');
      uimenu(h,'Label','Delete','Callback','fitline(''reg_delete'')');
      uimenu(h,'Label','Reset','Callback','fitline(''reg_reset'')');
      uimenu(h,'Label','Save','Callback','fitline(''reg_save'')','Enable','off');
      uimenu(h,'Label','Exit','Callback','fitline(''reg_exit'')');
      h = uimenu(line_obj.reg_fig,'Label','Zoom');
      uimenu(h,'Label','Left','Callback','fitline(''reg_zoom_left'')');
      uimenu(h,'Label','Right','Callback','fitline(''reg_zoom_right'')');
      uimenu(h,'Label','Range','Callback','fitline(''reg_zoom_range'')');
      uimenu(h,'Label','All','Callback','fitline(''reg_zoom_all'')');
      
      set(line_obj.reg_fig,'visible','on','name','Regions','NumberTitle','off');
      drawnow; shg;
      ro.ax(1) = axes('position',[.1 .7 .8 .2 ]);
      if length(ro.data.scan) > 1000
        lstyle = '-';
      else
        lstyle = '.-';
      end
      plot(ro.data.scan,ro.data.P,lstyle);
      set(ro.ax(1),'xticklabel',[]);
      ylabel('Torr');
      ro.ax(2) = axes('position',[.1 .5 .8 .2 ]);
      semilogy(ro.data.scan,ro.data.dT,'-');
      set(ro.ax(2),'YAxisLocation','right','XTickLabel',[]);
      ylabel('sec');
      ro.ax(3) = axes('position',[.1 .3 .8 .2 ]);
      plot(ro.data.scan,PTE(:,5)+PTE(:,8)+PTE(:,10));
      ylabel('fringes');
      xlabel('Scan Number');
      for i=1:3
        % axes(ro.ax(i));
        ylim(ro.ax(i), ylim(ro.ax(i)));
        set(ro.ax(i),'ButtonDownFcn','fitline(''reg_click'')');
      end
      ro.scan = [];
      ro.lines = [];
      ro.modified = 0;
      ro = reg_update_cursor(line_obj.reg_fig, ro);
    end
  end
  return
elseif strcmp(varargin{1},'deletefig')
  f = gcbo;
  line_obj = get(f,'UserData');
  if (line_obj.reg_fig ~= 0) && ishandle(line_obj.reg_fig)
    delete(line_obj.reg_fig);
    line_obj.reg_fig = 0;
  end
  return
elseif strcmp(varargin{1},'reg_deletefig')
  rf = gcbo;
  ro = get(rf,'UserData');
  f = ro.parent;
  line_obj = get(f,'UserData');
  line_obj.reg_fig = 0;
  set(f,'UserData',line_obj);
  return
elseif strcmp(varargin{1},'reg_click')
  ax = gcbo;
  rf = get(ax,'parent');
  seltype = get(rf,'SelectionType');
  ro = get(rf,'UserData');
  if strcmp(seltype,'normal')
    cp = get(ax,'CurrentPoint');
    newx = cp(1,1);
    dist = abs(ro.scan-newx);
    which = find(dist == min(dist), 1 );
    ro.scan(which) = newx;
    ro.modified = 1;
    h = findobj(rf,'Label','Save');
    set(h,'Enable','on');
    ro = reg_update_cursor(rf, ro);
  elseif strcmp(seltype,'alt') %zoom out
    xl = xlim(ro.ax(1));
    xl = mean(xl) + diff(xl)*.75 * [-1 1];
    for i=1:3
      xlim(ro.ax(i),xl);
    end
  end
  return
elseif strcmp(varargin{1},'reg_select')
  if nargin == 3
    rf = varargin{2};
    ro = get(rf,'UserData');
    h = findobj(rf,'tag','region');
  else
    h = gcbo;
    rf = get(gcbo,'parent');
    ro = get(rf,'UserData');
  end
  res = cond_save_region( rf, ro );
  if strcmp(res,'Cancel')
    set(h,'value',ro.CurRegion);
    return
  end
  if strcmp(res,'Yes')
    ro = get(rf,'UserData');
  end
  if nargin == 3
    ro.CurRegion = varargin{3};
    set(h,'value',ro.CurRegion);
  else
    ro.CurRegion = get(h,'value');
  end
  ro.scan = ro.Regions(ro.CurRegion).scan;
  ro = reg_update_cursor( rf, ro );
  xl = [ min(ro.data.scan) max(ro.data.scan) ];
  xl = mean(xl) + diff(xl)*.525*[-1 1];
  for i=1:3
    xlim(ro.ax(i),xl);
  end
  return
elseif strcmp(varargin{1},'reg_zoom_range')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  xl = mean(ro.scan) + diff(ro.scan)*.525*[-1 1];
  for i=1:3
    xlim(ro.ax(i),xl);
  end
elseif strcmp(varargin{1},'reg_zoom_all')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  xl = [ min(ro.data.scan) max(ro.data.scan) ];
  xl = mean(xl) + diff(xl)*.525*[-1 1];
  for i=1:3
    xlim(ro.ax(i),xl);
  end
elseif strcmp(varargin{1},'reg_zoom_right')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  xl = xlim(ro.ax(1));
  xl = ro.scan(2) + diff(xl)*.1*[-1 1];
  for i=1:3
    xlim(ro.ax(i),xl);
  end
elseif strcmp(varargin{1},'reg_zoom_left')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  xl = xlim(ro.ax(1));
  xl = ro.scan(1) + diff(xl)*.1*[-1 1];
  for i=1:3
    xlim(ro.ax(i),xl);
  end
elseif strcmp(varargin{1},'reg_create')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  res = cond_save_region( rf, ro );
  if strcmp(res,'Cancel')
    return
  end
  if strcmp(res,'Yes')
    ro = get(rf,'UserData');
  end
  name = inputdlg('Name:','Region Create',[1 20]);
  if ~isempty(name) && ~isempty(name{1})
    % now check for uniqueness
    if any(strcmp({ro.Regions.name}, name{1}))
      errordlg(['Region name "' name{1} '" already in use']);
    else
      ro.Regions(end+1) = struct( 'name', name{1}, 'scan', [] );
      ro.CurRegion = length(ro.Regions);
      ro.scan = [];
      [ names, ndx ] = sort( {ro.Regions.name} );
      ro.Regions = ro.Regions(ndx);
      ro.CurRegion = find(ndx==ro.CurRegion);
      rh = findobj(rf,'tag','region');
      set(rh,'string',names,'value',ro.CurRegion);
      reg_update_cursor(rf,ro);
    end
  end
  return
elseif strcmp(varargin{1},'reg_save')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  save_region(rf, ro);
  return
elseif strcmp(varargin{1},'reg_exit')
  rf = get(get(gcbo,'parent'),'parent');
  ro = get(rf,'UserData');
  res = cond_save_region(rf, ro);
  if ~strcmp(res,'Cancel')
    set(rf,'Visible','off');
  end
  return
elseif strcmp(varargin{1},'addsuffix')
  [~,rf] = gcbo;
  new_suffix = inputdlg('New Suffix:', 'New Suffix', 1 );
  new_suffix = new_suffix{1};

  % ignore empty string
  if isempty(new_suffix)
    return;
  end

  % add a leading '.' if necessary
  if new_suffix(1) ~= '.'
    new_suffix = [ '.' new_suffix ];
  end
  
  % Require suffix to be all letters and/or numbers
  if any(~(isletter(new_suffix(2:end))|isdigit(new_suffix(2:end))))
    errordlg('Invalid suffix');
    return;
  end
  
  % make sure it hasn't been used already
  so = findobj(rf,'tag','suffix');
  sfs = get(so,'string');
  if any(strcmp(new_suffix,sfs))
    errordlg('Suffix already exists');
    return;
  end
  line_obj = get(rf,'UserData');
  line_obj.Suffix = new_suffix;
  set(rf,'UserData',line_obj);
  fname = [ 'fitline' new_suffix '.mat' ];
  f_sav = line_obj.reg_fig;
  line_obj.reg_fig = 0;
  save(fname, 'line_obj');
  save('fitline.mat', 'line_obj');
  line_obj.reg_fig = f_sav;
  add_suffix(rf,line_obj,[],new_suffix);
  return;
elseif strcmp(varargin{1},'suffixcallback')
  % Update 'Suffix'
  % Load the suffix file and update line_obj with it
  % (we don't update the regions or the line definitions,
  % but we do update all of the line options. Ideally
  % we should check to make sure the line defs are identical)
  [h,rf] = gcbo;
  lo = get(rf,'UserData');
  suff = get(h,'string');
  suff = suff{get(h,'value')};
  lo.Suffix = suff;
  if ~isempty(suff)
    load([ 'fitline' suff '.mat']);
    update_from_line_obj(rf,line_obj);
  else
    set(rf,'UserData',lo);
  end
  set(rf, 'Name', [ 'fitline' lo.Suffix ]);
  return
elseif strcmp(varargin{1},'region')
  lo = fitline('load');
  rno = find(strcmp({lo.Regions.name},varargin{2}));
  if length(rno) ~= 1
    error('Bad region');
  end
  lo_out = lo.Regions(rno).scan;
  PTE = load(lo.PTEFile);
  if isempty(lo_out)
    lo_out = [min(PTE(:,1)) max(PTE(:,1))];
  end
  lo_out = PTE(PTE(:,1)>=lo_out(1) & PTE(:,1)<=lo_out(2),1);
else
  fprintf(1,'fitline(%s)\n', varargin{1} );
end
return

function add_th(te,use_default)
f = get(te,'parent');
line_obj = get(f,'UserData');
lines = line_obj.lines;
i = get(te,'UserData');
if use_default
  thresh = line_obj.Threshold;
else
  thresh = lines(i).th;
end
str = sprintf('%g',thresh);
th = findobj(f,'tag','th','UserData',i);
if ~isempty(th)
  set(th,'string','str');
else
  thlbl = findobj(f,'tag','thlbl');
  lblpos = get(thlbl,'position');
  pos = get(te,'position');
  uicontrol(f,'style','edit','string',str,'tag','th','UserData',i, ...
    'position',[ lblpos(1)+20 pos(2) 70 20 ]);
end
return;

function rm_th(te)
f = get(te,'parent');
i = get(te,'UserData');
h = findobj(f,'tag','th','UserData',i);
if ~isempty(h)
  delete(h);
end
return;


function lo_out = add_browse(f, lo, lofld, pattern, tag, pos, inc_subdirs )
files = dir(pattern);
if nargin >= 7 && inc_subdirs
  sdfiles = dir(['../' pattern]);
  for i=1:length(sdfiles)
    sdfiles(i).name = [ '../' sdfiles(i).name ];
  end
  files = [ files; sdfiles ];
end
files = files(~[files.isdir]);
if isempty(files)
  files = { lo.(lofld) };
else
  files = { files.name };
end
val = find(strcmp(files,lo.(lofld)));
if isempty(val)
  lo.(lofld) = files{1};
  val = 1;
end
uicontrol(f,'style','popupmenu','string',files,'value',val,...
  'position',pos,'tag',tag );
lo_out = lo;
return

function lo_out = add_suffix(f, lo, pos, cursuff)
files = dir('fitline.*.mat');
files = { files.name };
for i=1:length(files)
  files{i} = files{i}(8:end-4);
end
%files = { '', files{:} };
files = [ {''} files ];
if nargin < 4
  cursuff = lo.Suffix;
end
val = find(strcmp(files,cursuff));
if isempty(val)
  h = errordlg( ...
      sprintf('File fitline.%s.mat not found. Using no suffix', ...
      cursuff), ...
      'Suffix configuration not found','modal');
  waitfor(h);
  cursuff = '';
  lo.Suffix = cursuff;
  set(f,'UserData',lo);
  val = 1;
end
if nargin >= 4
  h = findobj(f,'tag','suffix');
  set(h,'string',files,'value',val);
else
  uicontrol(f,'style','popupmenu','string',files,'value',val,...
    'position',pos,'tag','suffix','Callback','fitline(''suffixcallback'')');
end
lo_out = lo;
return

function str = get_popup_val(f, tag)
h = findobj(f,'tag',tag);
strs = get(h,'string');
val = get(h,'value');
str = strs{val};
return

function str = set_popup_val(f, tag, str)
h = findobj(f,'tag',tag);
strs = get(h,'string');
val = find(strcmp(strs,str));
set(h,'value',val);
return

function width = uitext(f,str,x,y,varargin)
% Displays the specified string at the specified position, adjusting
% for it's width
h = uicontrol(f,'style','text','string',str,varargin{:});
ext = get(h,'extent');
set(h,'position', [x y ext([3 4])]);
width = ext(3);
return

function ro_out = reg_update_cursor(rf, ro)
% If ro.scan is empty, initialize it appropriately
% based on ro.Regions.CurRegion
% Given current setting of ro.scan, delete existing
% cursor lines and draw new ones.
if isempty(ro.scan)
  ro.scan = ro.Regions(ro.CurRegion).scan;
  if isempty(ro.scan)
    ro.scan = [ min(ro.data.scan) max(ro.data.scan) ];
  end
end
v = ro.data.scan>=min(ro.scan) & ro.data.scan<=max(ro.scan);
if ~any(v)
  errordlg('Somehow ran out of scans');
  return
end
% idx = find(ro.data.scan>=ro.scan(1), 1 );
% if isempty(idx)
%   errordlg('Somehow ran out of scans on the left');
%   return
% end
% ro.scan(1) = ro.data.scan(idx);
% idx = find(ro.data.scan<=ro.scan(2), 1, 'last' );
% if isempty(idx)
%   errordlg('Somehow ran out of scans on the right');
%   return
% end
% ro.scan(2) = ro.data.scan(idx);
ro.scan = [min(ro.data.scan(v)) max(ro.data.scan(v))];
st_h = findobj(rf,'tag','reg_start');
set(st_h,'string',num2str(ro.scan(1)));
st_h = findobj(rf,'tag','reg_end');
set(st_h,'string',num2str(ro.scan(2)));
for h=ro.lines(:)
  if h > 0
    delete(h);
  end
end
ro.lines = zeros(3,2);
for i=1:3
  % axes(ro.ax(i));
  hold(ro.ax(i), 'on');
  yl = ylim(ro.ax(i));
  ro.lines(i,1) = plot(ro.ax(i), ro.scan(1)*[1 1],yl,'k--');
  ro.lines(i,2) = plot(ro.ax(i), ro.scan(2)*[1 1],yl,'k--');
end
set(rf,'UserData',ro);
ro_out = ro;
return

function ro_out = save_region(rf, ro)
ro.Regions(ro.CurRegion).scan = ro.scan;
f = ro.parent;
line_obj = get(f,'UserData');
line_obj.Regions = ro.Regions;
line_obj.CurRegion = ro.CurRegion;
rh = findobj(f,'tag','region');
set(rh,'string',{ro.Regions.name},'value',ro.CurRegion);
set(f,'UserData',line_obj);
ro.modified = 0;
set(rf,'UserData',ro);
ro_out = ro;
h = findobj(rf,'Label','Save');
set(h,'enable','off');
return

function res = cond_save_region( rf, ro )
if ro.modified
  res = questdlg('Save Changes to Region "all"?','Save Changes?','Yes','No','Cancel','Yes');
  if strcmp(res,'Yes')
    save_region(rf, ro);
  end
else
  res = 'No';
end
return

function line_obj = update_line_obj(f)
line_obj = get(f,'UserData');
fields = { 'en','fd','fl','fp','ml','te' };
for j = 1:length(fields)
  tag = fields{j};
  h = findobj(f,'tag',tag);
  for i = 1:length(h)
    line_obj.lines(get(h(i),'UserData')).(tag) = get(h(i),'value');
  end
end
h = findobj(f,'tag','region');
line_obj.CurRegion = get(h,'value');
h = findobj(f,'tag','th');
for i = 1:length(h)
  val = str2double(get(h(i),'string'));
  ln = get(h(i),'UserData');
  if isnan(val)
    errordlg(sprintf('Invalid threshold for line %d',ln));
    line_obj = [];
    return;
  end
  line_obj.lines(ln).th = val;
end
line_obj.PTEFile = get_popup_val(f,'pte');
line_obj.Baseline = get_popup_val(f,'base');
set(f, 'UserData', line_obj );
return;

function update_from_line_obj(f,line_obj)
fields = { 'en','fd','fl','fp','ml','te' };
for j = 1:length(fields)
  tag = fields{j};
  h = findobj(f,'tag',tag);
  for i = 1:length(h)
    set(h(i),'value', line_obj.lines(get(h(i),'UserData')).(tag));
    if strcmp(tag,'te')
      rm_th(h(i));
    end
  end
end

set_popup_val(f,'pte',line_obj.PTEFile);
set_popup_val(f,'base',line_obj.Baseline);
update_line_obj(f);
lo = get(f,'UserData');
for i = 1:length(line_obj.lines)
  lo.lines(i).th = line_obj.lines(i).th;
end
for fldnam = { 'Threshold', 'PTEFile', 'Baseline', 'Suffix', ...
    'CurRegion' }
  lo.(fldnam{1}) = line_obj.(fldnam{1});
end

% Update suffix screen object
sfx = findobj( f, 'tag', 'suffix' );
sfxs = get(sfx,'String');
sfxn = find(strcmp(sfxs,lo.Suffix));
set(sfx,'value',sfxn);

% Update PTEFile screen object
ptex = findobj( f, 'tag', 'pte' );
ptes = get(ptex,'String');
pten = find(strcmp(ptes,lo.PTEFile));
set(ptex,'value',pten);

% Update Baseline screen object
bsx = findobj( f, 'tag', 'base' );
bss = get(bsx,'String');
bsn = find(strcmp(bss,lo.Baseline));
set(bsx,'value',bsn);

% Update Region on Screen
regx = findobj( f, 'tag', 'region' );
set( regx, 'value', lo.CurRegion );

set( f, 'UserData', lo );

hte = findobj(f,'tag','te');
for h = hte'
  val = get(h,'value');
  if val
    add_th(h,0);
  else
    rm_th(h);
  end
end
return;

function line_obj = update_regions(line_obj, varargin)
% add_regions( name, scan[, ...])
for i=1:2:length(varargin)-1
    n = find(strcmp({line_obj.Regions.name}, varargin{i}));
    if isempty(n)
        line_obj.Regions(end+1) = ...
            struct('name', varargin{i}, 'scan', varargin{i+1});
    else
        line_obj.Regions(n).scan = varargin{i+1};
    end
end
save fitline.mat line_obj
return;
