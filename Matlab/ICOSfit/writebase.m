function writebase( ofile, U, S, V );
% writebase( ofile, U, S, V );
% Writes a binary baseline file suitable for icosfit input.
fe = [ V(1,:)*S; U ];
writebin( ofile, fe );
