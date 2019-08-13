function ICOSfit_cfg = load_ICOSfit_cfg(use_default)
% ICOSfit_cfg = load_ICOSfit_cfg;
% Checks for the existence of an ICOSfit_Config script
% invokes the interactive dialog if one cannot be found. 
if nargin < 1
  use_default = 0;
end
dirs = { '.', '..', '../..' };
loaded = 0;
for i=1:length(dirs)
  fname = [ dirs{i} '/ICOSfit_Config.m' ];
  if exist(fname, 'file')
    cur = cd;
    cd( dirs{i} );
    ICOSfit_cfg = ICOSfit_Config;
    cd( cur );
    loaded = 1;
    break;
  end
end
if ~loaded
  if ispc
    ICOSfit_cfg.Matlab_Path = 'D:/Data/HCI';
    ICOSfit_cfg.ICOSfit_Path = '/Data/HCI';
  else
    ICOSfit_cfg.Matlab_Path = '~/Carbon/RAW_DATA';
    ICOSfit_cfg.ICOSfit_Path = '~/Carbon/RAW_DATA';
  end

end
if ~isfield(ICOSfit_cfg,'WavesFile')
  ICOSfit_cfg.WavesFile = 'Base/QCLI_C.m';
end
if ~isfield(ICOSfit_cfg,'ScanDir')
  ICOSfit_cfg.ScanDir = 'SSP_C';
end
if ~loaded && ~use_default
  ICOSfit_cfg = edit_ICOSfit_cfg( 'Config', ICOSfit_cfg );
end
