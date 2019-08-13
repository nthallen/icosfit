function WaveSpecs = load_waves(errok)
% WaveSpecs = load_waves;
% Find waves.m, run it and return the structure it defines.
if nargin < 1
  errok = 0;
end
rundir = getrun(1);
ICOSfit_cfg = load_ICOSfit_cfg;
dirs = { '.', ...
    [ ICOSfit_cfg.Matlab_Path filesep rundir ], ...
    [ ICOSfit_cfg.Matlab_Path filesep rundir '/Base' ] };
if ~isdigit(rundir(end))
    rundir = rundir(1:end-1);
    dirs = [ dirs, ...
        [ ICOSfit_cfg.Matlab_Path filesep rundir ], ...
        [ ICOSfit_cfg.Matlab_Path filesep rundir '/Base' ] ];
end
for j = 1:length(dirs)
  path = [ dirs{j} '/' ICOSfit_cfg.WavesFile ];
  if exist(path,'file')
    % I did this before with 'run()', but run doesn't deal
    % with forward slashes.
    savedir = pwd;
    cd(dirs{j});
    eval(['run ' path]);
    cd(savedir);
    return;
  end
end
if errok
  WaveSpecs = [];
else
  error('Unable to locate waves file');
end
