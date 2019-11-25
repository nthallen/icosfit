classdef icosfit_optimizer < handle
  properties
    survey
    opt
    cfg_map
    ScanNumRange
    IR
  end
  
  methods
    function self = icosfit_optimizer(varargin)
      self.survey = [];
      self.ScanNumRange = [];
      self.IR = [];
      self.opt.criteria = '';
      self.opt.mnemonic = ''; % string used for config files and output directories
      self.opt.cfg_ref = '';
      self.opt.xscale = 'linear';
      self.opt.cygwin_root = 'c:\cygwin64';
      self.opt.save_var = 'Opt';
      self.cfg_map = { 'Verbosity', '35', 'epsilon2', '5e-4' };
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
    
    function iterate(self, name, value, varargin)
      % create new config file with given parameters
      ofile = [ 'icosfit.' self.opt.mnemonic '.' name ];
      odir = [ 'ICOSout.' self.opt.mnemonic '.' name ];
      icosfit_reconfig(self.opt.cfg_ref, ofile, ...
        self.cfg_map{:}, varargin{:}, ...
        'OutputDir', odir);
      % run the fit
      self.savefile;
      if isfolder(odir)
        fprintf(1,'Removing OutputDir %s\n', odir);
        rmdir(odir,'s');
      end
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
        struct('base',odir,'value',value,'text',name);
      if isempty(self.survey)
        self.survey = new_svy;
      else
        self.survey(end+1) = new_svy;
      end
        
      self.savefile;
      if isempty(self.IR)
        self.UI;
      else
        self.IR.refresh(self.survey);
      end
    end
    
    function savefile(self)
      % OptI.savefile
      % Writes the OptI object to a .mat file with the name derived
      % from the mnemonic in OptI.opt.mnemonic. The filename is prefixed
      % with 'OptI_'.
      save_IR = self.IR;
      self.IR = [];
      S.(self.opt.save_var) = self;
      fname = sprintf('Opt_%s.mat', self.opt.mnemonic);
      save(fname, '-struct', 'S');
      fprintf(1, '%s %s saved to %s\n', class(self), ...
        self.opt.save_var, fname);
      self.IR = save_IR;
    end
    
    function UI(self)
      if isempty(self.IR)
        self.IR = icosfit_runs('criterion', self.opt.criteria, ...
          'units', self.opt.criteria, 'scale', self.opt.xscale, ...
          'survey', self.survey, 'Opt', self);
      end
      self.IR.show_params;
    end
    
    function analyze_scaling(OptI)
      % IO.analyze_scaling;
      % Produces a figure showing the scaling of fit parameters
      icosfit_scale_check(OptI.survey(end).base);
    end
    
    function rrfit(OptI, idx)
      if nargin < 2
        idx = 0;
      end
      if idx == 0
        if ~isempty(OptI.IR) && OptI.IR.inp_idx > 0 && ...
              OptI.IR.inp_idx <= length(OptI.survey)
          idx = OptI.IR.inp_idx;
        else
          idx = length(OptI.survey);
        end
      end
      if idx > 0
        rrfit(OptI.survey(idx).base);
      end
    end
    
    function update_menus(~, ~)
      % OptI.update_menus(f)
      % Add any application-specific menus to the figure
    end
    % This has to move into a separate epsilon2_optimizer
    %function eps2_analysis(self, varargin)
    %end
  end
end
