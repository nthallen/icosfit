function diagnose( base, line_nos )
% diagnose([base]);
% diagnose(line_nos);
% diagnose( base, line_nos );
% base defaults to 'ICOSout'
if nargin == 1 && isnumeric(base)
  line_nos = base;
  base = [];
elseif nargin < 2
  line_nos = [];
end
by_molecule=0;
run = getrun;
lines = [];
ICOSsetup;
if isempty(line_nos)
  line_nos = [1:n_lines];
end
line_leg = num2str(line_nos');

vf = v(line_nos) + n_base_params+n_abs_params+n_lines*(n_line_params+n_abs_line_params);
vflp = find(any(fitdata(:,vf-n_abs_line_params)));
if ~isempty(vflp)
  figure; plot(scannum, fitdata(:,v(vflp)-n_abs_line_params) );
  legend(num2str(line_nos(vflp)'),-1);
  title(['Line Deviations: ' run ]);
  xlabel('Scan Number');
  ylabel('cm^{-1}');
end

figure; plot( scannum, fitdata(:,v(line_nos)+2));
title(['Number Densities: ' run ]);
xlabel('Scan Number');
ylabel('mol/cm^3');
legend(cellstr(line_leg));

figure; plot( scannum, chi2 );
title(['Reduced \chi^2: ' run ]);
xlabel('Scan Number');
ylabel('Reduced \chi^2');

figure;
if exist('dFN','var')
    subplot(2,1,1);
    plot( scannum, nu_F0 );
    title(['\nu_{F_0}' run ]);
    ylabel('cm^{-1}');
    xlabel('Scan Number');
    subplot(2,1,2);
    plot( scannum, dFN );
    title( 'dFN' );
    ylabel('Fringes');
    xlabel('Scan Number');
else
    plot( scannum, nu_F0 );
    title(['\nu_{F_0}' run ]);
    ylabel('cm^{-1}');
    xlabel('Scan Number');
end

  figure;
  nsubplot( 2, 1, 1, 1 );
  plot(scannum, Ged(:,line_nos));
  title(['Fit Line Widths: ' run]);
  ylabel('Doppler Width cm^{-1}');
  set(gca,'YAxisLocation','right');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  grid;

  nsubplot( 2, 1, 2, 1 );
  plot( scannum, Gl(:,line_nos) );
  ylabel('Lorentz Width cm^{-1}');
  % set(gca,'XTickLabel',[]);
  xlabel('Scan Number');
  legend(cellstr(line_leg));
  grid;

  figure;
  nsubplot( 2, 1, 1, 1 );
  plot(scannum, Gedcalc(:,line_nos));
  title(['Calculated Line Widths: ' run]);
  ylabel('\gamma_{ED,calc} cm^{-1}');
  set(gca,'YAxisLocation','right');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  grid;

  nsubplot( 2, 1, 2, 1 );
  plot( scannum, Glcalc(:,line_nos) );
  ylabel('\gamma_{L,calc} cm^{-1}');
  % set(gca,'XTickLabel',[]);
  xlabel('Scan Number');
  legend(cellstr(line_leg));
  grid;

  figure;
  nsubplot( 2, 1, 1, 1 );
  plot(scannum, Ged(:,line_nos)./Gedcalc(:,line_nos));
  title([ 'Ratios of fit/calculated line widths: ' run ]);
  ylabel('\gamma_{ED}(fit)/\gamma_{ED}(calc)');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  grid;
  % legend( nu_text,  -1 );

  nsubplot( 2, 1, 2, 1 );
  plot(scannum, Gl(:,line_nos)./Glcalc(:,line_nos));
  ylabel('\gamma_l(fit)/\gamma_l(calc)');
  set(gca,'YAxisLocation','right');
  xlabel('Scan Number');
  legend(cellstr(line_leg));
  grid;
  % legend( nu_text,  -1 );
  
  vA = Gl./Ged;
  figure;
  nsubplot( 3, 1, 1, 1 );
  plot(scannum, vA(:,line_nos)); grid;
  title([ 'Voigt Parameter Fit, Calc and Ratio: ' run ] );
  ylabel('\gamma_l/\gamma_{ED}');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  % legend( nu_text,  -1 );

  vAcalc = Glcalc./Gedcalc;
  nsubplot( 3, 1, 2, 1 );
  plot(scannum, vAcalc(:,line_nos)); grid;
  %title(['Calculated Voigt Parameter' run]);
  ylabel('\gamma_l(calc)/\gamma_{ED}(calc)');
  set(gca,'YAxisLocation','right');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  % legend( nu_text,  -1 );

  Gvratio = Gv./Gvcalc;
  nsubplot( 3, 1, 3, 1 );
  plot(scannum, Gvratio(:,line_nos)); grid;
  ylabel('\gamma_V(fit)/\gamma_V(calc)');
  legend(cellstr(line_leg));
  % title(['Ratio of Voigt Linewidths ' run ]);
  % legend( nu_text, -1);

  lst = Scorr.*CavLen.*Nfit./(Ged*sqrt(pi));
  lst(lst<=0) = NaN;
  figure;
  semilogy(scannum,lst(:,line_nos))
  xlabel('Scan Number');
  ylabel('Line Strength');
  legend(cellstr(line_leg));
  
  if 0
    Glas = log(2)*(Ged.*Ged - Gedcalc.*Gedcalc);
    Glas(Glas<0) = NaN;
    Glas = sqrt(Glas);
    figure;
    plot(scannum,Glas,'.'); grid;
    title(['Perceived Laser Linewidth: ' run]);
    ylabel('\gamma_{laser} cm^{-1}');
    xlabel('Scan Number');
  end
