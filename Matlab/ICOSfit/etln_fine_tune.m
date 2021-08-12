classdef etln_fine_tune < handle
  properties
    PTE
    scans
    ibase
    obase
    x
    xx
    xx2
    xx3
    si
    x0
    fsr
    verbose
    Nsmooth
  end
  methods
    function eft = etln_fine_tune(PTEfile, scans, obase_suffix)
      % eft = etln_fine_tune(PTEfile[, scans[, obase_suffix]])
      % scans defaults to all scans in PTEfile
      % obase_suffix defaults to 'f'
      % scans can be empty in order to specify obase_suffix
      if nargin < 3; obase_suffix = 'f'; end
      eft.verbose = false;
      eft.PTE = load(PTEfile);
      eft.ibase = find_scans_dir;
      eft.obase = [ eft.ibase obase_suffix ];
      if nargin < 2 || isempty(scans)
        scans = eft.PTE(:,1);
      else
        if isrow(scans); scans = scans'; end
      end
      eft.scans = scans;
      wvs = waves_used(eft.scans);
      if length(wvs) ~= 1; error('Length wvs (%d) ~= 1', length(wvs)); end
      eft.si = interp1(eft.PTE(:,1),1:size(eft.PTE,1),eft.scans,'nearest','extrap');
      if any(eft.PTE(eft.si,1) ~= eft.scans); error('Not all scans found in PTEfile'); end
      eft.x = (eft.PTE(1,4):(wvs.NetSamples - wvs.TzSamples))';
      eft.xx = (eft.x-eft.x(1)+1)/1000;
      eft.xx2 = eft.xx.^2;
      eft.xx3 = eft.xx.^3;
      eft.x0 = get_waveform_params(wvs.Name, 'BackgroundRegion', 5:wvs.TzSamples);
      cell_cfg = load_cell_cfg;
      eft.fsr = cell_cfg.fsr;
      eft.Nsmooth  = 100;
    end
    
    function tune_scans(eft, nscans)
      % eft.tune_scans([nscans])
      % nscans defaults to all scans in the PTE file.
      if nargin < 2; nscans = length(eft.scans); end
      for i=1:nscans
        scan = eft.scans(i);
        Y = eft.Y(i);
        pi = mlf_path(eft.ibase,scan);
        [fi,hdr] = loadbin(pi);
        if isempty(fi)
          warning('File not found: %d => %s', scan, eft.ibase);
        else
          po = mlf_path(eft.obase,scan);
          etln = fi(:,2);
          fi(:,2) = NaN;
          try
            fi(eft.x,2) = eft.tune_scan(etln,Y);
            mlf_mkdir(eft.obase,scan);
            writebin( po, fi, hdr );
          catch except
            [~,name,ext] = fileparts(except.stack(1).file);
            fprintf(1,'tune_scan(%d) error: %s\n  %s%s line %d\n', ...
              scan, except.message, name, ext, except.stack(1).line);
          end
        end
      end
    end
    
    function Yout = Y(eft, index)
      Yout = eft.PTE(eft.si(index),[5:11 13:17]);
    end
    
    function dPhase = zero_crossings(eft, xss, sigf, dsign, dPhase)
      % eft.zero_crossing(sigf,dsign)
      % xss: sample numbers that correspond to rows of sigf and dsign
      %   that we want to consider for this analysis
      % sigf: [length(etln) x 2] The high-pass filtered raw etalon and
      %   etln_fit signals.
      % dsign: [length(xss) x 2] non-zero points mark zero crossings
      % dPhase: length(eft.x)
      %
      % We need to compare positive zero crossings to positive,
      % so this function will only consider one direction at a time.
      %
      % We will fill in the precise zero crossing differences into dPhase
      Across = find(dsign(:,1) > 0);
      Bcross = find(dsign(:,2) > 0);
      % zero crossing in the positive direction at integer indices
      % Across for column 1, Bcross for column 2
      if length(Across) ~= length(Bcross)
        N = min(length(Across),length(Bcross));
        d1 = abs(mean(Across(1:N)-Bcross(1:N)));
        d2 = abs(mean(Across((end-N+1):end)-Bcross((end-N+1):N)));
        if d1 < d2
          Across = Across(1:N);
          Bcross = Bcross(1:N);
          where = 'end';
        else
          Across = Across((end-N+1):end);
          Bcross = Bcross((end-N+1):end);
          where = 'beginning';
        end
        if eft.verbose
          warning('Scan %d: cross phase error near %s', scan, where);
        end
      end
      %Acrossf = Across;
      %Bcrossf = Bcross;
      for i = 1:length(Across)
        Ai = xss(Across(i));
        Acrossf = interp1(sigf(eft.x([Ai-1,Ai]),1),[Ai-1,Ai],0);
        Bi = xss(Bcross(i));
        Bcrossf = interp1(sigf(eft.x([Bi-1,Bi]),2),[Bi-1,Bi],0);
        dPhase(Ai) = Acrossf-Bcrossf;
        dPhase(Bi) = Acrossf-Bcrossf;
      end
    end
    
    function [ nu_rel2, nu_rel_out, etln1, etln2 ] = tune_scan(eft,etln,Y)
      % eft.tune_scan(etln,Y)
      % etln is the entire raw etalon signal. The zero offset
      % will be calculated and subtracted, and the fitting
      % region extracted.
      % nu_mdl2 is the same length as the raw scan
      % and consists of fine tuned relative wavenumber values
      % in the fit region (eft.x) and NaNs elsewhere.
      % nu_mdl, if requested, is the nu_rel value from etln_fit.
      % etln1, if reqested
      % etln2, if requested, is the tweaked full etalon function.
      etln = etln - mean(etln(eft.x0));
      sig = [etln etln];
      sig(eft.x,2) = etln_evalJ(Y,eft.xx)';
      efit = etln_evalJ(Y,eft.xx)'; %
      efitx = zeros(size(etln)); %
      efitx(eft.x) = efit; %
      Wn = 1/10;
      xr = (1:length(etln))';
      [b,a] = singlepole(Wn,'highpass');
      sigf = filter(b,a,sig);
      etlnfilt = sign(filter(b,a,etln)); %
      efitfilt = sign(filter(b,a,efitx)); %
      signf = sign(sigf);
      % prod = etlnfilt(eft.x).*efitfilt(eft.x);
      % Start with a range of values starting and ending where the
      %   raw signal and the fit agree, nominally assuring that the
      %   number of rising and falling edges agree between the two.
      % Identify all rising edges  of A
      % For each, locate the nearest rising edge of B, calculate phase
      % Do same for falling edges
      % Interpolate phase for all other values
      % Apply a low pass filter
      % xi_first = find(etlnfilt(eft.x) == efitfilt(eft.x),1,'first');
      % xi_last = find(etlnfilt(eft.x) == efitfilt(eft.x),1,'last');
      xi_first = find(signf(eft.x,1) == signf(eft.x,2),1,'first');
      xi_last = find(signf(eft.x,1) == signf(eft.x,2),1,'last');
      % xsubset is indices within eft.x
      xsubset = xi_first:xi_last;
      dsign = [ 0 0; diff(signf(eft.x(xsubset),:)) ];
      dPhase = nan * zeros(size(eft.x));
      dPhase = eft.zero_crossings(xsubset, sigf, dsign, dPhase);
      dPhase = eft.zero_crossings(xsubset, sigf, -dsign, dPhase);
      
      % Interpolate between values
      missing = isnan(dPhase);
      dPhase(missing) = interp1(eft.x(~missing),dPhase(~missing),eft.x(missing));
      missing = isnan(dPhase);
      if any(missing)
        dPhase(missing) = ...
          interp1(eft.x(~missing),dPhase(~missing),eft.x(missing), ...
            'nearest','extrap');
      end
      
      %
      % Create a gaussian distribution over N samples with unity sum
      N = eft.Nsmooth;
      R = 3;
      xg = linspace(-R,R,N);
      gxg = exp(-xg.^2);
      gxg = gxg/sum(gxg);
      dPhase2 = conv(dPhase,gxg,'same');
      % fringe_rate is fringes/Ksample
      fringe_rate = (Y(2) + 2*Y(3)*eft.xx - (Y(4)/Y(5))*exp(-eft.xx/Y(5)));
      fringe_num = etln_evalJ(Y(1:5),eft.xx);
      dfringe = (dPhase2/1000).*fringe_rate;
      
      tuning_rate = - eft.fsr * fringe_rate;
      nu_rel = - eft.fsr * fringe_num;
      dnu = (dPhase2/1000) .* tuning_rate;
      nu_rel2 = nu_rel - dnu;
      
      if nargout >= 2; nu_rel_out = nu_rel; end
      if nargout >= 3; etln1 = efit; end
      
      if nargout >= 4
        fringe_num2 = fringe_num - dfringe;
        P = Y(8)*eft.xx3 + Y(9)*eft.xx2 + Y(10)*eft.xx + Y(11);
        cse5 = pi*fringe_num2;
        cse6 = sin(cse5);
        cse7 = cse6.*cse6;
        D = 1 + Y(12)*cse7;
        etln2 = P./D;
      end
    end
    
    function view_tune(eft, ref)
      if nargin < 2; ref = []; end
      AppData.base = eft.obase;

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
      AppData.eft = eft;
      AppData.ref = ref;
      scan_viewer('Scans', eft.scans, 'Axes', AppData.Axes_1, 'Name', 'Fine Tune View', ...
          'Callback', @etln_fine_tune.tuneview_callback, 'AppData', AppData);
    end
    
    function callback(eft, handles, sv_axes)
      scan = handles.data.Scans(handles.data.Index);
      path = mlf_path( handles.data.AppData.base, scan, '.dat');
      fe = loadbin( path );
      data_ok = (~isempty(fe)) && size(fe,2) >= 2;
      if data_ok
        nsamples = size(fe,1);
        Y = eft.Y(handles.data.Index);
        nu_rel_0 = -etln_evalJ(Y(1:5),eft.xx)*eft.fsr;
        nu_rel_tune = fe(eft.x,2);
        dnu = nu_rel_tune - nu_rel_0;
        ref = handles.data.AppData.ref;
        if isempty(ref)
          plot(sv_axes(1),eft.x,dnu);
        else
          plot(sv_axes(1),eft.x,ref(:,handles.data.Index),eft.x,dnu);
        end
        grid(sv_axes(1),'on');
        title(sv_axes(1),sprintf('Scan %d: %s %s', scan, ...
          getrunaxis(handles.scan_viewer), ...
          getrun(0,handles.scan_viewer)));
        xlabel(sv_axes(1),'Sample');
      end
    end
    
    function [dnu, nu] = extract(eft)
      dnu = zeros(length(eft.x),length(eft.scans));
      if nargout > 1; nu = zeros(length(eft.x),length(eft.scans)); end
      for i=1:length(eft.scans)
        scan = eft.scans(i);
        Y = eft.Y(i);
        pi = mlf_path(eft.obase,scan);
        fi = loadbin(pi);
        if isempty(fi)
          warning('File not found: %d => %s', scan, eft.ibase);
        else
          Y = eft.Y(i);
          nu_rel_0 = -etln_evalJ(Y(1:5),eft.xx)*eft.fsr;
          nu_rel_tune = fi(eft.x,2);
          dnu(:,i) = nu_rel_tune - nu_rel_0;
          if nargout > 1; nu(:,i) = nu_rel_tune; end
        end
      end
    end
    
  end
  
  methods(Static)
    function tuneview_callback(handles, sv_axes)
      if nargin < 2
        sv_axes = handles.Axes;
      end
      handles.data.AppData.eft.callback(handles, sv_axes);
    end
  end
end