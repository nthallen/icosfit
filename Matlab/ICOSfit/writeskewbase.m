function Uout = writeskewbase( region, U, S, V, tol );
% Uout = writeskewbase( region, U, S, V [ , tol ] );
% region should be the scan number of the start of the
% baseline region or the region name.
% U, S and V are the relevant outputs from SVDS()
% Requires MirrorLoss.mat and CavityLength.mat
% tol is the tolerance to which we want to calculate skew
%   This should match the SkewTolerance keyword in the fitline file
%   It defaults to 10e-6
%
% Note that in this implementation the (1-R)^2 factor arising from loss
% entering and exiting the cavity is simply wrapped into the input
% power since (1-R)^2 is assumed to be constant.

% if isnumeric(region)
%   ofile = sprintf('sbase%d.dat', region);
% else
%   ofile = [ 'sbase.' region '.dat' ];
% end
ofile='sbase.dat';
if nargin < 5
  tol = 10e-6;
end
npts = size(U,1);
[A,k] = skew_matrix( region, npts, tol );
U1 = A\U;
%fprintf(1,'N = %f\nM = %d\nk = %f\n', N, M, k );
fe = [ (V(1,:)*S)/k; U1 ];
writebin( ofile, fe );
fprintf(1,'Output written to %s\n', ofile );
if nargout > 0
  Uout = U1 / (1-R2N);
end
