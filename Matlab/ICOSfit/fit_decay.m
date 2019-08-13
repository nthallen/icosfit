function [tau,amp,zero,fit] = fit_decay(data, offset)
  % [tau,amp,zero] = fit_decay(data, offset);
  % [tau,amp,zero,fit] = fit_decay(data, offset);
  % data = amp*exp(-i/tau)+zero;
  % tau is in sample periods.
  % offset defaults to 4
  if nargin < 2
    offset = 4;
  end
  V = fitlin(data, offset);
  b = V(2);
  a = V(5);
  tau = offset/log(b);
  zero = a/(1-b);
  x = cumsum(ones(size(data)));
  trialy = exp(-(x-1)/tau);
  amp = sum((data(x)-zero).*trialy)./sum(trialy.*trialy);
  if nargout > 3
    fit = zero+amp*trialy;
  end

