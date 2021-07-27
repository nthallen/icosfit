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
      self.opt.sopt = [];
      self.opt.criteria = '';
      self.opt.mnemonic = ''; % string used for config files and output directories
      self.opt.cfg_ref = '';
      self.opt.nscans = []; % For subsampling the ScanNumRange
      self.opt.xscale = 'linear';
      self.opt.cygwin_root = 'c:\cygwin64';
      self.opt.save_var = '';
      self.cfg_map = { 'Verbosity', '35', 'epsilon2', '5e-4' };
      for i=1:2:length(varargin)-1
        if isfield(self.opt, varargin{i})
          self.opt.(varargin{i}) = varargin{i+1};
        elseif isfield(self.opt.sopt, varargin{i})
          self.opt.sopt.(varargin{i}) = varargin{i+1};
        else
          self.cfg_map = [ self.cfg_map(:)' {varargin{i}} {varargin{i+1}} ];
          fprintf(1,'Assuming %s is a cfg_map item\n', varargin{i});
        end
      end
      if isempty(self.opt.mnemonic)
        error('Must specify mnemonic option');
      end
      if isempty(self.opt.save_var)
        self.opt.save_var = self.opt.mnemonic;
      end
      if exist(self.opt.mnemonic, 'dir')
        error('Subdirectory "%s" already exists', self.opt.mnemonic);
      end
      if ~mkdir('.', self.opt.mnemonic)
        error('Unable to create subdirectory "%s"', self.opt.mnemonic);
      end
    end
    
    function get_scanregion(self)
      % Reads the cfg_ref file to obtain the ScanNumRange
      ifp = fopen(self.opt.cfg_ref,'r');
      if ifp == -1
        error('Unable to open cfg_ref file "%s"', self.opt.cfg_ref);
      end
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
    
    function run_icosfit(self, cfgfile)
      if ispc
        cmd = [ self.opt.cygwin_root ...
          '\bin\bash -c ". /etc/profile.d/lapack0.sh; /bin/icosfit ' ...
          cfgfile ];
        res = system(cmd);
      else
        cmd = [ '/usr/local/bin/icosfit ' cfgfile ];
        res = system(cmd);
      end
      if res ~= 0
        error('"icosfit %s" apparently failed', cfgfile);
      end
    end
    
    function iterate(self, name, value, varargin)
      % create new config file with given parameters
      cfgfile = [ self.opt.mnemonic '/' 'icosfit.' name ];
      odir = [ self.opt.mnemonic '/' 'ICOSout.' name ];
      if isfolder(odir)
        fprintf(1,'Removing OutputDir %s\n', odir);
        rmdir(odir,'s');
      end
      if isempty(self.opt.nscans)
        icosfit_reconfig(self.opt.cfg_ref, cfgfile, ...
          self.cfg_map{:}, varargin{:}, ...
          'OutputDir', odir);
        % run the fit
        self.savefile;
        self.run_icosfit(cfgfile);
      else % nscans is specified
        % I need to know the BaselineFile. could be specified in
        % cfg_map or varargin or neither, if it's just in the
        % cfg_ref file.
        allopts = [ self.cfg_map varargin ];
        varargs.BaselineFile = [];
        for i=1:2:length(allopts)-1
          varargs.(allopts{i}) = allopts{i+1};
        end
        if isempty(varargs.BaselineFile)
          error('Must specify BaselineFile explicitly for subsampling');
        end
        if isempty(self.ScanNumRange)
          self.get_scanregion;
        end
        % Complain if PTEFile is not specified
        PTE = load(varargs.PTEFile);
        scans = PTE(:,1);
        V = scans >= self.ScanNumRange(1) & ...
          scans <= self.ScanNumRange(2);
        if size(PTE,2) < 12 || any(PTE(V,12) == 0)
          error('For nscans > 0, nu_F0 must be defined in PTEFile');
        end
        scans = scans(V);
        if self.opt.nscans < length(scans)
          ssix = round(linspace(1, length(scans), self.opt.nscans));
          scans = scans(ssix);
        end
        BaselineMnc = [ self.opt.mnemonic '_ss' ];
        BaselineFile = [ 'sbase.' BaselineMnc '.ptb' ];
        PTEFile = [ varargs.PTEFile ' + nu_F0' ];
        for i=1:length(scans)
          scan = scans(i);
          SR = sprintf('[%d,%d]', scan, scan);
          baseline_reinit(varargs.BaselineFile, BaselineMnc, scan, ...
            self.opt.mnemonic);
          icosfit_reconfig(self.opt.cfg_ref, cfgfile, ...
            allopts{:}, ...
            'PTEFile', PTEFile, ...
            'ScanNumRange', SR, ...
            'BaselineFile', [ self.opt.mnemonic '/' BaselineFile], ...
            'Threshold', '1e-3', ...
            'OutputDir', odir);
          self.run_icosfit(cfgfile);
        end
      end
      % add the fit to the survey
      self.add_run_to_survey(odir, value, name);
    end
    
    function add_run_to_survey(self, odir, value, name)
      % IO.add_run_to_survey(odir, value, name);
      % Adds the specified output directory to the survey
      % using the given value and name.
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
      fname = [ self.opt.mnemonic '/' 'Opt_' self.opt.mnemonic '.mat' ];
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
