function V = fitlin( v, n )
% V = fitlin( v , n );
%  v  exponential decay plus offset
%  n  number of samples to offset for the fit (defaults to 1)
% V = [ bminus b bplus s2 a ];
%         b = V(2);
%         a = V(5);
%         tau = n*dt/log(b);
%         z = a/(1-b);

if size(v,2) ~= 1
  error('Input vector v must be a column vector');
end
npts = length(v);

if npts < 1+n
  error('Input vector not long enough');
end
y = v(1:(npts-n));
x = v((1+n):npts);
V = linfit(x,y);


function V = linfit( X, Y )
% V = linfit( x, y );
% Returns the 1x5 vector V with b- b b+ s2 a from the
% least-squares line through the points specified by vectors
% x and y assuming that x and y both have error that is equal
mX = mean(X);
mY = mean(Y);
x = X - mX;
y = Y - mY;

sxy = sum(x.*y);
sx2 = sum(x.*x);
sy2 = sum(y.*y);
N = length(x);

% Determine slope by minimizing chi-squared
X2a = sxy;
X2b = sx2-sy2;
X2c = -sxy;
detsign = sign(X2a);
determ = sqrt(X2b*X2b - 4 *X2a*X2c);
b = (-X2b + detsign*determ)/(2*X2a);
a = mY - b*mX;
% Define variance of x,y by assuming reduced chi-squared
% is equal to 1. This implies that chi-square(min) is N-2
s2 = (sy2 - 2*b*sxy + b*b*sx2)/((N-2)*(1+b^2));

% Now determine confidence interval by solving
% for Chi-squared == chi-square(min)+1 == N-1
aa = sx2 - s2*(N-1);
bb = -2*sxy;
cc = sy2 - s2*(N-1);
dd = sqrt(bb.*bb - 4*aa*cc);
bpos = (-bb + dd)/(2*aa);
bneg = ( -bb - dd ) / (2*aa);
V = [ bneg b bpos s2 a ];
%if ( any(imag(V)) )
  % trychi2( x, y, [-1000:100:10000], [-10:1:50] );
  %disp('Imaginary output');
%end

% refer to linfit2 for debugging plots
