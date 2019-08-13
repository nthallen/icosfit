function scannums = listscans( base_in )
% scans = listscans( [ base_in ] )
% Identifies what scan indexes are actually present.
% See also gen_PT
if nargin < 1
  base_in = [];
end
base = find_scans_dir(base_in);
scannums = check_dir(base,0)+1;

function scannums = check_dir( path, ctin )
D = dir(path);
dirs = regexp({D.name}, '^\d+$');
I = [];
for i=1:length(dirs)
  if ~isempty(dirs{i})
    I(end+1) = i;
  end
end
% I = find(cellfun(@isempty,regexp({D.name}, '^\d+$'))==0);
if isempty(I)
  % look for .dat files
  J = regexp({D.name}, '^\d+(?=\.dat$)', 'match');
  I = [];
  for i=1:length(J)
    if ~isempty(J{i})
      I(end+1) = i;
    end
  end
  % I = find(~cellfun(@isempty, J));
  scannums = [];
  for i=1:length(I)
    scannums = [ scannums; ctin + str2num(J{I(i)}{1}) ];
  end
  % scannums = ctin + cellfun( @decell, {J{I}} )';
else
  ind = ctin+str2num(char({D(I).name}));
  scannums = [];
  for i=1:length(I)
    scannums = [ scannums; check_dir( [ path '/' D(I(i)).name ], 60*ind(i) ) ];
  end
end
return

function n = decell( x )
n = str2num(x{1});
return
