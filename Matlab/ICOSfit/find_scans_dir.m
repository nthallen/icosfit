function base = find_scans_dir( base_in, ICOSfit )
% base = find_scans_dir(base_in [, ICOSfit]);
% Finds the appropriate base directory for log files
% If the ICOSfit argument is provided and is non-zero, the
% path appropriate for use by ICOSfit is returned.
% (see load_ICOSfit_cfg for details).
if nargin < 1
  base_in = '';
end
if ~isempty(base_in)
  if exist(base_in,'dir')
    base = base_in;
  else
    error('Input base "%s" is not a directory', base_in);
  end
else
    ICOSfit_cfg = load_ICOSfit_cfg;
    runF = getrun(1);
    base = ICOSfit_cfg.ScanDir;
    if exist(base, 'dir')
        return;
    end
    base = [ ICOSfit_cfg.Matlab_Path filesep runF ...
            filesep ICOSfit_cfg.ScanDir ];
    if ~exist(base, 'dir') && ~isdigit(runF(end))
        runF = runF(1:end-1);
        base = [ ICOSfit_cfg.Matlab_Path filesep runF ...
            filesep ICOSfit_cfg.ScanDir ];
    end
    if ~exist(base, 'dir')
        error( [ 'Unable to locate appropriate base for ' getrun(0) ] );
    end
    if nargin > 1 && ICOSfit
      % Do not use filesep here, since ICOSfit always expects '/'
      base = [ ICOSfit_cfg.ICOSfit_Path '/' runF ...
         '/' ICOSfit_cfg.ScanDir ];
    end
end
