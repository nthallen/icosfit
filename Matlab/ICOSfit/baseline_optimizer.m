classdef baseline_optimizer < icosfit_optimizer
  properties
    %n_etalons
    %n_rescale
    %etalon_periods
    etalon_maxf
    k
    input
    basenames % struct recording number of instances
  end
  methods
    function self = baseline_optimizer(varargin)
      % options are:
      %   cfg_ref 
      %   mnemonic ('optb')
      %   save_var ( mnemonic )
      %   uses_input ( 0 )
      bopt.uses_input = 0;
      self = self@icosfit_optimizer( ...
        'mnemonic','optb','criteria','Baseline', 'sopt', bopt, ...
        varargin{:});
        % 'sopt', bopt, ...
      %self.n_etalons = 0;
      %self.n_rescale = 0;
      %self.etalon_periods = [];
      self.etalon_maxf = 0;
      self.k = 1;
      self.get_scanregion;
      self.basenames = [];
      self.input = '';
      if self.opt.sopt.uses_input
        self.input = ' + Input';
      end
      cellparams=load_cell_cfg;
      if cellparams.N_Passes == 0
        % 100 is a guess at "enough points to exceed the lifetime in the
        % cell"
        [~,self.k] = skew_matrix(self.ScanNumRange(1),100,1e-6);
      end
    end
    
    function new_polynomial(self, n_pcoeffs)
      % IO.new_polynomial(n_pcoeffs);
      % Create a new baseline file using the specified number of
      % polynomial coefficients.
      % self.opt.sopt.n_coeffs = n_pcoeffs;

      User = struct( ...
        'basename', '', 'fullname', '', 'n_poly_coeffs', n_pcoeffs, ...
        'periods', [], 'rescaled', 0);
      User = self.update_user_names(User);
      if isempty(User); return; end
      writeetlnbase(User.fullname, n_pcoeffs, [], [], [], self.ScanNumRange(1), ...
        self.opt.mnemonic);
      % create new config file, run the fit and add to the survey
      value = length(self.survey)+1;
      self.iterate(User.fullname, value, User, ...
        'BaselineFile', ...
          [ self.opt.mnemonic '/' 'sbase.' User.fullname '.ptb' self.input ]);
    end
    
    function period_out = analyze_etalons(self, maxf, oname)
      % OptB.analyze_etalons([maxf[, oname]])
      % oname is the name fragment to use for the new baseline file,
      % the new config file and the new output directory.
      % If oname is empty, this just displays the analysis.
      % maxf specifies the maximum frequency (in cm) to be considered
      % for the new etalon. If maxf is not specified or 0, the last
      % used value will be used or a value limited by the line widths
      % in play. If maxf is less than 0, the stored value is reset to
      % 0.
      if isempty(self.survey)
        fprintf(1,'No data to analyze\n');
        return;
      end
      if nargin < 2, maxf = 0; end
      if nargin < 3, oname = ''; end
      if maxf == 0
        maxf = self.etalon_maxf;
      elseif maxf < 0
        self.etalon_maxf = 0;
        maxf = 0;
      else
        self.etalon_maxf = maxf;
      end
      User = self.survey(self.IR.inp_idx).User;
      base = self.survey(self.IR.inp_idx).base;
      period = baseline_add_etalon(base, oname, ...
        [], User.periods, maxf, self.opt.mnemonic, self.k);
      if nargout > 0
        period_out = period;
      end
    end
 
    function period_out = analyze_etalons2(self, npeaks)
      if nargin < 2; npeaks = []; end
      BEA = baseline_etalon_analyzer(self);
      BEA.analyze(npeaks);
    end

    function add_etalon(self, maxf)
      % OptB.add_etalon([maxf])
      % Calls analyze_etalons and operates on the results.
      if isempty(self.survey)
        fprintf(1,'No data to analyze\n');
        return;
      end
      if nargin < 2, maxf = 0; end
      User = self.survey(self.IR.inp_idx).User;
      %name = self.survey(end).text;
      %t = regexp(name,'^(.*[^0-9er])','tokens');
      %t = t{1};
      User.periods = [ User.periods 0 ];
      User.rescaled = 0;
      User = self.update_user_names(User);
      % fprintf(1,'name=%s newname=%s\n', name, newname);
      period = self.analyze_etalons(maxf, User.fullname);
      User.periods(end) = period;

      %self.n_etalons = self.n_etalons+1;
      %self.etalon_periods(self.n_etalons) = period;
      value = length(self.survey)+1;
      self.iterate(User.fullname, value, User, ...
        'BaselineFile', ...
          [ self.opt.mnemonic '/sbase.' User.fullname '.ptb' self.input ]);
    end
    
    function rescale_baseline(self)
      % OptB.rescale_baseline()
      %
      % Analyzes the scaling of baseline parameters and
      % creates a new appropriately scaled baseline file.
      
      if isempty(self.survey) || isempty(self.IR)
        fprintf(1,'No data to analyze\n');
        return;
      end
      survey = self.survey(self.IR.inp_idx);
      User = survey.User;
      User.rescaled = User.rescaled+1;
      User = self.update_user_names(User);

      baseline_rescale(survey.base, User.fullname, [], self.opt.mnemonic);
      value = length(self.survey)+1;
      self.iterate(User.fullname, value, User, ...
        'BaselineFile', ...
          [ self.opt.mnemonic '/sbase.' User.fullname '.ptb' self.input]);
    end

    function User = update_user_names(self, User)
      pnm = sprintf('%dp',User.n_poly_coeffs);
      nperiods = length(User.periods);
      if nperiods > 0
        enm = sprintf('%de', nperiods);
      else
        enm = '';
      end
      if User.rescaled > 0
        if User.rescaled == 1
          rnm = 'r';
        else
          rnm = sprintf('%dr', User.rescaled);
        end
      else
        rnm = '';
      end
      User.basename = [pnm enm rnm];
      mnc = ['B' User.basename];
      if isfield(self.basenames,mnc)
        if isempty(enm) && isempty(rnm)
          errordlg(sprintf( ...
            'new_polynomial(%d) already processed, skipping',n_pcoeffs), ...
            'Duplicate Baseline');
          User = [];
          return;
        end
        inst = self.basenames.(mnc);
        User.fullname = sprintf('%s_%s',User.basename,char('a'+inst));
        self.basenames.(mnc) = inst+1;
      else
        User.fullname = User.basename;
        self.basenames.(mnc) = 0;
      end
    end

    function update_menus(self, f)
      me = uimenu(f,'Text','Analysis');
      uimenu(me,'Text','rrfit','Callback',@(src,evt)self.rrfit());
      uimenu(me,'Text','Scaling','Callback', ...
        @(src,evt)self.analyze_scaling());
      uimenu(me,'Text','Etalons','Callback', ...
        @(src,evt)self.analyze_etalons());
      uimenu(me,'Text','Etalons2','Callback', ...
        @(src,evt)self.analyze_etalons2());
      me = uimenu(f,'Text','Operations');
      uimenu(me,'Text','Rescale','Callback', ...
        @(src,evt)self.rescale_baseline());
      uimenu(me,'Text','Add Etalon','Callback', ...
        @(src,evt)self.add_etalon());
    end
  end
end