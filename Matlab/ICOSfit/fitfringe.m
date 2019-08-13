function [ fringex, fry ] = fitfringe( y, n, verbose, x_offset )
% fringex = fitfringe( et, n, verbose, x_offset );
% Returns the index of fringe peaks in et.
% n is the number of points on each side of the peak to
% use in the fit.
% verbose defaults to 0
% x_offset is only relevant when verbosity is turned on.

% Not just a simple peak detector, fitfringe fits parabolas
% to the data, and selects the points that yield the largest
% amplitude. It then double-checks the result for a reasonable
% progression of samples/fringe and will eliminate fringes at
% the beginning or end if they are the only outliers. Other
% dsfr problems produce a warning and might invoke additional
% graphics if verbose >= 0.
%
% The silent elimination of early fringes could result in very
% poor fitting in some regimes--That's something worth checking.
%
% The idea here is at each sample i to fit the points y(i+(-n:n)) to
% b2 * x^2 + b1 * x + b0
% a2 is a measure of where the peak is
extendit=0;
N = size(y,1);
Nc = 2*n+1;
if nargin < 4
  x_offset = 1;
  if nargin < 3
    verbose = 0;
  end
end
Na = N - Nc + 1;
Y = zeros(Na, Nc);
for i = 1:Nc
  Y(:,i) = y(i:Na-1+i);
end
col = ones(Na,1);
x = -n:n; x2 = x.*x; x4 = x2.*x2; sx2 = sum(x2); sx4 = sum(x4);
b2 = (Nc * sum(Y.*(col*x2),2) - sum(Y,2)*sx2)/(Nc*sx4-sx2*sx2);
b1 = sum(Y.*(col*x),2)/sx2;
b0 = sum(Y,2)/Nc - b2*sx2/Nc;
chi2 = sum((Y-(b2*x2 + b1*x + b0*ones(1,Nc))).^2,2);
a2 = -b1./(2*b2 + (abs(b2)<1e-6));
xx = (1:Na)'+n;

det = diff(b2);
deta = [ -1; det ];
detb = [ det; 1 ];
v = deta < 0 & detb >= 0 & b2 < 0 & (a2 >= -n & a2 <= n) & xx+a2 >= n;
if isempty(v)
  fringex = [];
  fry = [];
  return
end
fringex = xx(v) + a2(v);
fringey = b2(v).*a2(v).*a2(v) + b1(v).*a2(v) + b0(v);
% dfx is a normalized diff extended by one to match the length of
% fringex. It is normalized to the mean diff, which is just the average
% of the first and last points by collapsing summation.
dfx = length(fringex)*diff(fringex)/(fringex(length(fringex))-fringex(1));
dfx = [ dfx(1); dfx ];
fatalerror = 0;
if any(dfx > 1.5)
  if verbose >= 0
    disp('Totally missed a fringe or something.\n');
    if verbose == 0
      verbose = 1;
    end
  end
end
dfxok = dfx > .35;
if ~all(dfxok)
  fringex = fringex(dfxok);
  fringey = fringey(dfxok);
  notok = find(~dfxok);
  if verbose >= 0
    fprintf(1,'Eliminating %d extraneous fringes:\n', length(notok));
    for i=1:length(notok)
      fprintf(1,'  %d: dfx = %.3f\n', notok(i), dfx(notok(i)));
    end
  end
end

ddx = 1:length(fringex)-2;
dsfr = (fringex(ddx+2)-fringex(ddx+1))./(fringex(ddx+1)-fringex(ddx));
vdsfr = dsfr>1.26|dsfr<.9;
if any(vdsfr)
  dv = diff(vdsfr);
  if length(find(dv<0)) + length(find(dv>0)) <= 1
    dsfrok = find(~vdsfr);
    fringex = fringex(dsfrok);
    fringey = fringey(dsfrok);
    ddxok = dsfrok(dsfrok <= length(ddx));
    ddx = 1:length(ddxok);
    dsfr = dsfr(ddxok);
    if verbose >= 0
      fprintf(1,'DSFR out of range at start or end\n');
    end
  else
    if verbose >= 0
      fprintf(1,'DSFR out of range: %f - %f\n', min(dsfr), ...
        max(dsfr));
      if verbose == 0
        verbose = 1;
      end
    end
  end
end

% Now extend frx, fry beyond the x range
if extendit
  while fringex(1) > 1
    dx = fringex(2)-fringex(1);
    dy = fringey(2)-fringey(1);
    fringex = [ fringex(1)-dx; fringex ];
    fringey = [ fringey(1)-dy; fringey ];
  end
  while max(fringex) < max(xx)
    nfringe = length(fringex);
    dx = fringex(nfringe) - fringex(nfringe-1);
    dy = fringey(nfringe) - fringey(nfringe-1);
    fringex = [ fringex; fringex(nfringe)+dx ];
    fringey = [ fringey; fringey(nfringe)+dy ];
  end
end
if nargout > 1
  fry = fringey;
end

if length(fringex) < 2
  fatalerror = 1;
  warning('fitfringe:NoFringesFound','No fringes found');
end
frno = 1:length(fringex)-1;

if verbose > 0
  figure;
  ax = [ nsubplot(2,1,1,1), nsubplot(2,1,2,1)];
  plot(ax(1),fringex(frno)+x_offset-1,diff(fringex),'+-');
  ylabel(ax(1),'Samples/Fr');
  set(ax(1),'XTickLabel',[]);
  grid(ax(1));
  % ch = gca;
  plot(ax(2),fringex(ddx)+x_offset-1,dsfr,'+');
  ylabel(ax(2),'DSFR');
  set(ax(2),'YAxisLocation','Right');
  addzoom;
  linkaxes(ax,'x');
  %return;
  
  figure;
  ax = [nsubplot(4,1,1,1),nsubplot(4,1,2,1),nsubplot(4,1,3,1),nsubplot(4,1,4,1)];
  h = [];
  plot(ax(1),xx+x_offset-1,b2,xx(v)+x_offset-1,b2(v),'r+');
  ylabel(ax(1),'b2');
  set(ax(1),'XTickLabel',[]);
  zoom on;
  grid(ax(1),'on');
  % ch = [ch gca];
  
  h = [ h; plot(ax(2),xx+x_offset-1, Y(:,n)) ];
  ylabel(ax(2),'Raw');
  set(ax(2),'XTickLabel',[],'YAxisLocation','Right');
  % zoom yon;
  grid(ax(2),'on');
  % ch = [ch gca];
  
  h = [ h; plot(ax(3),xx+x_offset-1,a2)];
  ylabel(ax(3),'a1');
  set(ax(3),'XTickLabel',[]);
  % zoom yon;
  grid(ax(3),'on');
  % ch = [ch gca];
  
  h = [ h; plot(ax(4),xx+x_offset-1,chi2); ];
  ylabel(ax(4),'Chi^2');
  set(ax(4),'YAxisLocation','Right');
  grid(ax(4),'on');
  % ch = [ch gca];
  
  set(h,'Marker','+');
  linkaxes(ax,'x');
  shg;
end

if fatalerror > 0
  error('Fatal Error');
end
