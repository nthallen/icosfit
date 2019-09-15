function S = ICOS_setup(base, by_molecule)
% S = ICOS_setup([base [, by_molecule]])
% Assumes base variable is defined or defines it to be 'ICOSout'
% Loads ICOSout.sum into fitdata and defines
% C               ICOS_debug      chi2            n_input_params  
% Chi             Nfit            col             n_line_params   
% En              P               scannum         n_lines         
% Gair            S0 Scorr        delta dnu dFN   nu nu_P
% Ged             STdep           fitdata         nu_F0           
% Gedcalc         T               iso             nu_text         
% Gl              T0              lines           row             
% Glcalc          base            molwts          v               
% Gv              binary          n_base_params   
% Gvcalc          by_molecule     n_cols
%%%%
% C Number density of air molecules cm-3
% Nfit Number density of measured quantity molecules cm-3
% Chi Mixing ratio (normalized by HITRAN for isotopologues)
%%%%%
% v identifies the columns of fitdata corresponding to each line
if nargin < 2
    by_molecule = 0;
end
if nargin < 1 || isempty(base)
    base = 'ICOSout';
end

S.base = base;
S.ICOS_debug = 0;

if exist( [ base '/ICOSsum.dat' ], 'file' )
  S.fitdata = load( [ base '/ICOSsum.dat' ] );
elseif exist( [ base '/ICOSsum.out' ], 'file' )
  S.fitdata = load( [ base '/ICOSsum.out' ] );
  S.ICOS_debug = 1;
  S.ICOS_debug_scan = mlf_index(base);
  base = [ base '/../../..' ];
else
  error('Cannot locate ICOSsum.dat or ICOSsum.out in %s', base );
end
S.nu0 = 0;
if exist( [ base '/ICOSconfig.m' ], 'file' )
  addpath( base );
  eval( 'ICOSconfig;' );
  rmpath( base );
  req = { 'n_input_params', 'n_base_params', 'nu0', ...
      'CavLen', 'n_abs_params', 'n_abs_line_params', 'lines' };
  for i=1:length(req)
      if ~exist(req{i},'var')
          error('Variable "%s" not defined in ICOSconfig.m', req{i});
      end
  end
  if exist('ICOSfit_format_ver','var')
    S.ICOSfit_format_ver = ICOSfit_format_ver;
  else
    S.ICOSfit_format_ver = 1;
  end
  if S.ICOSfit_format_ver >= 2
      S.BackgroundRegion = BackgroundRegion;
      S.EtalonFSR = EtalonFSR;
      S.N_Passes = N_Passes;
      S.SignalRegion = S.fitdata(:,[5 6]);
  end
  if exist('Verbosity','var')
    S.Verbosity = Verbosity;
  else
    S.Verbosity = 0;
  end
  S.n_input_params = n_input_params;
  S.n_base_params = n_base_params;
  S.binary = binary;
  S.BaselineFile = BaselineFile;
  S.PTEfile = PTEfile;
  S.CavLen = CavLen;
  S.lines = eval('lines'); % to guard against function
  S.n_line_params = S.lines(:,9);
  if any(S.n_line_params ~= S.n_line_params(1))
    error('Cannot handle different line types!');
  end
  S.n_line_params = S.n_line_params(1);
  S.n_lines = size(S.lines,1);
  S.n_abs_params = n_abs_params;
  S.n_abs_line_params = n_abs_line_params;
  S.nu0 = nu0;
  if nu0 == 0
      if S.n_lines > 0
        S.nu0 = floor(S.lines(1,3));
      else
        S.nu0 = 0;
      end
  end
else
  linefile = [ base '/fitline.dat' ];
  if ~exist( linefile, 'file')
    linefile = 'fitline.dat';
    if ~exist(linefile, 'file')
      error 'Cannot locate fitline.dat'
    end
  end
  S.ICOSfit_format_ver = 1;
  S.lines = load(linefile);
  S.n_input_params = 8;
  S.n_base_params = 5;
  S.n_lines = size(S.lines,1);
  S.n_abs_params = 0;
  S.n_abs_line_params = 0;
end

S.n_fit_params = ( S.n_base_params + S.n_abs_params + ...
    S.n_lines * (S.n_line_params + S.n_abs_line_params) );
S.n_cols = S.n_input_params + 2 * S.n_fit_params;
if bitand(S.Verbosity, 32)
  S.n_cols = S.n_cols + S.n_fit_params; % dscl values
end
if S.n_cols > size(S.fitdata,2)
  error('ICOSconfig values specify %d cols: fitdata has %d', S.n_cols, size(S.fitdata,2));
end
S.n_extra_cols = size(S.fitdata,2) - S.n_cols;
S.n_cols = size(S.fitdata,2);

if S.ICOSfit_format_ver <= 1
  if S.n_input_params == 4
    S.scannum = S.fitdata(:,1);
    S.chi2 = S.fitdata(:,4);
  else
    % presumably this is for the n_input_params == 9 case
    S.scannum = S.fitdata(:,6);
    S.chi2 = S.fitdata(:,8);
  end
  if S.n_abs_params
    S.nu_F0 = S.fitdata(:,S.n_input_params+S.n_base_params+1);
    S.dFN = S.fitdata(:,9);
  else
    S.nu_F0 = S.fitdata(:,9);
    S.dFN = S.fitdata(:,10);
  end
else % S.ICOSfit_format_ver > 1 (2 for now)
  S.scannum = S.fitdata(:,1);
  S.chi2 = S.fitdata(:,4);
  S.nu_F0 = S.fitdata(:,S.n_input_params+S.n_base_params+1);
  if S.ICOSfit_format_ver >= 3 && bitand(S.Verbosity,2)
    S.info = S.fitdata(:,6+(1:9));
  end
end

S.v = ((1:S.n_lines)-1)*(S.n_line_params+S.n_abs_line_params) + ...
  S.n_input_params + S.n_base_params + S.n_abs_params + S.n_abs_line_params + 1;
S.row = ones(1,length(S.v));
S.col = ones( size(S.fitdata,1), 1 );
S.Nfit = S.fitdata(:,S.v+2);
S.P_vec = S.fitdata(:,2);
S.P = S.P_vec * S.row; % P in torr
S.T_vec = S.fitdata(:,3);
S.T = S.T_vec * S.row;
% C = 2.68675e19 * (P / 760.) ./ (T / 273.15); % [M]
S.C = 2.685e19 * (S.P / 760.) ./ (S.T / 273.15); % [M] Sayres' number
S.C(S.C==0) = NaN;
S.Chi = S.Nfit ./ S.C;

% Line definitions
S.S0 = S.lines(:,4)'; % line strength cm-1/(mol*cm-2)
S.En = S.lines(:,6)'; % Lower state energy in cm-1
S.Gair = S.lines(:,5)'; % air-broadend halfwidth at Tref, Pref
S.nu = S.lines(:,3)';
S.delta = S.lines(:,8)';
S.nu_P = S.col*S.nu + (S.col*S.delta).*S.P/760.; % pressure-corrected line positions
S.iso = (S.lines(:,1)*10 + S.lines(:,2))';
S.nu_text = {};
S.by_molecule = by_molecule;
if S.by_molecule > 0
  names = isovals(S.iso,'name');
  for i=1:S.n_lines
    S.nu_text{i} = sprintf('%d: %.4f %s',i, S.nu(i),names{i});
  end
else
  % nu_text = num2str( nu', '%.4f');
  for i=1:S.n_lines
    S.nu_text{i} = sprintf('%d: %.4f',i, S.nu(i));
  end
end
S.nu_text = char(S.nu_text);
S.STdep = S.lines(:,7)';
S.T0 = 296.;
S.Cfact = 1.438789;
S.Boltzfact = exp(S.Cfact*(S.col*S.En).*(S.T-S.T0)./(S.T0*S.T));
S.StimEmis = (1-exp(-S.Cfact*(S.col*S.nu)./S.T))./(1-exp(-S.Cfact*(S.col*S.nu)/S.T0));
% StimEmis = 1;
S.Qfact = load_QT(S.T(:,1),S.iso);
% S.Qfact = (S.T0./S.T).^1.5; % Need to do this line by line
S.Scorr = (S.col*S.S0) .* S.Qfact .* S.Boltzfact .* S.StimEmis; % correct line strength
if isempty(S.iso)
  S.molwts = zeros(size(S.iso));
else
  S.molwts = isovals(S.iso,'weight')';
end
S.Ged = S.fitdata(:,S.v+1);
S.Gl = S.fitdata(:,S.v+3);
if S.ICOSfit_format_ver <= 2
  S.dnu = S.fitdata(:,S.v);
else % Format V3 includes nu_F0 with each line even though it is common
  S.dnu = S.fitdata(:,S.v)+S.fitdata(:,S.v+4);
end
% Gedcalc = 3.581e-7 * (col*nu) .* sqrt(T./(col*molwts*log(2)));
S.Gedcalc = 4.30213e-7 * (S.col*S.nu) .* sqrt(S.T./(S.col*S.molwts));
S.Glcalc = ((S.T0./S.T).^(S.col*S.STdep)) .* (S.col*S.Gair) .* (S.P/760.);
S.Gv = 0.5346*S.Gl + sqrt( 0.2166 * S.Gl.*S.Gl + .69315*S.Ged.*S.Ged);
S.Gvcalc = 0.5346*S.Glcalc + sqrt( 0.2166 * S.Glcalc.*S.Glcalc + .69315*S.Gedcalc.*S.Gedcalc);
