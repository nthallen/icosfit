function nu = get_nu( varargin )
% nu_rel = get_nu(scannums, x [, PTEfile]);
%  Returns the relative wavenumber determined from the
%  etalon fit. Absolute wavenumber for a given sample
%  is equal to nu_rel + nu_F0 + nu0
%
% nu = get_nu( region, suffix, x [, PTEfile[, scannums]] )
%  Returns the absolute wavenumber for the specified
%  fit region and suffix.
PTEfile = [];
region = '';
if ischar(varargin{1})
  region = varargin{1};
  suffix = varargin{2};
  x = varargin{3};
  base = [ 'ICOSout.' region ];
  if ~isempty(suffix)
    base = [ base '.' suffix ];
  end
  if exist( base, 'dir' )
    S = ICOS_setup(base); % To define nu0, nu_F0
    if ~isfield(S,'nu0') || ~isfield(S,'nu_F0')
      error('ICOS_setup did not define nu0 or nu_F0');
    end
    if any(diff(S.scannum)==0) || (any(diff(S.scannum)<0) && any(diff(S.scannum)>0))
      error('ScanNum is non-monotonic in %s', base );
    end
  else
    error('Cannot locate directory %s', base );
  end
  PTEfile = S.PTEfile;
  if length(varargin) >= 4 && ~isempty(varargin{4})
    PTEfile = varargin{4};
  end
  if length(varargin) >= 5
    scannums = varargin{5};
  else
    scannums = S.scannum; % fitline('region', region);
  end
else
  scannums = varargin{1};
  x = varargin{2};
  if length(varargin) >= 3
    PTEfile = varargin{3};
  end
end
if isempty(PTEfile)
  PTEfile = 'PTE.txt';
end
PTE = load(PTEfile);
nu = zeros(length(x),length(scannums));
cellparams=load_cell_cfg;
FSR = cellparams.fsr; % 0.0198;
for i=1:length(scannums)
  j = find(PTE(:,1)==scannums(i));
  if length(j) > 1
    error('PTE file has duplicate entries for scannums %d', scannums(i));
  elseif isempty(j)
    error('Cannot locate PTE row for scannums %d', scannums(i));
  end
  Y = PTE(j,5:11);
  xx = (x-PTE(j,4)+1)*1e-3;
  nu(:,i) = -FSR*etln_evalJ(Y,xx);
%   if size(PTE,2) == 12
%     nu(:,i) = nu(:,i) + PTE(j,12);
%   end
end
if ~isempty(region)
  fdi = interp1( S.scannum, 1:length(S.scannum), scannums );
  nu = nu + S.nu0 + ones(length(x),1)*S.nu_F0(fdi)';
end
