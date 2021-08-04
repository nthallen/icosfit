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
  end
  methods
    function eft = etln_fine_tune(PTEfile, scans)
      eft.verbose = false;
      eft.PTE = load(PTEfile);
      eft.ibase = find_scans_dir;
      eft.obase = [ eft.ibase 'f' ];
      if nargin < 2
        scans = eft.PTE(:,1);
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
    end
    
    function tune_scans(eft)
      for i=1:length(eft.scans)
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
          fi(eft.x,2) = eft.tune_scan(etln,Y,scan);
          mlf_mkdir(eft.obase,scan);
          writebin( po, fi, hdr );
        end
      end
    end
    
    function Yout = Y(eft, index)
      Yout = eft.PTE(eft.si(index),[5:11 13:17]);
    end
    
    function [ nu_rel2, nu_rel_out, etln1, etln2 ] = tune_scan(eft,etln,Y,scan)
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
      efit = etln_evalJ(Y,eft.xx)';
      efitx = zeros(size(etln));
      efitx(eft.x) = efit;
      Wn = 1/10;
      xr = (1:length(etln))';
      [b,a] = singlepole(Wn,'highpass');
      etlnfilt = sign(filter(b,a,etln));
      efitfilt = sign(filter(b,a,efitx));
      % prod = etlnfilt(eft.x).*efitfilt(eft.x);
      % Start with a range of values starting and ending where the
      %   raw signal and the fit agree, nominally assuring that the
      %   number of rising and falling edges agree between the two.
      % Identify all rising edges  of A
      % For each, locate the nearest rising edge of B, calculate phase
      % Do same for falling edges
      % Interpolate phase for all other values
      % Apply a low pass filter
      dPhase = nan * zeros(size(eft.x));
      xi_first = find(etlnfilt(eft.x) == efitfilt(eft.x),1,'first');
      xi_last = find(etlnfilt(eft.x) == efitfilt(eft.x),1,'last');
      xsubset=eft.x(xi_first:xi_last);
      dA = [ 0; diff(etlnfilt(xsubset))];
      dB = [ 0; diff(efitfilt(xsubset))];
      Arising = find(dA > 0);
      Brising = find(dB > 0);
      if length(Arising) ~= length(Brising)
%         figure;
%         plot(eft.x(Arising(1:N)), Arising(1:N)-Brising(1:N),'.');
%         hold  on
%         plot(eft.x(Arising((end-N+1):end)), ...
%           Arising((end-N+1):end)-Brising((end-N+1):end),'o');
        N = min(length(Arising),length(Brising));
        d1 = abs(mean(Arising(1:N)-Brising(1:N)));
        d2 = abs(mean(Arising((end-N+1):end)-Brising((end-N+1):N)));
        if d1 < d2
          Arising = Arising(1:N);
          Brising = Brising(1:N);
          where = 'end';
        else
          Arising = Arising((end-N+1):end);
          Brising = Brising((end-N+1):end);
          where = 'beginning';
        end
        if eft.verbose
          warning('Scan %d: Rising phase error near %s', scan, where);
        end
      end
%       Br2 = interp1(Brising,Brising,Arising,'nearest','extrap');
%       if ~all(Br2 == Brising)
%         error('Sanity check failed');
%       end
      dPhase(Arising) = Arising-Brising;
      dPhase(Brising) = Arising-Brising;
      
      Afalling = find(dA < 0);
      Bfalling = find(dB < 0);
      if length(Afalling) ~= length(Bfalling)
        N = min(length(Afalling),length(Bfalling));
        d1 = abs(mean(Afalling(1:N)-Bfalling(1:N)));
        d2 = abs(mean(Afalling((end-N+1):end)-Bfalling((end-N+1):N)));
        if d1 < d2
          Afalling = Afalling(1:N);
          Bfalling = Bfalling(1:N);
          where = 'end';
        else
          Afalling = Afalling((end-N+1):end);
          Bfalling = Bfalling((end-N+1):end);
          where = 'beginning';
        end
        if eft.verbose
          warning('Scan %d: Falling phase error near %s', scan, where);
        end
      end
%       Bf2 = interp1(Bfalling,Bfalling,Afalling,'nearest','extrap');
%       if ~all(Bf2 == Bfalling)
%         error('Sanity check failed');
%       end
      dPhase(Afalling) = Afalling-Bfalling;
      dPhase(Bfalling) = Afalling-Bfalling;
      
      % Interpolate between values
      missing = isnan(dPhase);
      dPhase(missing) = interp1(eft.x(~missing),dPhase(~missing),eft.x(missing));
      missing = isnan(dPhase);
      dPhase(missing) = interp1(eft.x(~missing),dPhase(~missing),eft.x(missing),'nearest','extrap');
      %
      % Create a gaussian distribution over N samples with unity sum
      N = 40;
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
  end
end