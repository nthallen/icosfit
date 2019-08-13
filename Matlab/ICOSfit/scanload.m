function fe = scanload( ScanNum, base, binary )
% f = scanload( ScanNum [, base[, binary]] )
% binary defaults to TRUE
% base defaults to Config File ScanDir as per find_scans_dir()
ICOSfit_cfg = load_ICOSfit_cfg;
if nargin < 3
  binary = 1;
  if nargin < 2
    base = '';
  end
end
base = find_scans_dir(base);
ifile = mlf_path(base,ScanNum,'.dat');
if binary == 0
  fe = load(ifile);
else
  fe = loadbin(ifile);
end
