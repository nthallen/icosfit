%%
% Parameter survey
% Given a config file template, run fits over a range of parameters,
% monitoring:
%  chi2 for each scan for each parameter value
%    chi2 vs scannum (line for each eps2)
%    chi2 vs eps2 (line for each scan)
%    chi2 mesh
%  iterations for each scan for each eps2 value
%    iterations vs scannum (line for each eps2)
%    iterations vs eps2 (line for each scan)
%  function evaluations for each scan for each eps2 value
%  time (might be nice to see this per scan)
%    times vs eps2
%  Will also want to look at fit concentrations for each line
%    N(i) vs scannum (line for each eps2)
%    N(i) vs eps2 (line for each scan)
% Will need to preserve the output directories for these, but probably
% don't need verbose files.
%---------------------
% Folder ICOSout.survey
%  contains subfolders ICOSout.survey.<eps2>, where <eps2> is the value of
%  the epsilon2 parameter. The corresponding config files are in
%  ICOSout.survey/icosfit.survey.<eps2>.
D = dir('ICOSout.survey/ICOSout.survey.*');
neps2 = size(D,1);
eps2 = zeros(neps2,1);
for i=1:neps2
  fname = D(i).name;
  parts = split(fname,'.');
  eps2(i) = str2double(parts{3});
end
[seps2,Ieps2] = sort(eps2);
clear fname parts i
%%
% Now build the following matrices:
%   chi2(ncans,neps2)
%   iterations(nscans,neps2)
%   rtimes(neps2,3)
chi2 = [];
for i=1:neps2
  base = ['ICOSout.survey/' D(Ieps2(i)).name];
  S = ICOS_setup(base);
  if isempty(chi2)
    chi2 = zeros(length(S.scannum),neps2);
    iterations = zeros(length(S.scannum),neps2);
    nfev = zeros(length(S.scannum),neps2);
    rtimes = zeros(3,neps2);
    scannum = S.scannum;
    Ncols = S.v+2; % Number density columns
    Ncol_offsets = Ncols-min(S.p_cols)+1; % 
    Nparams = unique(S.col_params(Ncol_offsets));
    N = cell(length(Nparams),1);
    for j=1:length(Nparams)
      N{j} = struct('name', S.output_cols{S.p_cols(Nparams(j)+1)}, ...
        'N', zeros(length(S.scannum),neps2));
    end
  end
  chi2(:,i) = sqrt(S.chi2);
  iterations(:,i) = S.info(:,5);
  nfev(:,i) = S.info(:,7);
  rtimes_in = load([base '/icosfit.time.dat'])/length(scannum);
  rtimes_in = rtimes_in(:,1)*60 + rtimes_in(:,2);
  rtimes(:,i) = rtimes_in;
  for j=1:length(Nparams)
    N{j}.N(:,i) = S.fitdata(:,S.p_cols(Nparams(j)+1));
  end
end
%%
clear rtimes_in i S Ncols Ncol_offsets j
%%
clear D eps2 Ieps2 base
%%
% Times
figure;
semilogx(seps2,rtimes');
title('Fit Time vs \epsilon_2');
xlabel('\epsilon_2');
ylabel('Mean Seconds/Scan');
legend('real','user','sys');
%%
% Chi2 vs eps2
figure;
semilogx(seps2,chi2','-*');
title('\sigma by \epsilon_2');
xlabel('\epsilon_2');
ylabel('\sigma');
%%
% Chi2 vs scan
figure;
plot(scannum,chi2,'-*');
title('\sigma by Scan');
xlabel('Scan Number');
ylabel('\sigma');
%%
% Iterations vs eps2
figure;
semilogx(seps2,iterations','-*');
title('Iterations vs \epsilon_2');
xlabel('\epsilon_2');
ylabel('Iterations');
%%
% Function Evaluations vs scan
figure;
plot(scannum,nfev,'-*');
title('Function Evaluations by Scan Number');
xlabel('Scan Number');
ylabel('nfev');
%%
% Function Evaluations vs eps2
figure;
semilogx(seps2,nfev','-*');
title('Function Evaluations vs \epsilon_2');
xlabel('\epsilon_2');
ylabel('nfev');
%%
for j = 1:length(N)
  figure;
  semilogx(seps2,N{j}.N','-*');
  title(sprintf('%s vs \\epsilon_2',N{j}.name));
  xlabel('\epsilon_2');
  ylabel('mol/cm^3');
end
%%
for j = 1:length(N)
  NN = N{j}.N;
  NN0 = NN(:,1)*ones(1,neps2);
  dNN = abs(NN - NN0);
  Npcterr = 100*dNN./NN0;
  figure;
  semilogx(seps2,Npcterr','-*');
  title(sprintf('%s vs \\epsilon_2',N{j}.name));
  xlabel('\epsilon_2');
  ylabel('percent error');
  ylim([-0.2 1.2]);
end
