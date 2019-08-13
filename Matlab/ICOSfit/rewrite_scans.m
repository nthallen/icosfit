function rewrite_scans(ibase,obase,M,index)
% rewrite_scans(ibase,obase,M[,starting_index);
% This program is useful if spectra are inverted. It is better to fix it in hardware. 
% Should be customized for each axis and probably a specific version should be made 
% and copied into local directories.
if nargin < 1 || isempty(ibase)
   ibase = 'SSP';
end
if nargin < 2 || isempty(obase)
   obase = 'SSPo';
end
if nargin < 3 || isempty(M)
    M = [ 0 0 1; 0 1 0; 1 0 0];
end
if nargin < 4 || isempty(index)
  index = 1;
end
scans = listscans(ibase);
scans = scans(scans >= index);
for i=1:length(scans)
  scan = scans(i);
  pi = mlf_path(ibase,scan);
  [fi,hdr] = loadbin(pi);
  if isempty(fi)
    warning('File not found: %d => %s', scan, ibase);
  else
    po = mlf_path(obase,scan);
    fo = fi * M;
    mlf_mkdir(obase,scan);
    writebin( po, fo, hdr );
  end
end
