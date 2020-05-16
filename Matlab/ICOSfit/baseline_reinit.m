function baseline_reinit(ifile, ofilemnc, scannum)
% baseline_reinit(ifile, ofile, scannum)
% ifile is the input baseline file name
% ofilemnc is the middle part of the output baseline file name:
%   sbase.ofilemnc.ptb.
% Reads ifile and invokes writeetlnbase() to create ofile, reinitializing
% the polynomial coefficients to match scannum's power curve
[ nu, vectors, p_coeffs, ~, ~, ~ ] = readetlnbase( ifile );
writeetlnbase( ofilemnc, p_coeffs, nu, vectors, [], scannum );
