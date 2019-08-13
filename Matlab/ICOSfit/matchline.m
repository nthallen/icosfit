function matchline( op, line_obj )
% matchline( op[, lo] );
% matchline( 'init', lo );
% matchline( 'next' );
% matchline( 'prev' );
% matchline( 'save' );
%
% lo is a line_obj struct from fitline.
%
% Requires:
%   fitline.mat in the current or parent directory.
%   Cell_Config.m in the current or parent directory
%   PTE file specified in fitline.mat in the current directory
%   A skew baseline file sbase*.dat in the current directory
%   icosfit 2.2c or later (uses 'nu0' keyword)
% Local Configuration Items:
%   Matlab_Path
%   ICOSfit_Path

% Update from matchline6a() using line definitions to decide optimal
% fit parameters:
%  hlf = max(ceil(2.5 * voigt_half_width)) (was '24')
%  mfhw = min(ceil(.2 * voigt_half_width)) (was '1')
%  cv_hlf = max(ceil(voigt_half_width))    (was '10')
%  cv_mfhw = 1;                            (was '1')
cellparams=load_cell_cfg;
EtalonFSR = cellparams.fsr; % .019805;
if nargin == 0 || strcmp(op,'init')
  if nargin == 1
    line_obj = fitline('load');
  end
  CavityLength = cellparams.CavityLength;
  CavityFixedLength = cellparams.CavityFixedLength;
  N_Passes = cellparams.N_Passes;
  MirrorLoss = cellparams.MirrorLoss;
  run = getrun(1);
  if ~exist(line_obj.PTEFile,'file')
    errordlg(sprintf('PTEFile "%s" missing', line_obj.PTEFile));
    return
  end
  ICOSfit_cfg = load_ICOSfit_cfg;
  
  % Always load PT now to get waveform information
  PT = load_mat_files('PT', 'PandT');
  PTE = load(line_obj.PTEFile);
  WaveSpecs = load_waves;
  isicos = [ WaveSpecs.ISICOS ];
  ISICOS = isicos(PT.QCLI_Wave+1);
  if size(ISICOS,2) > 1, ISICOS = ISICOS'; end
  scannum = PT.ScanNum;
  ScanNum = line_obj.Regions(line_obj.CurRegion).scan;
  if isempty(ScanNum)
    ScanNum = scannum([ find(scannum>0 & ISICOS,1) find(scannum>0 & ISICOS,1,'last') ]);
  end
  idx = find(PTE(:,1)>=ScanNum(1) & PTE(:,1)<=ScanNum(2),1);
  if all(diff(PTE(:,1))<0)
    ScanNum(2) = PTE(idx,1);
  else
    ScanNum(1) = PTE(idx,1);
  end
  scan_start = PTE(idx,1);
  idx = find(scannum >= scan_start, 1);
  QCLI_Wave = PT.QCLI_Wave(idx);
  if length(ScanNum) < 2
    nxt_scan = scannum(find(scannum > ScanNum(1) & PT.QCLI_Wave ~= QCLI_Wave,1))-1;
    if isempty(nxt_scan)
      nxt_scan = max(scannum);
    end
    ScanNum(2) = nxt_scan;
  end
  
  % Find
  wv = waves_used(ScanNum(1):ScanNum(2));
  if length(wv) > 1
    waves_used(ScanNum(1):ScanNum(2));
    errordlg('More than one waveform used in specified range');
    return
  end
  if ~wv.ISICOS
    disp(wv);
    errordlg('Specified scan is not an ICOS scan');
    return;
  end
  SampleRate = round(wv.RawRate/wv.NAverage);
  % fprintf(1,'Waveform is %s\n',wv.Name);
  
  [ holdoff, x, LineMargin, LineMarginMultiplier ] = get_waveform_params( wv.Name, ...
    'holdoff', 4e-4, ...
    'SignalRegion', [], ...
    'LineMargin', 0.05, 'LineMarginMultiplier',8 );
  if isempty(x)
    startsample = round(wv.TzSamples + holdoff*SampleRate);
    endsample = wv.NetSamples - wv.TzSamples - 1;
    x = (startsample:endsample)';
  end
  if size(x,2)>1
    x = x'; % make sure it's a column vector
  end

  % mfhw = 5;
  % Ndens = [ 1 0 0 0 0 0 ]; % Need a hook here for relative number density
  Ndens = [ 1 0 0 1e-4 0 1e-4 ]; % Need a hook here for relative number density
  % run = getrun(1);
  
  try
    % fe = scanload( scan_start );
    % f = fe(x,1);
    f = loadscans([], scan_start, x);
  catch err
    errordlg(err);
    return
  end
  
  % resample to wavenumber scale
  % x -    sample numbers
  % xx -   1:n_samples - changed to index of subset of
  %        samples inside the result of fitfringe()
  % wvno - pseudo wavenumber scale
  %
  % Resample:
  % rswvno - covers the range of the lines
  % lineabs - absorption at rswvno based on lines
  % rsabswvno - covers the same range as wvno but at the
  %             same resolution as rswvno
  % rsabsorb - resampled absorption
  i = find(PTE(:,1)==ScanNum(1),1);
  if isempty(i)
    errordlg(sprintf('ScanNum %d not found in PTE.txt',ScanNum(1)));
    return
  end

  T = PTE(i,3); % Kelvin
  P = PTE(i,2); % Torr
  lines = reshape([ line_obj.lines.hitran ],9,[])';
  % lines = lines(find([ line_obj.lines.ml ]),:);
  lines = lines( [line_obj.lines.ml] ~= 0, : );

  % Line width calculations copied from ICOSsetup.m
  iso = lines(:,1)*10 + lines(:,2);
  molwts = isovals(iso,'weight');
  Gair = lines(:,5); % air-broadend halfwidth at Tref, Pref
  Pdelta = lines(:,8);
  linenu = lines(:,3);
  linewvno = linenu + Pdelta * (P/760.); % corrected for pressure shift...
  Gedcalc = 4.30213e-7 * linenu .* sqrt(T./molwts);
  STdep = lines(:,7);
  T0 = 296.;
  Glcalc = ((T0./T).^STdep) .* Gair .* (P/760.);
  Gvcalc = 0.5346*Glcalc + ...
    sqrt( 0.2166 * Glcalc.*Glcalc + .69315*Gedcalc.*Gedcalc);

  wvno = -etln_evalJ(PTE(i,5:11),(x-PTE(i,4)+1)/1000)*EtalonFSR;
  wvno = wvno - max(wvno);
  resolution = min(abs(diff(wvno)))/2;
  N = ceil((max(linewvno+3*Gvcalc)-min(linewvno-3*Gvcalc))/resolution);
  rswvno = (-1:N+1)*resolution + min(linewvno-3*Gvcalc);
  % resample (wvno,absorb) and extend to match linex.
  %nptsabs = floor((max(wvno)-min(wvno))/resolution);
  %rsabswvno = -(nptsabs:-1:0)*resolution;
  
  hlf = max(ceil( 1.8 * Gvcalc / resolution ));
  mfhw = min(ceil( .05 * Gvcalc / resolution ));

  [ vpk, vb ] = peakfind( f, hlf, mfhw, .02 ); % was 24, 1: need to add hook
  if size(vpk,1) > 0
    base = f;
    npeaks = size(vpk,1);
    % now generate a crude baseline by skipping over peaks
    vpk2 = [ 0 0 1; vpk; size(f,1) 0 0 ];
    for i = 1:npeaks+1
      vx = vpk2(i,3):vpk2(i+1,1);
      base(vx) = fmedianf(base(vx),mfhw);
    end
    if any(vb)
      base(~vb) = interp1(x(vb),base(vb),x(~vb),'linear','extrap');
    end
    absorb = log( base./f );

    linex = floor(((linewvno - rswvno(1))/resolution) + 1.5 );
    % use linex to initialize a vector of line positions
    lineabs = zeros(size(rswvno));

    % Automatically include enabled lines at full strength
    if max(lines(:,1)) > length(Ndens)
      Ndens = [ Ndens ones(1,max(lines(:,1))-length(Ndens)) ];
    end
    if any(Ndens(lines(:,1))==0)
      Ndens(lines(Ndens(lines(:,1))==0,1)) = 1;
    end
    lineabs(linex) = lines(:,4).*Ndens(lines(:,1))';
    lineabs(linex) = lineabs(linex)/max(lineabs(linex));
    % resample (wvno,absorb) and extend to match linex.
    nptsabs = floor((max(wvno)-min(wvno))/resolution);
    rsabswvno = -(nptsabs:-1:0)*resolution;
    rsabsorb = interp1( wvno, absorb, rsabswvno );
    % then do a correlation and see what we get.

    cv = conv(fliplr(rsabsorb),lineabs);
    % pk = find(cv == max(cv));
    cvx = (0:length(cv)-1)*resolution + rswvno(1);
    cv_hlf = max(ceil( .8 * Gvcalc / resolution ));
    cv_mfhw = 1;
    cvpk = peakfind( -cv', cv_hlf, cv_mfhw, .05 );
    pkht = cv(cvpk(:,2));
    [ ~, I ] = sort(-pkht);
    spk = cvpk(I,2);
    if size(spk,1)>1
      spk = spk';
    end

  else
    spk = [];
    base = [];
    cvx = [];
    % errordlg('peakfind found no peaks: You may need to adjust the threshold');
    % return
    %else
    %disp([ 'peakfind detected ' num2str(size(vpk,1)) ' peaks' ]);
  end
  ml_obj.line_obj = line_obj;
  ml_obj.Ndens = Ndens;
  ml_obj.spk = spk;
  ml_obj.wvno = wvno;
  ml_obj.linewvno = linewvno;
  ml_obj.x = x;
  ml_obj.f = f;
  ml_obj.base = base;
  ml_obj.cvx = cvx;
  ml_obj.cur_pk = 1;
  ml_obj.ScanNum = ScanNum;
  ml_obj.QCLI_Wave = QCLI_Wave;
  ml_obj.wv = wv;
  ml_obj.LineMargin = LineMargin;
  ml_obj.LineMarginMultiplier = LineMarginMultiplier;
  ml_obj.SampleRate = SampleRate;
  ml_obj.MirrorLoss = MirrorLoss;
  ml_obj.EtalonFSR = cellparams.fsr;
  ml_obj.CavityLength = CavityLength;
  ml_obj.CavityFixedLength = CavityFixedLength;
  ml_obj.N_Passes = N_Passes;
  ml_obj.run = run;
  ml_obj.ICOSfit_cfg = ICOSfit_cfg;
  if size(spk,1) == 0
    button = questdlg('No Lines Found: Create icosfit file anyway?','Error', ...
      'Yes', 'No', 'Yes' );
    if strcmp(button,'Yes')
      save_icosfit(ml_obj);
    end
  else
    fig = figure;
    ml_obj.ax = axes('position', [.1 .5 .8 .4 ]);
    set(fig,'UserData',ml_obj,'Name', 'matchline', 'Numbertitle', 'off');
    uicontrol(fig,'style','pushbutton','string','Next','Callback','matchline(''next'')',...
      'tag','next','position',[40 60 60 20]);
    uicontrol(fig,'style','pushbutton','string','Prev','Callback','matchline(''prev'')',...
      'tag','prev','enable','off','position',[110 60 60 20]);
    uicontrol(fig,'style','pushbutton','string','Save','Callback','matchline(''save'')',...
      'tag','save','position',[180 60 60 20]);
    draw_lines(ml_obj);
  end
  return;
else
  fig = get(gcbo,'parent');
  ml_obj = get(fig,'UserData');
  if strcmp(op,'next')
    if ml_obj.cur_pk < length(ml_obj.spk)
      ml_obj.cur_pk = ml_obj.cur_pk+1;
      set(fig,'UserData',ml_obj);
    end
    draw_lines(ml_obj);
    return
  elseif strcmp(op,'prev')
    if ml_obj.cur_pk > 1
      ml_obj.cur_pk = ml_obj.cur_pk-1;
      set(fig,'UserData',ml_obj);
    end
    draw_lines(ml_obj);
    return
  elseif strcmp(op,'save')
    save_icosfit(ml_obj);
    delete(fig);
    return
  else
    fprintf(1,'matchline(%s)\n', op);
    return
  end
end
end

function draw_lines(ml_obj)
fig = get(ml_obj.ax,'parent');
axes(ml_obj.ax);
cla;
XV = polyfit(ml_obj.x,ml_obj.base,1);
Xy = polyval(XV,ml_obj.x);
plot(ml_obj.x, ml_obj.f-Xy, ml_obj.x, ml_obj.base-Xy);
hold on;
pk = ml_obj.spk(ml_obj.cur_pk);

% now rsabswvno+cvx(pk) is a true wavenumber scale for rsabsorb,
% which means that wvno+cvx(pk) is a true wavenumber scale for
% absorb, and we can find line positions in sample units by
% interpolating:
linesample = floor(interp1(ml_obj.wvno+ml_obj.cvx(pk),ml_obj.x,ml_obj.linewvno)+.5);
linebase = interp1(ml_obj.x,ml_obj.base,linesample);
ln_idx = find([ml_obj.line_obj.lines.ml]);
for i=1:length(linesample);
  if ml_obj.Ndens(ml_obj.line_obj.lines(ln_idx(i)).hitran(1)) > 0
    plot([linesample(i) linesample(i)], ...
      [min(ml_obj.f-Xy) linebase(i)-polyval(XV,linesample(i))], 'r'); 
  end
end
hold off;
title(sprintf('Match %d of %d',ml_obj.cur_pk,length(ml_obj.spk)));
h = findobj(fig,'tag','next');
if ml_obj.cur_pk >= length(ml_obj.spk)
  set(h,'enable','off');
else
  set(h,'enable','on');
end
h = findobj(fig,'tag','prev');
if ml_obj.cur_pk > 1
  set(h,'enable','on');
else
  set(h,'enable','off');
end

return;
end

function save_icosfit(ml_obj)
% now rsabswvno+cvx(pk) is a true wavenumber scale for rsabsorb,
% which means that wvno+cvx(pk) is a true wavenumber scale for
% absorb, and we can find line positions in sample units by
% interpolating:
if size(ml_obj.spk,1) == 0
  linesample = 0 * ml_obj.linewvno;
else
  pk = ml_obj.spk(ml_obj.cur_pk);
  linesample = floor(interp1(ml_obj.wvno+ml_obj.cvx(pk),ml_obj.x,ml_obj.linewvno)+.5);
end

ScanNum = ml_obj.ScanNum;
reg_name = ml_obj.line_obj.Regions(ml_obj.line_obj.CurRegion).name;
suffix = ml_obj.line_obj.Suffix;
ofile = [ 'icosfit.' reg_name suffix ];
ofile = inputdlg({'Filename:'},'Matchline Save',1,{ofile});
if isempty(ofile)
  return
end
fid = fopen( ofile{1},'w');
if fid == -1
  errordlg( sprintf('Unable to write to output file "%s"', ofile{1}) );
end
fprintf( fid, '# Configuration for %s region %s line set %s\n', ...
  ml_obj.run, reg_name, suffix );
fprintf( fid, 'Verbosity = 1;\n' );
fprintf( fid, 'QCLI_Wave = %d; # Waveform %s\n', ml_obj.QCLI_Wave, ml_obj.wv.Name );
fprintf( fid, 'ScanNumRange = [ %d, %d ];\n', ScanNum(1), ScanNum(2) );
fprintf( fid, 'SignalRegion = [ %d, %d ];\n', min(ml_obj.x), max(ml_obj.x) );
fprintf( fid, 'BackgroundRegion = [ %d, %d ];\n', 5, ml_obj.wv.TzSamples );
% fprintf( fid, 'MinimumFringeSpacing = %.1f;\n', min(diff(frx)));
fprintf( fid, 'SampleRate = %d Hz;\n', ml_obj.SampleRate );
fprintf( fid, 'Threshold = %g;\n', ml_obj.line_obj.Threshold );
fprintf( fid, '# Fix Doppler;\n' );
fprintf( fid, '# Fix Lorentz;\n' );
fprintf( fid, 'nu0 = %d;\n', floor(min(ml_obj.linewvno)));
fprintf( fid, 'Lines = {\n' );
ldefs = ml_obj.line_obj.lines;
lines = reshape([ ldefs.hitran ],9,[])';
ml = [ ldefs.ml ];
lsidx = cumsum(ml);
for i=1:size(lines,1)
  if ldefs(i).en
    fprintf(fid,' ');
  else
    fprintf(fid,'#');
  end
  fprintf(fid, ...
    '%2d %d %12.6f %10.3e %5.4f %10.4f %4.2f %9.6f %d', ldefs(i).hitran );
  if ml(i) && ~isnan(linesample(lsidx(i)))
    fprintf(fid, ', Position=%d', linesample(lsidx(i)) );
  end
  if ldefs(i).fd
    fprintf(fid, ', Fix Doppler' );
  end
  if ldefs(i).fl
    fprintf(fid, ', Fix Lorentz' );
  end
  if ldefs(i).fp
    fprintf(fid, ', Float FinePosition' );
  end
  if ldefs(i).te
    fprintf(fid, ', Threshold = %.1e', ldefs(i).th );
  end
  fprintf(fid, ';\n' );
end
fprintf( fid, '};\n\n%s\n', ...
  '# DSFRLimits = [ .90, 1.26 ];');

fprintf( fid, 'LineMargin = %.2f cm-1;\n', ml_obj.LineMargin );
fprintf( fid, 'LineMarginMultiplier = %d;\n', ml_obj.LineMarginMultiplier );
fprintf( fid, 'MirrorLoss = %.1f ppm;\n', ml_obj.MirrorLoss );
fprintf( fid, 'CavityLength = %.3f;\n', ml_obj.CavityLength );
if ml_obj.N_Passes > 0
  fprintf( fid, 'CavityFixedLength = %.3f;\n', ml_obj.CavityFixedLength ); 
  fprintf( fid, 'N_Passes = %d;\n', ml_obj.N_Passes );
end
fprintf( fid, 'EtalonFSR = %.6f cm-1;\n', ml_obj.EtalonFSR );
fprintf( fid, '%s\n%s\n',...
  'Binary;', ...
  [ 'ICOSdir = ' find_scans_dir('',1) ';' ] );
fprintf( fid, 'PTEFile = %s;\n', ml_obj.line_obj.PTEFile );
fprintf( fid, 'BaselineFile = %s;\n', ml_obj.line_obj.Baseline );
fprintf( fid, 'OutputDir = ICOSout.%s%s;\n', reg_name, suffix );
fprintf( fid, '%s\n%s\n', ...
  'OutputFile = ICOSsum.dat;', ...
  'LogFile = ICOSfit.log;' );

fclose(fid);
disp( ['Output written to ' ofile{1} ] );

edit(ofile{1});
return;
end
