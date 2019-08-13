function average_spectra(n_avg,avg_type)
runn=pwd;
runn=runn(max(strfind(runn,'/'))+1:end);
base=['../' runn '.average' num2str(n_avg)];
mkdir('../',[runn '.average' num2str(n_avg)]);
runnoF=getrun(1);
runnoF=runnoF(1:end-1);
eval(['!cp ~/CarbonData/RAW_DATA/' getrun(1) '/* ' base]);

mkdir(base,'Base')
eval(['!cp /media/data/home/hci/raw/flight/' runnoF '/Base/* ' base '/Base']);

mkdir(base,'SSP_I');
baseCPCI=[base '/SSP_I/'];
PTE=load('PTE.txt');
l=PTE(end,1);
h=0; m=0;
while (h*3600 + m*60) < l
    mkdir(baseCPCI,sprintf('%02i',h))
    while m < 60 & (h*3600 + m*60) < l
        mkdir(strcat(baseCPCI,sprintf('%02i',h)),sprintf('%02i',m))
        m=m+1;
    end
    h=h+1; m=0;
end
if strcmp(avg_type,'coadd')
    
PTEnew=[];
breaks=[1;find(diff(PTE(:,1))>1);size(PTE,1)];
for i = 1:length(breaks)-1
    j=PTE(breaks(i)+1,1);
    while j < (PTE(breaks(i+1)-1,1)-n_avg)
        try [icos,etln]=loadscans([],j:j+n_avg-1); 
        icos=mean(icos');
        etln=mean(etln');
        writebin(mlf_path(baseCPCI,j),[icos;etln]');
        PTEnew(end+1,:)=PTE(find(PTE(:,1)==j),:);
        catch
        end
        j=j+n_avg;
    end
end

elseif strcmp(avg_type,'xavg')
    PTEnew=PTE;
    [data,etln]=loadscans([],PTE(:,1));
    for i = 1:size(PTE,1)
        datanew=fastavg(data(:,i),n_avg);
        etlnnew=fastavg(etln(:,1),n_avg);
        writebin(mlf_path(baseCPCI,PTE(i,1)),[datanew';etlnnew']');
    end
else
    disp('avg_type must be either ''coadd'' or ''xavg'' ');
end
cd(['../' runn '.average' num2str(n_avg)]);
save -ascii 'PTEnew.txt' 'PTEnew'
eval(['!cp ../' runn '/PT.mat .'])
eval(['!cp ../' runn '/sbase* .'])
eval(['!cp ../' runn '/*.m .'])
% if exist(['../' runn '/MirrorLoss.mat'])
%     eval(['!cp ../' runn '/MirrorLoss.mat .'])
% end
% if exist(['../' runn '/fitline.dat'])
%     eval(['!cp ../' runn '/fitline.dat .'])
% end
% if exist(['../' runn '/waves.m'])
%     eval(['!cp ../' runn '/waves.m .'])
% end
% eval(['!cp ../' runn '/*_etln.mat .'])


