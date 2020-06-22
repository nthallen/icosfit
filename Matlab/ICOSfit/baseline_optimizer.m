classdef baseline_optimizer < icosfit_optimizer
  properties
    n_etalons
    n_rescale
    etalon_periods
    etalon_maxf
    k
  end
  methods
    function self = baseline_optimizer(varargin)
      % options are:
      %   cfg_ref 
      %   mnemonic ('optb')
      %   save_var ('OptB')
      %   n_coeffs ([])
      % bopt.n_coeffs = [];
      self = self@icosfit_optimizer( ...
        'mnemonic','optb','criteria','Baseline','save_var','OptB', ...
        varargin{:});
        % 'sopt', bopt, ...
      self.n_etalons = 0;
      self.n_rescale = 0;
      self.etalon_periods = [];
      self.etalon_maxf = 0;
      self.k = 1;
%       for i=1:2:length(varargin)-1
%         if isfield(self.opt, varargin{i})
%           self.opt.(varargin{i}) = varargin{i+1};
%         elseif isfield(self.bopt, varargin{i})
%           self.bopt.(varargin{i}) = varargin{i+1};
%         else
%           % self.cfg_map.(varargin{i}) = varargin{i+1};
%           self.cfg_map = [ self.cfg_map(:)' {varargin{i}} {varargin{i+1}} ];
%           fprintf(1,'Assuming %s is a cfg_map item\n', varargin{i});
%           % error('Unrecognized option: %s', varargin{i});
%         end
%       end
      self.get_scanregion;
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
      name = sprintf('%dp', n_pcoeffs);
      writeetlnbase(name, n_pcoeffs, [], [], [], self.ScanNumRange(1), ...
        self.opt.mnemonic);
      % create new config file, run the fit and add to the survey
      value = length(self.survey)+1;
      self.iterate(name, value, ...
        'BaselineFile', [ self.opt.mnemonic '/' 'sbase.' name '.ptb' ]);
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
      period = baseline_add_etalon(self.survey(end).base, oname, ...
        [], self.etalon_periods, maxf, self.opt.mnemonic, self.k);
      if nargout > 0
        period_out = period;
      end
    end
    
    function add_etalon(self, maxf)
      % OptB.add_etalon([maxf])
      % Calls analyze_etalons and operates on the results.
      if isempty(self.survey)
        fprintf(1,'No data to analyze\n');
        return;
      end
      if nargin < 2, maxf = 0; end
      name = self.survey(end).text;
      t = regexp(name,'^(.*[^0-9er])','tokens');
      t = t{1};
      newname = sprintf('%s%de',t{1},self.n_etalons+1);
      % fprintf(1,'name=%s newname=%s\n', name, newname);
      period = self.analyze_etalons(maxf, newname);
      self.n_etalons = self.n_etalons+1;
      self.etalon_periods(self.n_etalons) = period;
      value = length(self.survey)+1;
      self.iterate(newname, value, ...
        'BaselineFile', [ self.opt.mnemonic '/sbase.' newname '.ptb' ]);
    end
    
    function rescale_baseline(OptB)
      % OptB.rescale_baseline()
      %
      % Analyzes the scaling of baseline parameters and
      % creates a new appropriately scaled baseline file.
      name = OptB.survey(end).text;
      t = regexp(name,'^(.*[^0-9r])([0-9]*)(r?)$','tokens');
      t = t{1};
      if strcmp(t{3},'r')
        if isempty(t{2})
          nr = 1;
        else
          nr = str2num(t{2});
        end
        newname = sprintf('%s%dr',t{1},nr+1);
      else
        if ~isempty(t{2})
          error('Run name "%s" ends in digits', name);
        end
        newname = [ name 'r' ];
      end
      baseline_rescale(OptB.survey(end).base, newname, [], OptB.opt.mnemonic);
      value = length(OptB.survey)+1;
      OptB.iterate(newname, value, ...
        'BaselineFile', [ OptB.opt.mnemonic '/sbase.' newname '.ptb' ]);
    end

    function update_menus(self, f)
      me = uimenu(f,'Text','Analysis');
      uimenu(me,'Text','rrfit','Callback',@(src,evt)self.rrfit());
      uimenu(me,'Text','Scaling','Callback', ...
        @(src,evt)self.analyze_scaling());
      uimenu(me,'Text','Etalons','Callback', ...
        @(src,evt)self.analyze_etalons());
      me = uimenu(f,'Text','Operations');
      uimenu(me,'Text','Rescale','Callback', ...
        @(src,evt)self.rescale_baseline());
      uimenu(me,'Text','Add Etalon','Callback', ...
        @(src,evt)self.add_etalon());
    end
  end
end