function synth_PwrIn(cpci)
% synth_PwrIn(cpci);
% Extract primary SVD from specified range of cpci scans,
% perform deskew ala writeskewbase, and write output to
% PwrIn_$Wavename.mat
wv = waves_used(cpci);
if length(wv) > 1
  error('More than one waveform used in specified region');
end
icos = base2([], cpci); % Should probably be a single scan, but...
[U,S,V] = svds(icos,1);
tol = 10e-6;
npts = size(U,1);
[A,k] = skew_matrix( cpci, npts, tol );
U1 = A\U;
PwrIn = V(1,:)*S*U1; % I think I don't need the k divisor
ofile = [ 'PwrIn_', wv.Name, '.mat' ];
save( ofile, 'PwrIn' );
fprintf(1,'Output written to %s\n', ofile);
