function average_spectra(n_avg,avg_type,fsample,PTEfile,scans,baseraw)
%function average_sepctra(n_avg,avg_type,fsample,PTEfile,scans,baseraw)
%creates new directory structure with averaged spectra
%
%n_avg is the integer number of spectra or values to average
%avg_type can be either 'coadd' or 'xavg'
%   coadd: takes the mean of n_avg spectra
%   xavg: takes the fastavg of n_avg points for each spectra
%fsample: the fraction of n_avg scans required to create the average
%PTEfile: the name of the PTE file
%scans: a vector of scan numbers that all must exist in the PTEfile.
%   Defaults to PTE(:,1)
%baseraw: The source scans directory. Defaults to [] to pick the usual.
%
runn=getrun(1);
base=['../' runn '.average' num2str(n_avg)];
mkdir('../',[runn '.average' num2str(n_avg)]);
if nargin < 6
    baseraw = [];
end
% runnoF=getrun(1);
% runnoF=runnoF(1:end-1);
% eval(['!cp ~/HCl/RAW_DATA/' getrun(1) '/* ' base]);

% mkdir(base,'Base')
% eval(['!cp /media/data/home/hci/raw/flight/' runnoF '/Base/* ' base '/Base']);

mkdir(base,'SSP');
baseSSP=[base '/SSP/'];
PTE=load(PTEfile);
if nargin < 5
  scans = PTE(:,1);
end

L = PTE(end,1);
h=0; m=0;
while (h*3600 + m*60) < L
    mkdir(baseSSP,sprintf('%02i',h))
    while m < 60 && (h*3600 + m*60) < L
        mkdir(strcat(baseSSP,sprintf('%02i',h)),sprintf('%02i',m))
        m=m+1;
    end
    h=h+1; m=0;
end

if strcmp(avg_type,'coadd')
    
  PTEnew=[];
  i=1;
  for j = PTE(1,1):n_avg:PTE(end,1)
    s = PTE( PTE(:,1)>=j & PTE(:,1)<j+n_avg ,1);
    nsample(i,2) = length(s);
    nsample(i,1) = s(round(length(s)/2));
    if nsample(i,2)>=n_avg*fsample
      try [icos,etln]=loadscans(baseraw,s);
        icos=mean(icos');
        etln=mean(etln');
        writebin(mlf_path(baseSSP,nsample(i,1)),[icos;etln]');
        PTEnew(end+1,:)=PTE(PTE(:,1)==nsample(i,1),:);
      catch
      end
    end
    i=i+1;
  end

elseif strcmp(avg_type,'xavg')
    PTEnew=PTE;
    [data,etln]=loadscans(baseraw,PTE(:,1));
    for i = 1:size(PTE,1)
        datanew=fastavg(data(:,i),n_avg);
        etlnnew=fastavg(etln(:,1),n_avg);
        writebin(mlf_path(baseSSP,PTE(i,1)),[datanew';etlnnew']');
    end
else
    disp('avg_type must be either ''coadd'' or ''xavg'' ');
end
cd(['../' runn '.average' num2str(n_avg)]);
save -ascii 'PTEnew.txt' 'PTEnew'
save nsample.mat nsample
eval(['!cp ../' runn '/PT.mat .'])
eval(['!cp ../' runn '/*.m .'])

if exist(['../' runn '/Cell_Config.m'])
    eval(['!cp ../' runn '/Cell_Config.m .'])
end
if exist(['../' runn '/fitline.dat'])
    eval(['!cp ../' runn '/fitline.dat .'])
end
if exist(['../' runn '/waves.m'])
    eval(['!cp ../' runn '/waves.m .'])
elseif exist(['../RAW/' runn '/waves.m .'])
    eval(['!cp ../RAW/' runn '/waves.m .'])
end
eval(['!cp ../' runn '/*_etln.mat .'])
if exist(['../' runn '/sbase*'])
    eval(['!cp ../' runn '/sbase* .'])
end



