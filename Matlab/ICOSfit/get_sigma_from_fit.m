function [sigma,aveP,scannum]=get_sigma_from_fit(base)

%function sigma=get_sigma_from_fit('ICOSout')

data=load([base '/ICOSsum.dat']);
scannum=data(:,6);
sigma=ones(1,length(scannum))*NaN;
aveP=ones(1,length(scannum))*NaN;

for i =1:length(scannum)
    path = mlf_path(base, scannum(i));
    f=load(path);
    sigma(i)=std((f(:,3)-f(:,4))./f(:,5));
    aveP(i)=mean(f(:,5));
end
