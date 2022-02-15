function average_spectra2(secs_avg, PTEfile)
% average_spectra2(secs_avg[, PTEfile])
% Average scans for the specified number of seconds
% Output goes in the same directory as the current scans directory.
% This differs from average_spectra(), which is based on the
% real RAW data.
% PTEfile defaults to 'PTE.txt'
% All scans listed in the PTEfile will be averaged
% All scans listed in the  PTEfile must correspond to the same waveform
% Time bins will be aligned with even multiples of the average time.
if nargin < 2; PTEfile = 'PTE.txt'; end
base = find_scans_dir;
[path,name,ext] = fileparts(base);
suffix = [ '.average' num2str(secs_avg) ];
obase = fullfile(path, [name ext suffix]);
[path,name,ext] = fileparts(PTEfile);
PTEofile = fullfile(path, [name suffix ext]);

PTE=load(PTEfile);
scans = PTE(:,1);
wvs = waves_used(scans);
if ~isscalar(wvs)
  error('PTE file covers more than one waveform');
end
wvs_per_bin = wvs.FTrigger/wvs.NCoadd;
min_wvs_per_bin = 0.6*wvs_per_bin;
T = scantime(scans);
% Check that T is monotonically increasing
if any(diff(T)<=0)
  error('Times or PTE scans are not monotonically increasing');
end
PTEo = fopen(PTEofile, 'w');

T0 = floor(T(1)/secs_avg)*secs_avg;
while T0 <= T(end)
  V = T >= T0 & T < (T0+secs_avg);
  n_avg = sum(V);
  if n_avg >= min_wvs_per_bin
    binscans = scans(V);
    [icos,etln] = loadscans(base,binscans);
    icos = mean(icos,2);
    etln = mean(etln,2);
    new_scannum = round(mean(binscans));
    mlf_mkdir(obase, new_scannum);
    writebin(mlf_path(obase,new_scannum),[icos,etln]);
    nearest_scan_index = interp1(binscans, find(V), new_scannum,'nearest');
    PTEnew = PTE(nearest_scan_index,2:12);
    fprintf(PTEo, ...
        '%d %.2f %.1f %d %.7g %.7g %.7g %.7g %.7g %.7g %.7g %.6g %d\n', ...
        new_scannum, PTEnew, n_avg);
  end
  T0 = T0+secs_avg;
end
fclose(PTEo);
