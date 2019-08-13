function chi2 = logchi( V, x, y );
% chi2 = logchi( V, x, y );
% evaluates chi^2 for y = V(1)*exp(-x/V(2)) + V(3)
% To be called from fmins( 'logchi', V, [], [], x, y );
yfit = V(1)*exp(-x/V(2)) + V(3);
chi2 = sum( (yfit - y).^2 );
