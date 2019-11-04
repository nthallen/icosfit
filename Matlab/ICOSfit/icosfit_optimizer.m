classdef icosfit_optimizer < handle
  properties
    survey % struct array of iterations
    n_etalons
    n_iterations
    basebase
    cfgbase
  end
  
  methods
    function self = icosfit_optimizer(varargin)
      self.n_etalons = 0;
      self.n_iterations = 0;
      self.basebase = 'ICOSout.opt.';
      self.cfgbase = 'icosfit.opt.';
      self.survey = [];
    end
    
    function new_polynomial(self, n_pcoeffs)
      % IO.new_polynomial(n_pcoeffs);
      % Create a new baseline file using the specified number of
      % polynomial coefficients.
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
    
    function eps2_analysis(self, varargin)
    end
    
    function iterate(self, varargin)
      % create new config file with given parameters
      % run the fit
      % add the fit to the survey
    end
  end
end
