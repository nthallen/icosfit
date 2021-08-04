function PTE_add_nu_F0(base,ofile)
% PTE_add_nu_F0(OutputDir, ofile)
%
% OutputDir is the output directory of a run covering the entire run
%
% ofile is the name of the output file, defaulting to appending '_nu.txt'
% to the file used in the fit.
%
% Using the output from a complete run, replaces column 12 in the PTE
% file with the nu_F0 from the fit output
S = ICOS_setup(base);
PTE = load(S.PTEfile);
if nargin < 2
  ofile = [ S.PTEfile(1:end-4) '_nu.txt'];
end
% Figure out what rows of PTE we need to include:
rows = interp1(PTE(:,1),1:size(PTE,1),S.scannum,'nearest');
if any(S.scannum ~= PTE(rows,1))
  error('Not all rows found in %s\n', S.PTEfile);
end
PTE(rows,12) = S.nu_F0;
PTEnu = PTE(rows,:);
save(ofile, 'PTEnu', '-ASCII');
