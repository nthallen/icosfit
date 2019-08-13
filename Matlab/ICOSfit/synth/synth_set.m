function synth_set(OutputDir, Wavename, ppm, nu_0, noise, Cell_P, Cell_T, PwrIn, TX )
% synth_set(OutputDir, Wavename, ppm, nu_0, noise, CellP, Cell_T, ...
%   PwrIn, TX);
% ppm is an N x M matrix determining how many files are written.
%  It must have as many columns as there are lines.
% nu_0 can be constant or as long as ppm. It is added to the nu_rel
%  determined from the PTE.txt file in this directory. A value near
%  1485.4 works well with this data set (but it would be nice to
%  have this determined more automatically).
% TX is a time multiplier to synthesis TX points per input waveform sample
% so the only useful input to PT and PTE are CPCI range 1 to ?
% (Throw in a CPCI==0 line in PT.mat too)
% [synth1 included beginnings of hooks for ambient water
%   and A/C coupling]
%
% Things I want to vary within a run:
%   Laser position relative to baseline water
%   Concentrations
%   noise
%
% Questions 12/27/05
%   Does family of linear regressions have substantially the
%   same slope curve independent of the baseline? I expect it
%   to be different, but how different?
%   To answer: generate data sets for markedly different
%   baselines and compare. Also generate data sets for
%   marginally different baselines
if nargin < 8
  error('synth_set: Not enough arguments.');
end
if nargin < 9
  TX = 1;
end

PTEfile = [ 'PTE_' Wavename '.txt' ];
NeedFiles = { 'waves.m', 'fitline.dat', PTEfile, 'CavityLength.mat' };
for i=1:length(NeedFiles)
  if ~exist( NeedFiles{i}, 'file' )
    error( [ NeedFiles{i} ' not found' ] );
  end
end

% Turn off A/C coupling
AC = 0;
sizes = [ size(ppm,1) length(nu_0) length(noise) length(Cell_P) ];
nscans = max( sizes );
if any(sizes ~= nscans & sizes ~= 1)
  error('All inputs must be constant or the same length');
end
if nscans > 1
  col = ones(nscans+1,1);
  if size(ppm,1) == 1; ppm = col*ppm; end
  % if size(nu_0,2)>1; nu_0 = nu_0'; end
  % if size(nu_0,1)==1; nu_0 = col*nu_0; end
  if size(noise,2)>1; noise = noise'; end
  if size(noise,1)==1; noise = col*noise; end
  if size(Cell_P,2)>1; Cell_P = Cell_P'; end
  if size(Cell_P,1)==1; Cell_P = col*Cell_P; end
  if size(Cell_T,2)>1; Cell_T = Cell_T'; end
  if size(Cell_T,1)==1; Cell_T = col*Cell_T; end
end

% load MirrorLoss;
load CavityLength;
WaveSpecs = load_waves;
Waveidx = find(strcmp({WaveSpecs.Name}, Wavename)) - 1;
wv = WaveSpecs(Waveidx+1);

% establish output directory name
if ~exist(OutputDir,'dir')
  mkdir(OutputDir);
end
if ~exist([ OutputDir '/CPCI14' ], 'dir' )
  mkdir( OutputDir, 'CPCI14' );
end
cpfiles = { 'waves.m', 'fitline.dat', 'N_Passes.mat', 'MirrorLoss.mat', ...
  'CavityLength.mat', [ wv.Name '_etln.mat' ] };
for i=1:length(cpfiles)
  if exist(cpfiles{i}, 'file' )
    copyfile(cpfiles{i}, [ OutputDir '/' cpfiles{i} ] );
  end
end
lines = load('fitline.dat');

% Write out PT.mat and PTE.txt
cpci = (0:nscans)';

% It looks like PT could be largely constant
% PT:
% Time (increment by seconds?)
% CellP (constant 40?)
% T in Kelvin (27+273.15)
% CPCI14 (1 to N)
% Cal_F (zero)
% InltF (zero)
% QCLI_Wave (determined from input)
Tcpci = cpci * wv.NCoadd/wv.FTrigger;
TPT = (0:ceil(max(Tcpci)))';
CPCI14 = floor(interp1( Tcpci,cpci,TPT));
CPCI14(isnan(CPCI14)) = max(cpci);
Tavg = interp1(Tcpci, Cell_T, TPT, 'linear', 'extrap' );
CellP = interp1( Tcpci, Cell_P, TPT, 'linear','extrap' );
%Cal_F = 0*Tavg;
%InltF = Cal_F;
QCLI_Wave = Waveidx * ones(size(TPT));
PT_vars = {'TPT', 'CellP', 'Tavg', 'CPCI14', 'QCLI_Wave'};
save([ OutputDir '/PT.mat' ], PT_vars{:} );
clear( PT_vars{:} );


% PTE:
% CPCI14
% CellP in Torr (i.e. 40)
% CellT in Kelvin (i.e. 27+273.15)
% Etln(0..7)
PTE_X = load(PTEfile);
PTE_X = PTE_X(1,4:end);
ofd = fopen( [ OutputDir '/PTE.txt' ], 'w' );
for i=2:length(cpci)
  fprintf( ofd, '%d %.2f %.1f %d %.7g %.7g %.7g %.7g %.7g %.7g %.7g\n', ...
    cpci(i), Cell_P(i-1), Cell_T(i-1), PTE_X );
end
fclose(ofd);

x = (TX:TX*wv.NetSamples)'/TX;
on = ((wv.TzSamples+1)*TX:(wv.NetSamples-wv.TzSamples)*TX)'; % Not perfect
% establish tuning rate
%  Try to apply the tweak_base2b power curve params here
%  (or just punt! We use PTE.txt anyway, so this is just cosmetic, right?)
FSR = 0.019805; % cm-1
nu_rel = -FSR * etln_evalJ(PTE_X(2:end), (x-PTE_X(1)+1)/1000);
etln = zeros(size(x));
etln(on) = etln_evalJ([PTE_X(2:end) -0.3169    0.7606    3.5943    9.3701    1.6958], ...
  (on/TX-PTE_X(1)+1)/1000);

if nargin < 8
  % Establish power curve using tweak_base2b parameters
  % This section of code is currently disabled by an nargin
  % check at the top.

  % Model power throughout the 'on' region, with zero elsewhere
  % Feed the 'mdl' region (which brackets the on region) to
  % synthetic. Leave the rest zero prior to noise and
  % A/C coupling.

  Pin = zeros(size(x));
  xx = x(on)-160; % arbitrary zero from tweak_base2b.
  Pin(on) = .013372 + 7.918e-6*xx - 9.091e-10*xx.*xx ...
    + 1.31e-3 * exp(-xx/227.92) + 1.039e-3 * exp(-xx/48.07);
  Pin(on) = Pin(on)*1.2649e+6;

  % Add a couple perturbations to the baseline
  Pin(on) = Pin(on) + 13*sin(2*pi*(nu_rel(on)-.06)/.15) + 50*sin(2*pi*nu_rel(on));


  [b,a] = butter(2,.5*2/(wv.RawRate/wv.NAverage),'high');

  % Write out baseline file
  % If we're doing A/C coupling, we need to pass the baseline through
  % the A/C coupling for writing
  if AC
    Pf = filter(b, a, Pin, mean(Pin)*[-1 1]);
    Pf = Pf - mean(Pf(1:wv.TzSamples));
  else
    Pf = Pin;
  end
elseif TX == 1
  Pf = PwrIn;
else
  Pf = interp1((1:wv.NetSamples)',PwrIn,x);
end
[U,S,V] = svds(Pf,1);
writebase([ OutputDir '/sbase.all.dat' ],U,S,V);

synthetic(struct('reset',1,'CavityLength', CavityLength, ...
  'SampleRate', TX*wv.RawRate/wv.NAverage, 'PowerCurve', Pf, 'Lines', lines));

if length(nu_0) == 1
  nu = nu_rel + nu_0;
  synthetic(struct('nu', nu));
end

base = [ OutputDir '/CPCI14' ];
% figure;
for cpci = 1:nscans
  if length(nu_0) > 1
    nu = nu_rel + nu_0(cpci);
    synthetic(struct('nu', nu));
  end
  output = synthetic( Cell_P(cpci), Cell_T(cpci), ppm(cpci,:) );
  if AC
    output = filter(b, a, output, mean(output)*[-1 1]) + 1.1*mean(output);
  end
  output = output + noise(cpci)*randn(size(output));
  path = mlf_path('', cpci);
  if ~exist( [ base path(1:3) ], 'dir' )
    mkdir( base, path(2:3) );
  end
  if ~exist( [ base path(1:6) ], 'dir' )
    mkdir( [ base path(1:3) ], path(5:6) );
  end
  writebin( [ base path ], [ output etln ] );
%   clf;
%   nsubplot(2,1,1);
%   plot( x, output );
%   title(sprintf('cpci %d %.0f Torr', cpci, Cell_P(cpci)));
%   nsubplot(2,1,2);
%   plot( x, etln );
%   drawnow;
end
