classdef maxiterations_optimizer < icosfit_optimizer
  % Leverage icosfit_optimizer tools to survey performance for
  % a range of MaxIterations values.
  properties
    eopt
  end
  methods
    function maxi = maxiterations_optimizer(varargin)
      maxi = maxi@icosfit_optimizer( ...
        'mnemonic','maxi','criteria','MaxIterations','xscale','linear', ...
        'save_var','OptMI');
      maxi.eopt.maxi_vals = [];
      for i=1:2:length(varargin)-1
        if isfield(maxi.opt, varargin{i})
          maxi.opt.(varargin{i}) = varargin{i+1};
        elseif isfield(maxi.eopt, varargin{i})
          maxi.eopt.(varargin{i}) = varargin{i+1};
        else
          error('Unrecognized option: %s', varargin{i});
        end
      end
      if ~isempty(maxi.eopt.maxi_vals)
        maxi.add_values(maxi.eopt.maxi_vals);
      end
    end
    
    function add_values(maxi, values)
      for i = 1:length(values)
        text = sprintf('%d',values(i));
        maxi.iterate(text, values(i), 'MaxIterations', text);
      end
    end
    
  end
end
