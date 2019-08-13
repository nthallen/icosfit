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
% p_coeffs is the number of polynomial coefficients (degree+1). Output
% specifies polynomial function of sample number/1000.
%
% c_nu and c_vector, if non-empty, specify explicit SVD-type vectors
% to include in the baseline. These vectors are resampled onto an evenly-
% spaced nu vector.
%
% periods is a vector of wave periods to include in the baseline. For each
% period, two vectors (cos & sin) will be included in the baseline.
%
% scannum is a representative scannum number to use for approximating the polynomial
% coefficients for Herriot Cell configurations. Could be extended for use with
% ICOS.
%
% I will use the fitline lines to determine a
% suitably large range for nu in the fit.
lo = fitline('load');
lines = lo.lines; % depends on fitline update
nuc = zeros(length(lines));
for i=1:length(lines)
  nuc(i) = lines(i).hitran(1,3);
end
margin = .4; % Long enough? Should probably be based on width
res = 5e-4;
nu_min = min(nuc)-margin;
nu_max = max(nuc)+margin+res;
nu = [nu_min:res:nu_max];
if ~isempty(c_nu)
    c_vector=interp1(c_nu,c_vector,nu);
end
if nargout > 0
  nu_out = nu';
  if nargout > 1
    Vout = zeros(length(nu),length(periods)*2);
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
if p_coeffs>0
  x = (300:2644)'/1000;
  if N_Passes ~= 0
    if nargin >= 6
      wv = waves_used(scannum);
      x = get_waveform_params(wv.Name,'SignalRegion', 1:wv.NetSamples);
      rawdata = loadscans([],scannum,x);
      x = x'/1000;
    else
      error('Cannot currently guess suitable raw source for Herriot');
    end
  else
    V = [ 7.56393401961969   0.00412919996159   3.5410634E-7  -1.9782E-10];
    rawdata = polyval(fliplr(V),x);
  end
  P=polyfit(x,rawdata,p_coeffs-1);
  V = fliplr(P);
else
  V =[];
end
fname2 = [ 'sbase.' name '.ptb' ];
fid = fopen( fname2, 'w' );
if fid > 0
  fwrite( fid, [0 1], 'integer*4'); % func_base_ptbnu format
  fwrite( fid, [ 1000 min(nu) res ], 'real*8' ); % polyscale, nu_min, dnu
  fwrite( fid, [ 2*length(periods)+size(c_vector,1) length(nu) p_coeffs 0 ], 'integer*2' );
  % n_vectors n_pts poly_coeffs poly_of_nu
  fwrite( fid, ones(1,2*length(periods)+size(c_vector,1)), 'real*4' );
  % Initial parameter values
  fwrite( fid, V, 'real*4' );
  fwrite( fid, c_vector, 'real*4');
  for i=1:length(periods)
    theta = 2*pi*nu/periods(i);
    fwrite( fid, sin(theta), 'real*4');
    fwrite( fid, cos(theta), 'real*4');
    if nargout > 1
      Vout(:,2*i-1) = sin(theta);
      Vout(:,2*i) = cos(theta);
    end
  end
  fclose(fid);
  fprintf( 1, 'Output written to %s\n', fname2 );
else
  error('Cannot write to %s', fname2);
end
