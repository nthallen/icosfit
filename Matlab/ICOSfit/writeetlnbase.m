function [ nu_out, Vout ] = writeetlnbase( name, p_coeffs, c_nu, ...
   c_vector, periods, scannum )
% [ nu_out, Vout ] = writeetlnbase( name, poly_coeffs, c_nu, c_vector, periods[,scannum] );
% Creates sbase.<name>.ptb specifying a baseline
% function containing a polynomial of sample number, an arbitrary
% number of explicit basis vectors as a function of wavenumber,
% and sinusoidal etalon signals of specified periods. The
% periods are specified in wavenumbers (cm-1).
%
% Note: The func_base_ptbnu format allows polynomials of wavenumber as
% well, but this function does not currently support that option.
%
% p_coeffs is either:
%   a: the scalar number of polynomial coefficients (degree+1). Output
%      will estimate the coefficients based on the specified scan data.
%   b: a vector of polynomical coefficents in polyfit order (highest degree
%      first.)
% The polynomial function's input is sample number/1000.
%
% c_nu and c_vector, if non-empty, specify explicit SVD-type vectors
% to include in the baseline. These vectors are resampled onto an evenly-
% spaced nu vector.
%
% periods is an n x 2 matrix where the first column holds wave periods
% and the second column holds wave amplitude. This is a change from earlier
% versions where all amplitudes were assumed to be 1. This change could be
% reverted if baseline_rescale works well.
%
% scannum is a representative scannum number to use for approximating the polynomial
% coefficients for Herriot Cell configurations. Could be extended for use with
% ICOS.
%
% I will use the fitline lines to determine a
% suitably large range for nu in the fit.
lo = fitline('load');
lines = lo.lines; % depends on fitline update
nuc = zeros(length(lines),1);
for i=1:length(lines)
  nuc(i) = lines(i).hitran(1,3);
end
margin = .4; % Long enough? Should probably be based on width
res = 5e-4;
nu_min = min(nuc)-margin;
nu_max = max(nuc)+margin+res;
nu = [nu_min:res:nu_max];
if ~isempty(c_nu)
  % complain if c_nu does not cover the range
  if nu_min < min(c_nu)-res/2 || nu_max > max(c_nu)+res/2
    error('c_nu does not cover the range required');
  end
  % resample only if c_nu is not uniformly spaced
  d_c_nu = diff(c_nu);
  ud_c_nu = unique(abs(d_c_nu));
  md_c_nu = abs(mean(d_c_nu));
  if any((diff(ud_c_nu)/md_c_nu) > 1e-8)
    fprintf(1,'Resampling c_vector due to non-uniform c_nu\n');
    c_vector=interp1(c_nu,c_vector,nu);
  else
    nu = c_nu;
  end
end
if nargin < 5
  periods = [];
end
if ~isempty(periods)
  if size(periods,2) ~= 2
    error('periods must be size nx2 with ampltitude in the second column');
  end
  if size(periods,1) == 1
    warning('periods of size 1x2 being interpreted as one period,ampltitude pair');
  end
end
if nargout > 0
  nu_out = nu';
  if nargout > 1
    Vout = zeros(length(nu),size(periods,1)*2);
  end
end

% Load N_Passes to determine whether this is ICOS or Herriot.
cellparams=load_cell_cfg;
N_Passes = cellparams.N_Passes;

% icos = loadscans([],30000); % random scan
% plot(icos); % to pick x range
% x = [500:2644]';
% V = fliplr(polyfit(x, icos(x)/1000, 3);
% % This isn't quite right either. For ICOS, we need to take
% % into account the ICOS gain (see skew_matrix). For a non-
% % integrating cavity, you don't get that gain.
k = 1;
if length(p_coeffs) > 1
  if size(p_coeffs,2)==1
    p_coeffs = p_coeffs';
  end
  V = fliplr(p_coeffs);
  p_coeffs = length(V);
elseif p_coeffs>0
  if nargin >= 6
    wv = waves_used(scannum);
    x = get_waveform_params(wv.Name,'SignalRegion', 1:wv.NetSamples);
    rawdata = loadscans([],scannum,x);
    x = x'/1000;
  else
    error('Cannot currently guess suitable raw source for Herriot');
  end
  if N_Passes == 0
    [~,k] = skew_matrix(scannum,length(x),1e-6);
  end
  P=polyfit(x,rawdata,p_coeffs-1);
  V = fliplr(P)/k;
else
  V =[];
end
fname2 = [ 'sbase.' name '.ptb' ];
fid = fopen( fname2, 'w' );
if fid > 0
  fwrite( fid, [0 1], 'integer*4'); % func_base_ptbnu format
  fwrite( fid, [ 1000 min(nu) res ], 'real*8' ); % polyscale, nu_min, dnu
  n_vectors = 2*size(periods,1)+size(c_vector,2);
  fwrite( fid, [ n_vectors length(nu) p_coeffs 0 ], 'integer*2' );
  % n_vectors n_pts poly_coeffs poly_of_nu
  fwrite( fid, ones(1,2*size(periods,1)+size(c_vector,2)), 'real*4' );
  % Initial parameter values
  fwrite( fid, V, 'real*4' );
  fwrite( fid, c_vector/k, 'real*4');
  for i=1:size(periods,1)
    theta = 2*pi*nu/periods(i,1);
    fwrite( fid, periods(i,2)*sin(theta)/(k*sqrt(2)), 'real*4');
    fwrite( fid, periods(i,2)*cos(theta)/(k*sqrt(2)), 'real*4');
    if nargout > 1
      Vout(:,2*i-1) = periods(i,2)*sin(theta)/sqrt(2);
      Vout(:,2*i) = periods(i,2)*cos(theta)/sqrt(2);
    end
  end
  fclose(fid);
  fprintf( 1, 'Output written to %s\n', fname2 );
else
  error('Cannot write to %s', fname2);
end
