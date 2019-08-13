function [ Chiout, xout, Pout, lines_out ] = mixlines( base, by_molecule );
% Chi = mixlines( [base [, by_molecule ] );
% [ Chi, scannum ] = mixlines( [base [, by_molecule ] );
% [ Chi, scannum, P ] = mixlines( ... );
% [ Chi, scannum, P, lines ] = mixlines( ... );
% base is the directory where the output files are located
% by_molecule:
%   0: Create a separate graph for each isotope
%   1: Plot all isotopes of a molecule on the same graph
%   2: Same as 0, but list x axis as time rather than Scan Number
%   3: Same as 1, but list x axis as time rather than Scan Number
%   4: Don't plot, just return the outputs.
% base defaults to 'ICOSout'
% base/ICOSsum.dat summary
% base/00/00/00.dat details
% The line definitions read from base/ICOSconfig.m
plotlines = 0;
if nargin < 2
  by_molecule = 1;
end
by_time = by_molecule >= 2;
by_molecule = by_molecule - by_time*2;

run = getrun;
lines=[];
n_lines = 0;
ICOSsetup;
if nargout > 0
  Chiout = Chi;
  if nargout > 1
    xout = scannum;
    if nargout > 2
      Pout = P(:,1);
      if nargout > 3
        lines_out = lines;
      end
    end
  end
end
if by_molecule >= 2
  return;
end
% T = T * row;
% P = P * row; % P in Torr
% Nfit = fitdata(:,v+2);
% C = 2.68675e19 * (P/760.) ./ (T / 273.15); % [M]
% C = C * row;
col = ones( size(fitdata,1), 1 );

if by_time
  x = time2d(scantime(scannum));
else
  x = scannum;
end

% v_mn is transition energy in cm-1 
% number 1.438 etc. comes from h*c/k, units are K*cm (should be)
% vmn = col * nu;
% Cfact = 1.438789;
% Boltzfact = exp(Cfact*(col*En).*(T-T0)./(T0*T));
% StimEmis = (1-exp(-Cfact*vmn./T))./(1-exp(-Cfact*vmn/T0));
% Qfact = (T0./T).^1.5;
% S = (col*S0) .* Qfact .* Boltzfact .* StimEmis; % correct line strength
% L = 70;
% Chi = ( Sfit .* Ged * sqrt(pi) ) ./ ( S .* C * L );

% isos is a vector of the unique isotopes
% visos is a boolean matrix. visos(i,:) is a boolean vector
%  identifying elements of iso that correspond to the unique
%  isotope at siso(i)
if by_molecule > 0
  grp_iso = floor(iso/10)*10;
else
  grp_iso = iso;
end
siso = sort(grp_iso');
isos = siso([ 1; find(diff(siso))+1 ]);
names = isovals( isos, 'name' );
abund = isovals( isos, 'abundance' );
visos = isos * ones(size(grp_iso)) == ones(size(isos))*grp_iso;
for i = 1:length(isos)
  figure;
  a1 = nsubplot( 4, 1, [3 3], 1 );
  plot(x, Chi(:,visos(i,:))*1e6*abund(i));
  title([ '[' char(names(i)) ']/[M] ppm ' run '/' base ]);
  ylabel(sprintf('[%s]/[M] ppm', char(names(i))));
  set(gca, 'XTickLabel', [] );
  grid;
  la = legend( nu_text(visos(i,:),:),'Location','EastOutside');
  lap = get(la, 'position');
  a1p = get(a1, 'position' );
  a1p(3) = lap(1) - a1p(1);
  set( a1, 'position', a1p );

  a2 = nsubplot( 4, 1, 4, 1 );
  a2p = get(a2,'position');
  a2p(3) = a1p(3);
  set(a2,'position', a2p);
  plot( x, P );
  ylabel('P Torr');
  set(gca,'YAxisLocation','right');
  grid;
  
  orient landscape;
  normalize;
  %if by_time
  %  tl = get(gca,'XTick');
  %  hr = floor(tl/12);
  %  min = floor(((tl/12)-hr) * 60 + .1);
  %  for j = 1:length(tl)
  %    tlbl(j) = { sprintf('%d:%02d',hr(j),min(j)) };
  %  end
  %  set( gca, 'XTickLabel', char(tlbl) );
  %end
  addzoom;
end
