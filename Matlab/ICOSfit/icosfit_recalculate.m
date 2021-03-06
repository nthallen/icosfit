function outval = icosfit_recalculate(arg1, varargin)
% RC = icosfit_recalculate(base, varargin)
%   Setup for subsequent calculations. Options include:
%    'scannum', scans : limit subsequent operations to specified scans
% recalc = icosfit_recalculate(RC, Index)
%   Produces an output matrix similar to the verbose fit output
% matrix.
%
% RC.S is the ICOS_setup structure, but I redefine RC.S.nu_P by
% subtracting S.nu0.
if ischar(arg1)
    S = ICOS_setup(arg1);
    if S.ICOSfit_format_ver < 2
        error('ICOSfit recalculation requires ICOSfit_format_ver >= 2');
    end
    S.nu_P = (S.col*S.nu - S.nu0) + (S.col*S.delta).*S.P/760.;
    RC.ICOSfit_cfg = load_ICOSfit_cfg;
    RC.ScanBase = find_scans_dir([]);
    RC.Scans = S.scannum;
    RC.IScans = 1:length(RC.Scans);
    % now RC.Scans == S.scannum(RC.IScans)
    % When scans are specified explicitly, this allows us to deal with
    % fits that might run in reverse or even have multiple overlapping
    % regions.
    RC.S = S;
    
    % Load PTE stuff
    if ~exist(RC.S.PTEfile,'file')
        error('Unable to locate PTEfile %s', RC.S.PTEfile);
    end
    RC.PTE = load(RC.S.PTEfile);
    i = 1;
    while i <= length(varargin)
      if ~ischar(varargin{i})
        error('Expected option string at argument %d', i+1);
      elseif strcmpi(varargin{i}, 'scannum')
        i = i + 1;
        if i > length(varargin)
          error('Scans option requires value');
        end
        RC.Scans = varargin{i};
        if size(RC.Scans,1) == 1
          RC.Scans = RC.Scans';
        end
        % should check that these scans are all in S.scannum
        [ss,I] = unique(RC.S.scannum);
        Is = interp1(ss,I,RC.Scans,'nearest','extrap');
        v = RC.S.scannum(Is) == RC.Scans;
        if ~any(v)
          error('Specified scan range does not match fit data range');
        elseif ~all(v)
          warning('ICOSfit:recalc:ScanNumRange', 'Some scans in specified range are missing');
          RC.Scans = RC.Scans(v);
          RC.IScans = Is(v);
        else
          RC.IScans = Is;
        end
      else
        error('Unrecognized option: "%s"', varargin{i});
      end
      i = i + 1;
    end

    % Now map RC.Scans onto rows of PTE
    [ps,I] = unique(RC.PTE(:,1));
    Ip = interp1(ps,I,RC.Scans,'nearest','extrap');
    v = RC.PTE(Ip,1) == RC.Scans;
    if ~all(v)
        error('Specified scan range does not match PTE file range');
    else
        RC.PTEi = Ip;
    end
    
    wvs = waves_used(RC.Scans);
    if length(wvs) > 1
        error('More than one waveform for specified scans');
    end
    if any(RC.S.BackgroundRegion ~= [5 wvs.TzSamples])
        warning('ICOSfit:recalc:BackgroundRegion', ...
            'BackgroundRegion differs from default');
    end
    RC.BGi = ...
        RC.S.BackgroundRegion(1):RC.S.BackgroundRegion(2);
    
    if S.N_Passes == 0 % ICOS
      % CavityLength = S.CavLen;
      % MirrorLoss = cellparams.MirrorLoss*1e-6;
      c = lightspeed; % cm/sec
      R = 1-S.MirrorLoss;
      RC.N = c/(2*S.CavLen*S.SampleRate);
      RC.M = ceil(log(S.SkewTolerance)/(2*RC.N*log(R)));
      RC.R2 = R^2;
      RC.R2N = RC.R2.^RC.N;
      RC.P_scale = (1-RC.R2N)/(1-RC.R2);
      % Create a skew matrix for baseline power
      npts = max(S.SignalRegion(:,2)) - min(S.SignalRegion(:,1)) + RC.M;
      n = 0:RC.M-1;
      RC.PA = spdiags(ones(npts,1)*(RC.R2N.^n), -n, npts, npts);
      % This provides a correction for the first M-1 points
      % Not really necessary
      %wt = sum(RC.PA,2);
      %RC.PA = RC.P_scale*RC.PA.*((wt(end)./wt)*ones(1,npts));
      RC.PA = RC.P_scale*RC.PA;
    end
    
    % Load baseline stuff
    RC.Baseline = loadetlnbase(RC);
      
    outval = RC;
else
    RC = arg1;
    Index = varargin{1};
    assert(Index <= length(RC.Scans));
    ScanNum = RC.Scans(Index);
    IScan = RC.IScans(Index);
    PScan = RC.PTEi(Index);
    S = RC.S;
    assert(ScanNum == S.scannum(IScan));
    ifile = mlf_path(RC.ScanBase,ScanNum,'.dat');
    raw = loadbin(ifile); % Includes zero
    raw = raw - mean(raw(RC.BGi,1));
    if S.N_Passes == 0
      SR = (S.fitdata(IScan,5)-RC.M+1:S.fitdata(IScan,6))';
    else
      SR = (S.fitdata(IScan,5):S.fitdata(IScan,6))';
    end
    BP = S.fitdata(IScan,RC.Baseline.PVi)';
    nu_rel = -S.EtalonFSR*etln_evalJ(RC.PTE(PScan,5:11), ...
        (SR-RC.PTE(PScan,4)+1)/RC.Baseline.Pscale);
    %baseline = RC.Baseline.XM(SR - RC.Baseline.minx+1,:) * BP;
    baseline = evaletlnbase(RC, SR, BP, nu_rel+S.nu_F0(IScan)+S.nu0);
    Abs = zeros(size(SR));
    XK = zeros(length(SR),2*S.n_lines);
    for i = 1:S.n_lines
        X = (nu_rel + S.dnu(IScan,i) - S.nu_P(IScan,i)) / S.Ged(IScan,i);
        Y = S.Gl(IScan,i)/S.Ged(IScan,i);
        [K,~,~] = humdev(X,Y);
        XK(:,2*i-1) = X;
        XK(:,2*i) = K;
        Abs = Abs + S.Nfit(IScan,i)*S.Scorr(IScan,i)*S.CavLen*K / ...
            (S.Ged(IScan,i) * sqrt(pi));
    end
    if S.N_Passes > 0
      fit = baseline .* exp(-S.N_Passes * Abs);
    else
      npts = length(SR);
      beta = exp(-Abs);
      gamma = RC.R2 * beta.^2;
      eps = gamma.^RC.N;
      delta = (eps-1)./(gamma-1);
      g = baseline.*beta.*delta;
      n = 0:RC.M-1;
      A = spdiags((eps*ones(1,RC.M)).^(ones(npts,1)*n), -n, npts, npts);
      fit = A*g;
      baseline = RC.PA(1:npts,1:npts) * baseline;
    end
    outval = [ SR nu_rel raw(SR,1) fit baseline Abs XK ];
    if S.N_Passes == 0
      outval = outval(RC.M:end,:);
    end
end

function Baseline = loadetlnbase(RC)
% Assign Baseline params to structure
[ nu, vectors, p_coeffs, Ptype, PV, Pscale ] = ...
    readetlnbase( RC.S.BaselineFile );
Baseline = struct('nu', nu, 'vectors', vectors, ...
    'p_coeffs', p_coeffs, 'Ptype', Ptype, 'PV', PV, ...
    'Pscale', Pscale);
assert(Ptype == 0);
% assert(isempty(vectors));
n_vectors = size(vectors,2);
if n_vectors
  n_base_params = n_vectors + p_coeffs + 1; % for nu_f0
else
  n_base_params = p_coeffs;
end
assert(RC.S.n_base_params == n_base_params);
assert(length(PV) == p_coeffs);
Baseline.minx = min(RC.S.fitdata(:,5));
if RC.S.N_Passes == 0
  Baseline.minx = Baseline.minx - RC.M + 1;
end
maxx = max(RC.S.fitdata(:,6));
Baseline.XM = ((Baseline.minx:maxx)'*ones(1,p_coeffs)/Pscale) .^ ...
    (ones(maxx-Baseline.minx+1,1)*(0:p_coeffs-1));
Baseline.PVi = RC.S.n_input_params+(1:RC.S.n_base_params);

function baseline = evaletlnbase(RC, SR, BP, nu)
baseline = RC.Baseline.XM(SR - RC.Baseline.minx+1,:) * ...
    BP(end-RC.Baseline.p_coeffs+1:end);
for i=1:size(RC.Baseline.vectors,2)
    baseline = baseline + ...
        interp1(RC.Baseline.nu,RC.Baseline.vectors(:,i),nu) * BP(i+1);
end
