classdef epsilon2_optimizer < icosfit_optimizer
  % Leverage icosfit_optimizer tools to survey performance for
  % a range of epsilon2 values.
  properties
    eopt
  end
  methods
    function eps2 = epsilon2_optimizer(varargin)
      eps2 = eps2@icosfit_optimizer( ...
        'mnemonic','eps2','criteria','epsilon2','xscale','log', ...
        'save_var','OptE');
      eps2.eopt.eps2_vals = [];
      for i=1:2:length(varargin)-1
        if isfield(eps2.opt, varargin{i})
          eps2.opt.(varargin{i}) = varargin{i+1};
        elseif isfield(eps2.eopt, varargin{i})
          eps2.eopt.(varargin{i}) = varargin{i+1};
        else
          error('Unrecognized option: %s', varargin{i});
        end
      end
      if ~isempty(eps2.eopt.eps2_vals)
        eps2.add_values(eps2.eopt.eps2_vals);
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
