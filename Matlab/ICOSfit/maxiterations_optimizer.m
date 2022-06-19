classdef maxiterations_optimizer < icosfit_optimizer
  % Leverage icosfit_optimizer tools to survey performance for
  % a range of MaxIterations values.
  properties
  end
  methods
    function maxi = maxiterations_optimizer(varargin)
      eopt.maxi_vals = [];
      maxi = maxi@icosfit_optimizer( ...
        'mnemonic','maxi','criteria','MaxIterations','xscale','linear', ...
        'save_var','OptMI','sopt',eopt, ...
        varargin{:});
      if ~isempty(maxi.opt.sopt.maxi_vals)
        maxi.add_values(maxi.opt.sopt.maxi_vals);
      end
    end
    
    function add_values(maxi, values)
      for i = 1:length(values)
        text = sprintf('%d',values(i));
        maxi.iterate(text, values(i), 'MaxIterations', text, []);
      end
    end
    
  end
end
