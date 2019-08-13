function [ nu, vectors, p_coeffs, Ptype, PV, Pscale ] = readetlnbase( file )
% [ nu, vectors, p_coeffs, Ptype, PV, Pscale ] = readetlnbase( file );
% read func_base_ptbnu file format for baseline files containing
% polynomials and etalons (or other vectors of nu).
% FILEFORMAT (from funceval.h):
% // This is a function supporting vectors as a function of
% // nu as well as polynomials as a function of x or nu
% // The file format is:
% // i*4  0  To distinguish from func_base_svdx format
% // i*4  1  To identify func_base_ptbnu format
% // f*8 polynomial scale factor
% // f*8 nu0 smallest value of nu
% // f*8 dnu increment between samples
% // i*2 n_vectors
% // i*2 npts per vector
% // i*2 number of polynomial coefficients: polynomial degree + 1
% // i*2 Ptype: polynomial of x == 0, nu == 1
% // f*4 X n_vectors initial parameter values
% // f*4 X PV: polynomial degree initial parameter values
% // f*4 X npts X n_vectors: vector data in column order
%
fid = fopen( file, 'r' );
if fid > 0
    A = fread( fid, 2, 'integer*4'); 
    if ( A(1) ~= 0 || A(2) ~= 1 )
        disp('Error: File is not in func_base_ptbnu format');
        return
    end
    A = fread( fid, 3, 'real*8' );
    Pscale = A(1); nu0 = A(2); dnu = A(3);
    A = fread( fid, 4, 'integer*2' );
    n_vectors = A(1); npts = A(2); p_coeffs = A(3); Ptype = A(4); % x== 0, nu ==1
    n_vectors_init_param = fread( fid, n_vectors, 'real*4' );
    poly_init_param = fread( fid, p_coeffs, 'real*4' );
    PV = flipud(poly_init_param);
    vectors = fread( fid, [npts,n_vectors], 'real*4' );
    
    nu = nu0 + (0:npts-1)'*dnu;
else
  error('Cannot read file %s', file);
end
