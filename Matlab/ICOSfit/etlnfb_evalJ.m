function [ emdl, J] = etlnfb_evalJ(Y,x)
% [ emdl, J ] = etlnfb_evalJ(Y,x);
% Models the etalon airy function for a given sample.
% Y is the parameter vector which can be 10, 11, 12 or 13 elements long
%   It consists of:
%     3 polynomial coefficients (x^0, x^1, x^2: reverse of polyfit/val)
%     2 exponential coefficents (amplitude and time constant)
%     Optional 2 more exponential coefficients
%     Feedback coefficient
%     4 cubic coefficients for power curve
%     Optional  1 finesse coefficent
%   Since the size of the optional elements are all unique, it is
%   possible to determine which are present just by the length of
%   the parameter vector. This is handy because passing additional
%   parameters to this function would be inconvenient.
%
%   If the finesse coefficient is omitted, the output is fringe number.
%   Otherwise the output is intensity. Hence:
%     10 => fringe number, single exponential
%     11 => power, single exponential
%     12 => fringe number, double exponential
%     13 => power, double exponential
% x is the sample number vector scaled as (1:Nsample)/1000
%   Hence if the actual samples run X=400:1800, x should be
%   (X-min(X)+1)/1000 which would be (1:1401)/1000;
if ~isrow(Y)
  error('Expected row vector for Y');
end
x2 = x.*x;
x3 = x2.*x;
JP = [x3 x2 x ones(size(x))];
if length(Y) == 10 % fringe number, single exp, feedback, power
  P = JP * Y(7:10)';
  if nargout > 1
    [ f, Jf ] = etln_evalJ( Y(1:5),x);
  else
    f = etln_evalJ( Y(1:5),x );
  end
  cse1 = 2*pi*f;
  cse2 = sin(cse1);
  emdl = f - Y(6)*P.*cse2;
  % plot(x,emdl); shg; pause;
  if nargout > 1
    J = [
      (1-2*pi*Y(6)*P.*cos(cse1))*ones(1,5) .* Jf, ...
      -P .* cse2, ...
      -Y(6)*cse2*ones(1,4) .* JP ];
  end
elseif length(Y) == 12 % fringe number, double exp, feedback, power
  P = JP * Y(9:12)';
  if nargout > 1
    [ f, Jf ] = etln_evalJ( Y(1:7),x);
  else
    f = etln_evalJ( Y(1:7),x );
  end
  cse1 = 2*pi*f;
  cse2 = sin(cse1);
  emdl = f - Y(8)*P.*cse2;
  % plot(x,emdl); shg; pause;
  if nargout > 1
    J = [
      (1-2*pi*Y(8)*P.*cos(cse1))*ones(1,7) .* Jf, ...
      -P .* cse2, ...
      -Y(8)*cse2*ones(1,4) .* JP ];
  end
elseif length(Y) == 11 % power, single exp, feedback, power, finess
  P = JP * Y(7:10)';
  if nargout > 1
    [ f, Jf ] = etlnfb_evalJ( Y(1:10),x);
  else
    f = etlnfb_evalJ( Y(1:10),x );
  end
  cse1 = pi*f;
  cse2 = sin(cse1);
  cse3 = cse2.*cse2;
  D = 1 + Y(11)*cse3;
  emdl = P./D;
  if nargout > 1
    J = [
      -((2*pi*emdl*Y(11).*cse2.*cos(cse1))*ones(1,10)) .* Jf, ...
      -emdl .* cse3 ];
    J(:,7:10) = J(:,7:10) + JP;
    J = J./(D*ones(1,11));
  end
elseif length(Y) == 13 % power, double exp, feedback, power, finess
  P = JP * Y(9:12)';
  if nargout > 1
    [ f, Jf ] = etlnfb_evalJ( Y(1:12),x);
  else
    f = etlnfb_evalJ( Y(1:12),x );
  end
  cse1 = pi*f;
  cse2 = sin(cse1);
  cse3 = cse2.*cse2;
  D = 1 + Y(13)*cse3;
  emdl = P./D;
  if nargout > 1
    J = [
      -((2*pi*emdl*Y(13).*cse2.*cos(cse1))*ones(1,12)) .* Jf, ...
      -emdl .* cse3 ];
    J(:,9:12) = J(:,9:12) + JP;
    J = J./(D*ones(1,13));
  end
else
    error('Invalid number of parameters in Y: %d', length(Y));
end
