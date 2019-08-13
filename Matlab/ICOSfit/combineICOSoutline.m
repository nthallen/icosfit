function [output]=combineICOSoutline(regions,suffix,calc_sigma)
% function combineICOSoutline({'R1','R1a',...},{''cc18','wl1','...});
% 
% Combines multiple ICOSout directories and suffixes with different lines 
%into one structure. 
% s = struct( 'iso', [], 'v0', [], 'time', [], 'cpci14', [], 'data', [],...
%           'cal', [], 'precision', [], 'multiplier', [], 'abundance', [],...
%           'text', [], 'unit', [], 'drift', 0, 'drift_correction', 0,...
%           'cross_section', [], 'doppler_width', [], 'sigma', [], 'uncertainty', []...
%           'pressure', [], 'temperature', [], 'PTEfile', [], 'sbasefile', [],...
%           'suffix', [] );

lines=[];
if nargin < 3
    calc_sigma=1;
end
%define struct
s = struct( 'iso', [], 'v0', [], 'time', [], 'scannum', [], 'data', [], 'cal', [], 'precision', [], 'multiplier', [], 'abundance', [], 'text', [], 'unit', [], 'drift', 0, 'drift_correction', 0, 'cross_section', [], 'doppler_width', [], 'lorentz_width', [], 'sigma', [], 'uncertainty', [], 'pressure', [], 'temperature', [], 'PTEfile', [], 'sbasefile', [], 'suffix', [] );
lo=fitline('load');
cfg = load_ICOSfit_cfg;
%reads in calibration numbers
% H2O.a.cal = 1;
% H2O.b.cal = 1;
% H2O.c.cal = 1;
% H2O.d.cal = 1;
% H2O.e.cal = 1;
% HDO.a.cal = 1;
% HDO.b.cal = 1;
% HDO.c.cal = 1;
% HDO.d.cal = 1;
% HDO.e.cal = 1;
% HDO.f.cal = 1;
% H218O.a.cal = 1;
% H218O.b.cal = 1;
% H218O.c.cal = 1;
% H217O.a.cal = 1;
% H217O.b.cal = 1;
% H217O.c.cal = 1;
% CH4.a.cal = 1;
% CH4.b.cal = 1;
% cal_numbers;

for i=1:length(suffix)
    chi=[]; scannum=[]; sigma=[]; aveP=[]; P=[]; T=[]; DW=[]; LW=[];
    for k=1:length(regions)
        base = ['ICOSout.' regions{k} '.' suffix{i}];
        disp(['Reading ' base ' ...']);
        data=load([base '/ICOSsum.dat']);
        l=size(data,1);
        [chi(1+end:end+l,:),scannum(1+end:end+l)]=mixlines(base,4);
        eval(['run ' base '/ICOSconfig.m']);
        if calc_sigma == 1
            try
                [sigma(1+end:end+l),aveP(1+end:end+l),xx]=get_sigma_from_fit(base);
            catch
                sigma(1+end:end+l)=NaN;
                aveP(1+end:end+l)=NaN;
            end
        else
            sigma(1+end:end+l)=NaN;
            aveP(1+end:end+l)=NaN;
        end
        P(1+end:end+l)=data(:,2);
        T(1+end:end+l)=data(:,3);
        startn=n_input_params + n_base_params + n_abs_params;
        DW(1+end:end+l,:)=data(:,startn+3+([1:size(chi,2)]-1)*5);
        LW(1+end:end+l,:)=data(:,startn+5+([1:size(chi,2)]-1)*5);
    end
    disp(['Processing suffix ' suffix{i} ' ....']);
    D=ne_load('HCIeng_1','HCI_Data_Dir');
    Axis=cfg.ScanDir(5);
    SSP_Num=eval(['D.SSP_' Axis '_Num']);
    t=interp1(SSP_Num(diff(SSP_Num)>0),time2d(D.THCIeng_1(diff(SSP_Num)>0)),scannum);
    %base = ['icosfit.' regions{1} '.' suffix{i}];
    %fid=fopen(base);
    %if fid>0
     %   temp=fgets(fid);
      %  while(~strncmp('PTEFile',temp,7))
       %     temp=fgets(fid);
%         end
%         PTEFile=temp(findstr('= ',temp)+2:end-1);
%         temp=fgets(fid);
%         Basefile=temp(findstr('= ',temp)+2:end-1);
%     else
%         PTEFile='';
%         Basefile='';
%     end
    for j = 1:size(chi,2)
        iso=lines(j,1)*10+lines(j,2);
        foundline='F';
        k=1;
        letter=char('a'-1);
        while (strcmp(foundline,'F'))
            if [lo.lines(k).hitran(1)*10+lo.lines(k).hitran(2)]==iso;
                letter=char(letter+1);
            end
            if lo.lines(k).hitran(3)==lines(j,3)
                foundline='T';
            end
            k=k+1;
        end
        name2=strtrim(isovals(iso,'text'));
        num=regexp(name2{1},'\d');
        if num(1)==1
            l=find(diff(num)>1);
            name2{1}=[name2{1}(l+1) name2{1}(1:l) name2{1}(l+2:end)];
        end
        name=['output.' name2{1} '.' letter];
        eval([name '=s;']);
        %eval([name '.cal = ' name2{1} '.' letter '.cal;']);
        eval([name '.iso = ' num2str(iso) ';']);
        eval([name '.v0 = ' num2str(lines(j,3)) ';']);
        eval([name '.cross_section = ' num2str(lines(j,4)) ';']);
        eval([name '.n = ' num2str(lines(j,7)) ';']);
        eval([name '.time = t'';']);
        eval([name '.scannum = scannum'';']);
        eval([name '.data = chi(:,j);']);
        eval([name '.multiplier = ' num2str(isovals(iso,'multiplier')) ';']);
        temp=isovals(iso,'text');
        eval([name '.text = temp{1};']);
        eval([name '.precision = ' num2str(isovals(iso,'precision')) ';']);
        eval([name '.abundance = ' num2str(isovals(iso,'abundance')) ';']);
        temp=isovals(iso,'unit');
        eval([name '.unit = temp{1};']);
        eval([name '.PTEfile = PTEfile;']);
        eval([name '.sbasefile = BaselineFile;']);
        eval([name '.suffix = suffix{i};']);
        eval([name '.sigma = sigma'';']);
        eval([name '.pressure = P'';']);
        eval([name '.temperature = T'';']);
        eval([name '.doppler_width = DW(:,j);']);
        eval([name '.lorentz_width = LW(:,j);']);
%         l=90.57; cs=eval([name '.cross_section']); v0=eval([name '.v0']);
%         S=cs*l*voigt3(v0,v0,mean(DW(:,j)),mean(LW(:,j)))/(mean(DW(:,j))*sqrt(pi/log(2)));
%         if exist('MirrorLoss.mat')
%             load MirrorLoss
%             Leff=90/(MirrorLoss);
%             uncertainty=(2*sigma)./(P./760*2.685e19./(T/273.15).*S.*Leff);
%         else
%             load ../CavityLength
%             load ../N_Passes
%             Leff=CavityLength*N_Passes;
%             uncertainty=(2*sigma./aveP).*Leff./(S*(1-2*sigma./aveP)).*(T/273.15).*(760./P)/2.684e19;
%         end
%         eval([name '.uncertainty = uncertainty''*' name '.abundance*' name '.cal*1.3;']);
       
    end
end
output.time=t;
output.Lat=interp1(time2d(D.THCIeng_1),D.BP_Lat,t);
output.Lon=interp1(time2d(D.THCIeng_1),D.BP_Lon,t);
output.Ht=interp1(time2d(D.THCIeng_1),D.BP_Ht,t);
output.AirT=interp1(time2d(D.THCIeng_1),D.BAT_FOTemp,t);
output.AirP=interp1(time2d(D.THCIeng_1),D.BAT_Ps,t);