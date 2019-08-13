function  [osc_out, beta_out, S_out, sigosc_out, sigbeta_out] = feedback_analysis(varargin)
% [osc_out, beta_out, S_out, sigosc_out, sigbeta_out] = ...
%    feedback_analysis([scans,] base [, base ...]);
% 
% feedback_analysis takes one to three arguments:
%   An optional list of scan numbers to use in the analysis
%   An optional reference base name of an icosfit for comparison
%   The base name of an icosfit run to fully analyze.
scans = [];
bi = 1;
noplot = 0;
if ~isempty(varargin) && isnumeric(varargin{1})
  scans = varargin{1};
  bi = 2;
end
if length(varargin) >= bi && strcmpi(varargin{bi},'noplot')
  bi = bi + 1;
  noplot = 1;
end
if bi > length(varargin)
  help feedback_analysis
  return;
end
bases = varargin(bi:end);
[line_pos0,S0] = get_line_position(bases{1});
if nargout > 2
  S_out = cell(length(bases),1);
  S_out{1} = S0;
end
osc = zeros(length(bases),size(S0.Chi,2));
beta = osc;
sigosc = osc;
sigbeta = osc;
[osc(1,:), beta(1,:), sigosc(1,:), sigbeta(1,:)] = ...
  fit_comp([],S0, line_pos0, scans, noplot);
for i = 2:length(bases)
  [line_pos,S] = get_line_position(bases{i});
  [ osc(i,:), beta(i,:), sigosc(i,:), sigbeta(i,:) ] = ...
    fit_comp(S0, S, line_pos, scans, noplot);
  if nargout > 2
    S_out{i} = S;
    if nargout > 3
      sigosc_out = sigosc;
      if nargout > 4
        sigbeta_out = sigbeta;
      end
    end
  end
end

if noplot == 0
  f = figure;
  lnums = 1:size(osc,2);
  % plot(lnums,osc','s-');
  errorbar(lnums, osc', 2*sigosc');
  legend(bases);
  set(gca,'YGrid','On','XDir','Reverse','xlim',[0.75 lnums(end)+0.25]);
  title(sprintf('%s: Residual Oscillation by Line',getrun));
  set(f,'Name',sprintf('%s Summary',getrun));
  
  f = figure;
  % plot(lnums, beta', 's-');
  errorbar(lnums, beta', 2*sigbeta');
  legend(bases);
  set(gca,'YGrid','On','XDir','Reverse','xlim',[0.75 lnums(end)+0.25]);
  title(sprintf('%s: Phase of oscilation',getrun));
  set(f,'Name',sprintf('%s Phase',getrun));
  
  % f = figure;
  % plot(osc', beta','.-');
  % xlabel('Amplitude');
  % ylabel('Phase');
  % title(sprintf('%s: Phase plot',getrun));
  % set(f,'Name',sprintf('%s: Phase plot',getrun));
  
  % f = figure;
  % plot(S0.nu, beta');
  % title(sprintf('%s: Phase vs Wavenumber', getrun));
  % xlabel('cm^{-1}');
  % ylabel('Phase deg');
  % set(f, 'Name', sprintf('%s: Phase vs cm-1', getrun));


f = figure;
% polar(deg2rad(beta'), osc','.-');
maxosc = max(max(osc+2*sigosc));
polar(0, maxosc, 'w');
hold on;
colors = 'bgkr';
for i=1:size(osc,1)
  bc = colors(mod(i-1,length(colors))+1);
  for j=1:size(osc,2)
    % draw individual point
    polar(deg2rad(beta(i,j)), osc(i,j), ['.' bc]);
    % Label point with line number
    xc = cos(deg2rad(beta(i,j))) * osc(i,j);
    yc = sin(deg2rad(beta(i,j))) * osc(i,j);
    text(xc,yc,sprintf(' %d',j));
    % Draw uncertainty box
    th = beta(i,j) + 2*[-1:.1:1 1:-.1:-1 -1]*sigbeta(i,j);
    rho = osc(i,j) + 2*[-1*ones(1,21) ones(1,21) -1]*sigosc(i,j);
    polar(deg2rad(th), rho, bc);
  end
end
hold off;
title(sprintf('%s: %d-%d: Phase Plot',getrun, min(scans), max(scans)));
set(f,'Name',sprintf('%s: Phase Plot',getrun));
drawnow;
end
if nargout > 0
  osc_out = osc;
  if nargout > 1
    beta_out = beta;
    if nargout > 3
      sigosc_out = sigosc;
      if nargout > 4
        sigbeta_out = sigbeta;
      end
    end
  end
end


%--------------------------------------------------------
function [osc_out, beta_out, sigosc_out, sigbeta_out] = ...
  fit_comp(S0, S, line_pos, scans, noplot)
if nargin < 4 || isempty(scans)
  scans = S.scannum;
end
if nargin < 5
  noplot = 0;
end
use_stat = 1;
[scans,vs] = scan_intersect(scans, S.scannum);
PTE = load(S.PTEfile);
[Pscans,vp] = scan_intersect(scans, PTE(:,1));
if length(Pscans) ~= length(scans)
  error('Scans present in S are not present in PTE file');
end
PTE = PTE(vp,:);
scan10 = fastavg(scans,10);
if ~isempty(S0)
  [scans0,vs0] = scan_intersect(scans, S0.scannum);
  scan010 = fastavg(scans0,10);
end

x = (PTE(1,4):max(S.SignalRegion(:,2)))';
X = (x' - PTE(1,4))/1000;
row = ones(1,length(x));
a = PTE(:,7);
b = PTE(:,6);
c = PTE(:,5);
d = PTE(:,8);
tau = PTE(:,9);
d2 = PTE(:,10);
tau2 = PTE(:,11);
fn = a*(X.^2) + b*X + c*row + (d*row).*exp(-(1./tau)*X) + ...
    (d2*row).*exp(-(1./tau2)*X);
[XX,YY] = meshgrid(x,scans);

osc = zeros(1,size(S.Chi,2));
beta_out = osc;
sigosc_out = osc;
sigbeta_out= osc;
for loi=1:size(S.Chi,2)
  if noplot == 0
    f = figure;
    set(f,'Name',sprintf('%s: Line %d',S.base,loi));
    p = get(f,'Position');
    new_h = 500;
    new_w = 1500;
    p = [ p(1)-(new_w-p(3))/2 p(2)-(new_h-p(4)) new_w new_h];
    set(f,'Position',p)
    xsp = .08;
    if isempty(S0)
      ax = nsubplot(1,3,1,1,xsp);
      plot(ax(1),scan10, fastavg(S.Chi(vs,loi),10),'.');
      title(ax(1), sprintf('%s: Line %d', getrun, loi));
      ylabel(ax(1),S.base);
      xlabel(ax(1),'Scan Number');
    else
      ax = [ nsubplot(2,3,1,1,xsp) nsubplot(2,3,2,1,xsp) ];
      plot(ax(1),scan010, fastavg(S0.Chi(vs0,loi),10),'.');
      title(ax(1), sprintf('%s: Line %d', getrun, loi));
      ylabel(ax(1),sprintf('Ref: %s',S0.base));
      set(ax(1),'XTickLabel',[]);
      plot(ax(2),scan10, fastavg(S.Chi(vs,loi),10),'.');
      ylabel(ax(2),sprintf('%s',S.base));
      xlabel(ax(2),'Scan Number');
      set(ax(2),'YAxisLocation','Right');
      linkaxes(ax,'x');
    end
  end

  Chimean = mean(S.Chi(vs,loi));
  Chires = (S.Chi(vs,loi)-Chimean)./Chimean;
  % Gedmean = mean(S.Ged(vs,loi));
  % Gedrat = S.Ged./S.Gedcalc;
  % Gedres = Gedrat(vs,loi);
  fn3 = interp2(XX,YY,fn,line_pos(vs,loi),scans);
  
  Navg = 10;
  fn310 = fastavg(fn3,Navg);
  ffn3 = fn310 - floor(fn310);
  Chires10 = fastavg(Chires,Navg);

  if noplot == 0
    ax = [ nsubplot(2,3,1,2,xsp) nsubplot(2,3,2,2,xsp) ];
    plot(ax(1),scan10,Chires10,'.');
    title(ax(1),sprintf('%s: Line %d', getrun, loi));
    set(ax(1),'XTickLabel',[]);
    ylabel(ax(1),'Mixing Ratio RDFM');
    plot(ax(2),scan10,ffn3,'.');
    set(ax(2),'YAxisLocation','Right');
    xlabel(ax(2),'Scan Number');
    ylabel(ax(2),'Fractional Fringe');
    set(ax(2),'YAxisLocation','Right');
    linkaxes(ax,'x');
  end
  
  % This is a fit to a V
  % xffn = [0, 0.5, 1];
  % vxffn = 0.5*[1, -1, 1];
  % vffn = interp1(xffn,vxffn,ffn3);
  % Vffn = polyfit(vffn,Chires10,1);
  % vffnfit = polyval(Vffn,vxffn);
  % osc(loi) = Vffn(1);
 
  % This is a fit to an arbitrary sine wave
  SM = [1+0*ffn3, sin(2*pi*ffn3), cos(2*pi*ffn3)];

  if use_stat
    [sa,saint,r,rint,stats] = regress(Chires10,SM,1-0.6827);
    sigsa = saint(:,2)-sa;
    sigsa2 = sqrt((sa(2)^2)*(sigsa(2)^2) + (sa(3)^2)*(sigsa(3)^2));
    osc(loi) = sqrt(sa(2)^2 + sa(3)^2);
    sigosc_out(loi) = sigsa2/osc(loi);
    sigbeta_out(loi) = (sigsa2/(osc(loi)^2)) * 180/pi;
  else
    sa = SM\Chires10;
    osc(loi) = sqrt(sa(2)^2 + sa(3)^2);
  end
  beta = 90 - (atan2(sa(3),sa(2)) * 180 / pi);
  if beta < 0
    beta = beta + 360;
  end
  beta_out(loi) = beta;

  xffn = (0:.01:1)';
  vffnfit = sa(1) + sa(2)*sin(2*pi*xffn) + sa(3)*cos(2*pi*xffn);
  
  if noplot == 0
    ax = nsubplot(2,3,[2 2],3,xsp);
    %scatter(ffn3,Chires10,[],scan10);
    plot(ax,ffn3*360,Chires10,'.',xffn*360,vffnfit,'r');
    % hold on;
    % errorbarxy(ax, beta, osc(loi)+sa(1), sigbeta_out(loi), sigosc_out(loi));
    xlim([0 360]);
    title(ax,sprintf('%s: Line %d, \\beta = %.0f^o', getrun, loi, beta));
    xlabel(ax,'Etalon Fractional fringe position at line center');
    ylabel(ax,'Mixing Ratio RDFM');
    drawnow;
  end
end

osc_out = osc;

function [scans1_out, vs] = scan_intersect(scans1, scans2)
if isrow(scans1)
  scans1 = scans1';
end
vi = interp1(scans1,1:length(scans1),scans2,'nearest','extrap');
vs = scans2 == scans1(vi);
scans1_out = scans1(vi(vs));
