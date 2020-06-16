classdef epsilon2_optimizer < icosfit_optimizer
  % Leverage icosfit_optimizer tools to survey performance for
  % a range of epsilon2 values.
  properties
  end
  methods
    function eps2 = epsilon2_optimizer(varargin)
      eopt.eps2_vals = [];
      eps2 = eps2@icosfit_optimizer( ...
        'mnemonic','eps2','criteria','epsilon2','xscale','log', ...
        'save_var','OptE','sopt',eopt, ...
        varargin{:});
      if ~isempty(eps2.opt.sopt.eps2_vals)
        eps2.add_values(eps2.opt.sopt.eps2_vals);
      end
    end
    
    function add_values(eps2, values)
      for i = 1:length(values)
        text = sprintf('%.0e',values(i));
        eps2.iterate(text, values(i), 'epsilon2', text);
      end
    end
    
  end
end
