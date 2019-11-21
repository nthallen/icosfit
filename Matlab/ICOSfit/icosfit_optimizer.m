classdef icosfit_optimizer < handle
  properties
    survey
    opt
    cfg_map
    ScanNumRange
  end
  
  methods
    function self = icosfit_optimizer(varargin)
      self.survey = [];
      self.ScanNumRange = [];
      self.opt.criteria = '';
      self.opt.mnemonic = ''; % string used for config files and output directories
      self.opt.cfg_ref = '';
      self.opt.xscale = 'linear';
      self.opt.cygwin_root = 'c:\cygwin64';
      self.cfg_map = { 'Verbosity', '35', 'epsilon2', '1e-4' };
      for i=1:2:length(varargin)-1
        if isfield(self.opt, varargin{i})
          self.opt.(varargin{i}) = varargin{i+1};
        end
      end
    end
    
    function get_scanregion(self)
      % Reads the cfg_ref file to obtain the ScanNumRange
      ifp = fopen(self.opt.cfg_ref,'r');
      while true
        tline = fgets(ifp);
        if isempty(tline) || isnumeric(tline)
          break;
        end
        a = regexp(tline, ...
          '^ *ScanNumRange *= *\[ *([0-9]+) *, *([0-9]+) *\] *;', ...
          'tokens');
        if ~isempty(a)
          self.ScanNumRange = [ ...
            str2num(a{1}{1}) str2num(a{1}{2}) ];
          fclose(ifp);
          return;
        end
      end
      fclose(ifp);
      error('ScanNumRange not found in cfg_ref %s', self.opt.cfg_ref);
    end
    
    function iterate(self, name, varargin)
      % create new config file with given parameters
      ofile = [ 'icosfit.' self.opt.mnemonic '.' name ];
      odir = [ 'ICOSout.' self.opt.mnemonic '.' name ];
      icosfit_reconfig(self.opt.cfg_ref, ofile, ...
        self.cfg_map{:}, varargin{:}, ...
        'OutputDir', odir);
      % run the fit
      self.savefile;
      if ispc
        cmd = [ self.opt.cygwin_root ...
          '\bin\bash -c ". /etc/profile.d/lapack0.sh; /bin/icosfit ' ...
          ofile ];
        res = system(cmd);
      else
        error('Non-PC platforms not yet sorted');
      end
      if res ~= 0
        error('"icosfit %s" apparently failed', ofile);
      end
      % add the fit to the survey
      new_svy = ...
        struct('base',odir,'value',length(self.survey)+1,'text',name);
      if isempty(self.survey)
        self.survey = new_svy;
      else
        self.survey(end+1) = new_svy;
      end
        
      self.savefile;
    end
    
    function savefile(IO)
      % IO.savefile
      % Writes the IO object to a .mat file with the name derived
      % from the mnemonic in IO.opt.mnemonic. The filename is prefixed
      % with 'IO_'.
      fname = sprintf('IO_%s.mat', IO.opt.mnemonic);
      save(fname, 'IO');
      fprintf(1, 'icosfit_optimizer saved to %s\n', fname);
    end
    
    % This has to move into a separate epsilon2_optimizer
    %function eps2_analysis(self, varargin)
    %end
  end
end
