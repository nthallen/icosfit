function [ emdl, J] = etln_evalJ(Y,x)
% [ emdl, J ] = etln_evalJ(Y,x);
% Models the etalon airy function for a given sample.
% Y is the parameter vector which can be 5, 7, 10, or 12 elements long
%   It consists of:
%     3 polynomial coefficients (x^0, x^1, x^2: reverse of polyfit/val)
%     2 exponential coefficents (amplitude and time constant)
%     Optional 2 more exponential coefficients
%     Optional power curve group {
%       4 cubic coefficients for power curve
%       1 finesse coefficent
%     }
%   Since the size of the optional elements are all unique, it is
%   possible to determine which are present just by the length of
%   the parameter vector. This is handy because passing additional
%   parameters to this function would be inconvenient.
%
%   If the power curve group is omitted, the output is fringe number.
%   Otherwise the output is intensity.
% x is the sample number vector scaled as (1:Nsample)/1000
%   Hence if the actual samples run X=400:1800, x should be
%   (X-min(X)+1)/1000 which would be (1:1401)/1000;
x2 = x.*x;
if length(Y) == 5
  cse1 = exp(-x/Y(5));
  cse2 = Y(4)*cse1;
  emdl = Y(1)+Y(2)*x+Y(3)*x2+cse2;
  if nargout > 1
    J = zeros(length(x),length(Y));
    J(:,1) = 1;
    J(:,2) = x;
    J(:,3) = x2;
    J(:,4) = cse1;
    J(:,5) = cse2.*x/(Y(5)*Y(5));
  end
elseif length(Y) == 7
  cse1 = exp(-x/Y(5));
  cse2 = Y(4)*cse1;
  cse3 = exp(-x/Y(7));
  cse4 = Y(6)*cse3;
  emdl = Y(1)+Y(2)*x+Y(3)*x2+cse2+cse4;
  if nargout > 1
    J = zeros(length(x),length(Y));
    J(:,1) = 1;
    J(:,2) = x;
    J(:,3) = x2;
    J(:,4) = cse1;
    J(:,5) = cse2.*x/(Y(5)*Y(5));
    J(:,6) = cse3;
    J(:,7) = cse4.*x/(Y(7)*Y(7));
  end
elseif length(Y) == 10 % 5 for fringe number
  x3 = x2.*x;
  P = Y(6)*x3 + Y(7)*x2 + Y(8)*x + Y(9);
  if nargout > 1
    [ f, Jf ] = etln_evalJ( Y(1:5),x);
  else
    f = etln_evalJ( Y(1:5),x );
  end
  cse5 = pi*f;
  cse6 = sin(cse5);
  cse7 = cse6.*cse6;
  D = 1 + Y(10)*cse7;
  emdl = P./D;
  % plot(x,emdl); shg; pause;
  if nargout > 1
    J = zeros(length(x),length(Y));
    J(:,1:5) = - emdl*2*pi*Y(10).*cse6.*cos(cse5)*ones(1,5) .* Jf;
    J(:,6)  = x3;
    J(:,7)  = x2;
    J(:,8) = x;
    J(:,9) = 1;
    J(:,10) = - emdl.*cse7;
    J = J./(D*ones(1,10));
  end
elseif length(Y) == 12
  x3 = x2.*x;
  P = Y(8)*x3 + Y(9)*x2 + Y(10)*x + Y(11);
  if nargout > 1
    [ f, Jf ] = etln_evalJ( Y(1:7),x);
  else
    f = etln_evalJ( Y(1:7),x );
  end
  cse5 = pi*f;
  cse6 = sin(cse5);
  cse7 = cse6.*cse6;
  D = 1 + Y(12)*cse7;
  emdl = P./D;
  % plot(x,emdl); shg; pause;
  if nargout > 1
    J = zeros(length(x),length(Y));
    J(:,1:7) = - emdl*2*pi*Y(12).*cse6.*cos(cse5)*ones(1,7) .* Jf;
    J(:,8)  = x3;
    J(:,9)  = x2;
    J(:,10) = x;
    J(:,11) = 1;
    J(:,12) = - emdl.*cse7;
    J = J./(D*ones(1,12));
  end
else
    error('Invalid number of parameters in Y: %d', length(Y));
end
