function hdrs = loadscanhdrs(scans)
% hdrs = loadscanhdrs(scans)
base = find_scans_dir([]);
p = mlf_path(base, scans(1));
[~,hdr] = loadbin(p);
hdrs(1) = hdr;
hdrs(length(scans)) = hdr;
for i=2:length(scans)
  p = mlf_path(base,scans(i));
  [~,hdr] = loadbin(p);
  hdrs(i) = hdr;
end
