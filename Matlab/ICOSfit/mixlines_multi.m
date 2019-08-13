function [chi,scannum,lines] = mixlines_multi( Regions, Suffixes )
% [chi,scannum,lines] = mixlines_multi( Regions, Suffixes );
% Assuming output directories of the form ICOSout.<region>.<suffix>,
% calls mixlines on each directory and builds up combined chi, scannum
% and lines matrices. Each output directory for a specified region
% must have exactly the same scannum numbers, and each output directory
% for a given suffix must have the same line definitions (both of
% which requirements are checked.)
chi = [];
scannum = [];
ScanNum = {}; % keep track of scannum vectors for each region
lines = [];
if ~iscell(Regions)
  Regions = { Regions };
end
if nargin < 2
  Suffixes = '';
end
if ~iscell(Suffixes)
  Suffixes = { Suffixes };
end
for i = 1:length(Suffixes)
  suffix = Suffixes{i};
  if length(suffix) > 0
    suffix = [ '.' suffix ];
  end
  chi_s = []; % cumulative chi for this suffix
  lines_s = [];
  for j = 1:length(Regions)
    [chi_sr,scannum_sr,P,lines_sr] = mixlines(['ICOSout.' Regions{j} suffix ], 4);
    if size(lines_s,2) > 0
      if any(size(lines_s) ~= size(lines_sr)) | ...
          any(any((lines_s(:,[1:3]) ~= lines_sr(:,[1:3]))))
        error(sprintf('Lines for %s.%s differ from previous regions', Regions{j}, Suffixes{i} ));
      end
    else
      lines_s = lines_sr;
    end
    if length(ScanNum) < j
      ScanNum{j} = scannum_sr;
      scannum = [ scannum; NaN; scannum_sr ];
    elseif length(ScanNum{j}) ~= length(scannum_sr)
      error(sprintf('scannum for %s.%s is different length than previous suffixes', ...
        Regions{j}, Suffixes{i} ));
    elseif any(ScanNum{j} ~= scannum_sr)
      error(sprintf('scannum values differ for %s.%s from previous suffixes', ...
        Regions{j}, Suffixes{i} ));
    end
    chi_s = [ chi_s; NaN*ones(1,size(chi_sr,2)); chi_sr ];
  end
  chi = [ chi chi_s ];
  lines = [ lines; lines_s ];
end
