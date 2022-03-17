function ofile_out = PTE_add_nu_F0(base,varargin)
% PTE_add_nu_F0(OutputDir)
% PTE_add_nu_F0(OutputDir[, 'ofile', ofile] ['ifile', ifile])
% ofile = PTE_add_nu_F0(OutputDir [,...]);
%
% OutputDir is the output directory of a run covering the entire run
%
% ifile is the name of the input file, defaulting to the one used
% in OutputDir, but can be replaced with another, possibly with
% more scans. The nu_F0 values from OutputDir are interpolated
% onto the rows of ifile. This will also extrapolate at the ends,
% assuming that the extrapolation will be limited.
%
% ofile is the name of the output file, defaulting to appending '_nu.txt'
% to the ifile used in the fit.
%
% Using the output from a complete run, replaces column 12 in the PTE
% file with the nu_F0 from the fit output
ifile = '';
ofile = '';
ifile_explicit = 0;
for i = 1:2:length(varargin)-1
  switch varargin{i}
    case 'ifile'
      ifile = varargin{i+1};
      ifile_explicit = 1;
    case 'ofile'
      ofile = varargin{i+1};
    otherwise
      error('Invalid option');
  end
end
S = ICOS_setup(base);
if isempty(ifile)
  ifile = S.PTEfile;
end
if isempty(ofile)
  ofile = strrep(ifile, '.txt', '_nu.txt');
  if strcmp(ifile, ofile)
    error('Automatic ofile setting failed due to non ''.txt'' ending.');
  end
end
PTE = load(ifile);
% Figure out what rows of PTE we need to include:
if ifile_explicit
  PTEnu = PTE;
  PTEnu(:,12) = interp1(S.scannum,S.nu_F0,PTEnu(:,1),'linear','extrap');
else
  rows = interp1(PTE(:,1),1:size(PTE,1),S.scannum,'nearest');
  if any(S.scannum ~= PTE(rows,1))
    error('Not all rows found in %s\n', S.PTEfile);
  end
  PTE(rows,12) = S.nu_F0;
  PTEnu = PTE(rows,:);
end
save(ofile, 'PTEnu', '-ASCII');
if nargout > 0
  ofile_out = ofile;
end
