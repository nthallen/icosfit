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
%%
run = getrun;
S = ICOS_setup(base);
if isempty(line_nos)
  line_nos = 1:S.n_lines;
end
line_leg = num2str(line_nos');

vf = S.v(line_nos) + S.n_base_params+S.n_abs_params+S.n_lines*(S.n_line_params+S.n_abs_line_params);
vflp = find(any(S.fitdata(:,vf-S.n_abs_line_params)));
if ~isempty(vflp)
  figure; plot(S.scannum, S.fitdata(:,S.v(vflp)-S.n_abs_line_params) );
  legend(num2str(line_nos(vflp)'));
  title(['Line Deviations: ' run ]);
  xlabel('Scan Number');
  ylabel('cm^{-1}');
end
%%
figure; plot( S.scannum, S.fitdata(:,S.v(line_nos)+2));
title(['Number Densities: ' run ]);
xlabel('Scan Number');
ylabel('mol/cm^3');
legend(cellstr(line_leg));

figure; plot( S.scannum, S.chi2 );
title(['Reduced \chi^2: ' run ]);
xlabel('Scan Number');
ylabel('Reduced \chi^2');

figure;
if isfield(S,'dFN')
    subplot(2,1,1);
    plot( S.scannum, S.nu_F0 );
    title(['\nu_{F_0}' run ]);
    ylabel('cm^{-1}');
    xlabel('Scan Number');
    subplot(2,1,2);
    plot( S.scannum, S.dFN );
    title( 'dFN' );
    ylabel('Fringes');
    xlabel('Scan Number');
else
    plot( S.scannum, S.nu_F0 );
    title(['\nu_{F_0}' run ]);
    ylabel('cm^{-1}');
    xlabel('Scan Number');
end
%%
  figure;
  nsubplot( 2, 1, 1, 1 );
  plot(S.scannum, S.Ged(:,line_nos));
  title(['Fit Line Widths: ' run]);
  ylabel('Doppler Width cm^{-1}');
  set(gca,'YAxisLocation','right');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  grid;

  nsubplot( 2, 1, 2, 1 );
  plot( S.scannum, S.Gl(:,line_nos) );
  ylabel('Lorentz Width cm^{-1}');
  % set(gca,'XTickLabel',[]);
  xlabel('Scan Number');
  legend(cellstr(line_leg));
  grid;

  figure;
  nsubplot( 2, 1, 1, 1 );
  plot(S.scannum, S.Gedcalc(:,line_nos));
  title(['Calculated Line Widths: ' run]);
  ylabel('\gamma_{ED,calc} cm^{-1}');
  set(gca,'YAxisLocation','right');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  grid;

  nsubplot( 2, 1, 2, 1 );
  plot( S.scannum, S.Glcalc(:,line_nos) );
  ylabel('\gamma_{L,calc} cm^{-1}');
  % set(gca,'XTickLabel',[]);
  xlabel('Scan Number');
  legend(cellstr(line_leg));
  grid;

  figure;
  nsubplot( 2, 1, 1, 1 );
  plot(S.scannum, S.Ged(:,line_nos)./S.Gedcalc(:,line_nos));
  title([ 'Ratios of fit/calculated line widths: ' run ]);
  ylabel('\gamma_{ED}(fit)/\gamma_{ED}(calc)');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  grid;
  % legend( nu_text,  -1 );

  nsubplot( 2, 1, 2, 1 );
  plot(S.scannum, S.Gl(:,line_nos)./S.Glcalc(:,line_nos));
  ylabel('\gamma_l(fit)/\gamma_l(calc)');
  set(gca,'YAxisLocation','right');
  xlabel('Scan Number');
  legend(cellstr(line_leg));
  grid;
  % legend( nu_text,  -1 );
  
  vA = S.Gl./S.Ged;
  figure;
  nsubplot( 3, 1, 1, 1 );
  plot(S.scannum, vA(:,line_nos)); grid;
  title([ 'Voigt Parameter Fit, Calc and Ratio: ' run ] );
  ylabel('\gamma_l/\gamma_{ED}');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  % legend( nu_text,  -1 );

  vAcalc = S.Glcalc./S.Gedcalc;
  nsubplot( 3, 1, 2, 1 );
  plot(S.scannum, vAcalc(:,line_nos)); grid;
  %title(['Calculated Voigt Parameter' run]);
  ylabel('\gamma_l(calc)/\gamma_{ED}(calc)');
  set(gca,'YAxisLocation','right');
  set(gca,'XTickLabel',[]);
  legend(cellstr(line_leg));
  % legend( nu_text,  -1 );

  Gvratio = S.Gv./S.Gvcalc;
  nsubplot( 3, 1, 3, 1 );
  plot(S.scannum, Gvratio(:,line_nos)); grid;
  ylabel('\gamma_V(fit)/\gamma_V(calc)');
  legend(cellstr(line_leg));
  % title(['Ratio of Voigt Linewidths ' run ]);
  % legend( nu_text, -1);

  lst = S.Scorr.*S.CavLen.*S.Nfit./(S.Ged*sqrt(pi));
  lst(lst<=0) = NaN;
  figure;
  semilogy(S.scannum,lst(:,line_nos))
  title(['Line Strength ' run])
  xlabel('Scan Number');
  ylabel('Line Strength');
  legend(cellstr(line_leg));
  
  if 0
    Glas = log(2)*(S.Ged.*S.Ged - S.Gedcalc.*S.Gedcalc);
    Glas(Glas<0) = NaN;
    Glas = sqrt(Glas);
    figure;
    plot(S.scannum,Glas,'.'); grid;
    title(['Perceived Laser Linewidth: ' run]);
    ylabel('\gamma_{laser} cm^{-1}');
    xlabel('Scan Number');
  end
