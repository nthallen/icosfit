function PTE_gen( scannums, PTEfile, PTparams );
% PTE_gen( [ scannums [, PTEfile [, PTparams ] ] ] );
%  Make up numbers for a tuning rate in the absence of an etalon
%  If we don't have P and T, make them up too.
%  For scannums, use listscans
% PTparams correspond to columns 4:end of PTE.txt
if nargin < 3
  PTparams = ...
    [200 17.91724 34.33037 1.489716 -9.231663 0.09478366 -14.00556 0.2113355 ];
elseif any(size(PTparams) ~= [1 8])
  error('PTparams input must be 1x8');
end
if nargin < 2
  PTEfile = 'PTE.txt';
end
if nargin < 1
  scannums = listscans;
end

if exist('PT.mat','file')
  PT = load('PT.mat');
else
  PT = [];
end
if isfield(PT,'ScanNum')
  if min(scannums) < min(PT.ScanNum) | max(scannums) > max(PT.ScanNum)
    warning('ScanNum files exceed PT file indices');
  end
  v = find(diff(PT.ScanNum)>0)+1;
end
if isfield(PT,'ScanNum') && isfield(PT,'CellP')
  P = interp1(PT.ScanNum(v),PT.CellP(v),scannums,'nearest');
else
  warning('Assuming 40 Torr');
  P = 40*ones(size(scannums));
end
if isfield(PT,'ScanNum') && isfield(PT,'Tavg')
  T = interp1(PT.ScanNum(v),PT.Tavg(v),scannums,'nearest');
else
  warning('Assuming 25 Celcius');
  T = (25+273.15)*ones(size(scannums));
end
ofp = fopen(PTEfile, 'a');
%fprintf( ofp, '%d %.2f %.1f %d %.7g %.7g %.7g %.7g %.7g %.7g %.7g\n', ...
%  0, P(1), T(1), PTparams );
for i=1:length(scannums)
  fprintf( ofp, '%d %.2f %.1f %d %.7g %.7g %.7g %.7g %.7g %.7g %.7g\n', ...
    scannums(i), P(i), T(i), PTparams );
end
fclose(ofp);

      
