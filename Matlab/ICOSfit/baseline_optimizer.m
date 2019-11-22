classdef baseline_optimizer < icosfit_optimizer
  properties
    bopt % baseline options
    n_etalons
    n_rescale
    etalon_periods
    etalon_maxf
  end
  methods
    function self = baseline_optimizer(varargin)
      % options are:
      %   mnemonic
      %   cfg_base 
      self = self@icosfit_optimizer( ...
        'mnemonic','opt','criteria','Baseline');
      self.bopt.n_coeffs = [];
      self.n_etalons = 0;
      self.n_rescale = 0;
      self.etalon_periods = [];
      self.etalon_maxf = 0;
      for i=1:2:length(varargin)-1
        if isfield(self.opt, varargin{i})
          self.opt.(varargin{i}) = varargin{i+1};
        elseif isfield(self.bopt, varargin{i})
          self.bopt.(varargin{i}) = varargin{i+1};
        else
          error('Unrecognized option: %s', varargin{i});
        end
      end
      self.get_scanregion;
    end
    
    function new_polynomial(self, n_pcoeffs)
      % IO.new_polynomial(n_pcoeffs);
      % Create a new baseline file using the specified number of
      % polynomial coefficients.
      self.bopt.n_coeffs = n_pcoeffs;
      name = sprintf('%dp', n_pcoeffs);
      writeetlnbase(name, n_pcoeffs, [], [], [], self.ScanNumRange(1));
      % create new config file, run the fit and add to the survey
      self.iterate(name, 'BaselineFile', [ 'sbase.' name '.ptb' ]);
    end
    
    function period_out = analyze_etalons(self, maxf, oname)
      % BO.analyze_etalons([oname[, maxf]])
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
        [], self.etalon_periods, maxf);
      if nargout > 0
        period_out = period;
      end
    end
    
    function add_etalon(self, maxf)
      % BO.add_etalon([maxf])
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
      self.iterate(newname, 'BaselineFile', [ 'sbase.' newname '.ptb' ]);
    end
    
    function rescale_baseline(BO)
      % BO.rescale_baseline()
      %
      % Analyzes the scaling of baseline parameters and
      % creates an new appropriately scaled baseline file.
      name = BO.survey(end).text;
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
      baseline_rescale(BO.survey(end).base, newname);
      BO.iterate(newname, 'BaselineFile', [ 'sbase.' newname '.ptb' ]);
    end
    
    function savefile(BO)
      % BO.savefile
      % Writes the BO object to a .mat file with the name derived
      % from the mnemonic in BO.opt.mnemonic. The filename is prefixed
      % with 'BO_'.
      save_IR = BO.IR;
      BO.IR = [];
      fname = sprintf('BO_%s.mat', BO.opt.mnemonic);
      save(fname, 'BO');
      fprintf(1, 'baseline_optimizer saved to %s\n', fname);
      BO.IR = save_IR;
    end

  end
end