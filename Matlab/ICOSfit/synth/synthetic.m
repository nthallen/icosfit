function output = synthetic( P, T, ppm, extra_cavity );
% output = synthetic( P, T, ppm[, extra_cavity]  );
%  nu wavenumber vector
%  P scalar pressure in Torr
%  T scalar temperature in Celcius
%  ppm column vector of mixing ratios
%  extra_cavity if set to 1 eliminates the skew calculation
%
% opts = synthetic( opts );
%  opts struct contains any additional parameters, including
%   CavityLength
%   MirrorLoss
%   PowerCurve (vector)
%   nu (vector)
%   SampleRate
%   Lines
%
% opts values are persistent and don't need to be passed to
% subsequent invocations.
%
% Persistent opt fields:
%   iso: vector of isotopomer numbers
%   molwts = isovals(popt.iso,'weight');
%   line_nu = lines(:,3);
%   S0 = lines(:,4)'; % line strength cm-1/(mol*cm-2)
%   En = lines(:,6)'; % Lower state energy in cm-1
%   Gair = lines(:,5)'; % air-broadend halfwidth at Tref, Pref
%   STdep = lines(:,7)';
%   delta = lines(:,8)';
persistent popt;
optfields = { 'nu', 'CavityLength', 'MirrorLoss', 'PowerCurve', 'SampleRate', 'Lines' };
if nargin == 1 && isstruct(P)
  opts = P;
  if isfield(opts, 'reset')
    popt = [];
  end
  for i = 1:length(optfields)
    if isfield(opts,optfields{i})
      popt.(optfields{i}) = opts.(optfields{i});
    end
  end
  if isfield(popt,'iso')
    popt = rmfield(popt,'iso');
  end
  output = popt;
  return;
end

if ~isfield(popt,'CavityLength')
  popt.CavityLength = load_cavity_length;
end
popt.N_Passes = 0;
dirs = { '.', '..' };
for i = 1:length(dirs)
  path = [ dirs{i} '/N_Passes.mat' ];
  if exist(path,'file')
    load(path);
    popt.N_Passes = N_Passes;
    popt.MirrorLoss = 0;
    clear N_Passes
    break;
  end
end
if popt.N_Passes == 0 && ~isfield(popt,'MirrorLoss')
  load MirrorLoss.mat;
  popt.MirrorLoss = MirrorLoss;
end
missing = {};
for i = 1:length(optfields)
  if ~isfield(popt,optfields{i})
    missing = { missing{:}, [ ' ' optfields{i} ] };
  end
end
if length(missing)
  error(sprintf('Missing option: %s\n', missing{:}));
end

R = 1-popt.MirrorLoss;
if ~isfield(popt,'iso')
  lines = popt.Lines;
  popt.iso = (lines(:,1)*10 + lines(:,2))';
  popt.molwts = isovals(popt.iso,'weight')';
  popt.line_nu = lines(:,3)';
  popt.S0 = lines(:,4)'; % line strength cm-1/(mol*cm-2)
  popt.En = lines(:,6)'; % Lower state energy in cm-1
  popt.Gair = lines(:,5)'; % air-broadend halfwidth at Tref, Pref
  popt.STdep = lines(:,7)';
  popt.delta = lines(:,8)';
  c = 2.99792458e10; % cm/sec
  tol = 10e-6;
  if popt.N_Passes == 0
    popt.Npasses = c/(2*popt.CavityLength*popt.SampleRate);
    popt.Msamples = ceil(log(tol)/(2*popt.Npasses*log(R)));
  end
end
if nargin == 0
  output = popt;
  return;
end

npts = length(popt.nu);
nlines = size(popt.Lines,1);
if length(ppm) == 1
  ppm = ppm * ones(nlines,1);
end
if length(ppm) ~= nlines
  error('ppm does not match number of lines');
end
if size(ppm,1) > 1
  ppm = ppm';
end
C = 2.685e19 * (P / 760.) ./ (T / 273.15); % [M] Sayres' number
N = ppm * 1e-6 * C;

T0 = 296.;
Cfact = 1.438789;
Boltzfact = exp(Cfact*(popt.En).*(T-T0)./(T0*T));
StimEmis = (1-exp(-Cfact*popt.line_nu/T))./(1-exp(-Cfact*popt.line_nu/T0));
Qfact = (T0./T).^1.5;

Scorr = popt.S0 .* Qfact .* Boltzfact .* StimEmis; % correct line strength
Glcalc = ((T0./T).^(popt.STdep)) .* (popt.Gair) .* (P/760.);
Gedcalc = 4.30213e-7 * popt.line_nu .* sqrt(T./(popt.molwts));
Gv = Glcalc ./ Gedcalc;
line_nu_P = popt.line_nu + popt.delta.*P/760.; % pressure-corrected line positions

absorb = zeros(size(popt.nu));
for i=1:length(Scorr)
  np = 1;
  if popt.N_Passes > 0; np = popt.N_Passes; end
  absorb = absorb + N(i) * Scorr(i) * popt.CavityLength * np * ...
    humlik((popt.nu-line_nu_P(i))/Gedcalc(i), Gv(i)) / (Gedcalc(i)*sqrt(pi));
end

Beta = exp(-absorb);
if nargin > 3
  if extra_cavity
    output = popt.PowerCurve.*Beta;
    return;
  end
end
if popt.N_Passes == 0
  Gamma = (R^2)*(Beta.^2);
  GN = Gamma.^popt.Npasses;
  Eta = popt.PowerCurve.*Beta.*(1-GN)./(1-Gamma);
  B = zeros(npts,popt.Msamples);
  for j=[1:popt.Msamples]
    B(:,j) = GN.^(j-1);
  end
  A = spdiags(B, [0:-1:-popt.Msamples+1], npts, npts);

  % As is a correction factor for the first M samples
  %As = (1./sum(A')')/(1 - R^(2*popt.Npasses));
  %As(popt.Msamples:end) = 1;

  % The (2/popt.MirrorLoss - 1) factor here is just a scale
  % factor applied to the input power so the magnitude matches
  % the output power. In fact, the input power is greater than
  % the output power by this factor, but we never measure the
  % input power directly. It is easier to characterize the
  % input power in terms of the output power in the absence of
  % absorbers.
  output = popt.MirrorLoss^2*(2/popt.MirrorLoss - 1).*(A*Eta);
else
  output = popt.PowerCurve.*Beta;
end