classdef baseline_optimizer < icosfit_optimizer
  properties
    bopt % baseline options
    n_etalons
    n_rescale
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
    
    function etalon_analysis(self)
      % set survey(end).pmax
      if isempty(self.survey)
        fprintf(1,'No data to analyze\n');
        return;
      end
    end
    
    function add_etalon(self)
      if isempty(self.survey)
        fprintf(1,'No data to analyze\n');
        return;
      end
      if self.survey(end).pmax == 0
        self.etalon_analysis;
        if self.survey(end).pmax == 0
          fprintf(1,'Etalon analysis failed\n');
          return;
        end
      end
      % create new baseline with pmax
      % create new config file
      % run the fit
      % add the fit to the survey
    end
    
    function scale_analysis(self)
      % produces a figure showing scale stuff
    end
    
    function rescale_baseline(self)
      % create new baseline
      self.iterate();
      % create new config file
      % run the fit
      % add the fit to the survey
    end
    
    function savefile(BO)
      % BO.savefile
      % Writes the BO object to a .mat file with the name derived
      % from the mnemonic in BO.opt.mnemonic. The filename is prefixed
      % with 'BO_'.
      fname = sprintf('BO_%s.mat', BO.opt.mnemonic);
      save(fname, 'BO');
      fprintf(1, 'baseline_optimizer saved to %s\n', fname);
    end

  end
end