function [ D, T ] = load_mat_files( varargin )
% [ D, T ] = load_mat_files(...);
% Load the first of the specified files found in the
% usual places. Files are specified without '.mat' extension.
% T if requested, gets set to the appropriate time variable.
% Example:
%  [D,T] = load_mat_files('PT', 'PandT');
run = getrun(1);
ICOSfit_cfg = load_ICOSfit_cfg;
dirs = { '.', [ ICOSfit_cfg.Matlab_Path '/anal/' run ], ...
    [ ICOSfit_cfg.Matlab_Path '/' run ] };
for i = 1:length(varargin)
  file = varargin{i};
  for j = 1:length(dirs);
    dir = dirs{j};
    path = [ dir '/' file '.mat' ];
    if exist( path, 'file')
      D = load(path);
      if nargout > 1; T = getfield( D, ['T' file]); end
      return;
    end
  end
end
error([ 'Unable to locate file ' varargin{1} ]);
