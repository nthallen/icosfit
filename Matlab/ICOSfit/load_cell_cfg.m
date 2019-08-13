function cell_cfg = load_cell_cfg(use_default)
% cell_cfg = load_cell_cfg;
% Checks for the existence of a Cell_Config script and complains
% if one cannot be found. Below is a sample version of a
% CR_Config function.
%
%  function cell_cfg = Cell_Config;
%  % CR_Config defines local configuration and should be located
%  % in a local configuration directory (as opposed to a directory
%  % of shared scripts).
%  cell_cfg.Matlab_CD_Path = 'E:';
%  cell_cfg.ICOSfit_CD_Path = '/cd';
%  cell_cfg.HomeDir = '/home/CR';
if nargin < 1
  use_default = 0;
end
dirs = { '.', '..', '../..' };
loaded = 0;
for i=1:length(dirs)
  fname = [ dirs{i} '/Cell_Config.m' ];
  if exist(fname, 'file')
    cur = cd;
    cd( dirs{i} );
    cell_cfg = eval('Cell_Config;');
    cd( cur );
    loaded = 1;
    break;
  end
end
if ~loaded
    cell_cfg.CavityLength = '90.57';
    cell_cfg.fsr = '0.0293';
    cell_cfg.MirrorLoss = '215';
    cell_cfg.N_Passes = '0';
    cell_cfg.CavityFixedLength = '0';
end

if ~loaded && ~use_default
  cell_cfg = edit_cell_cfg( 'Config', cell_cfg );
end
