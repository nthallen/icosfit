function PTE_hack(PTEin,PTEout,PTEnumber)
%Create a PTE file with constant tuning rate from a small PTE file.
%Usage: PTE_hack(PTEin,PTEout,PTEnumber)
%PTEin = small PTE file whos tuning rate you want to use
%PTEout = name of PTE output file. If left out will be same as PTEin.
%PTEnumber = line number in PTEin that you want to use for the tuning rate.
%Default is line 1.
%

t=load(PTEin);
if exist('PT.mat','file')
    load PT.mat;
else
    error('PT.mat does not exist')
end
if nargin<3
    PTEnumber=1;
end
if nargin<2
    PTEout=PTEin;
end
t2=ones(range(ScanNum),1)*t(PTEnumber,:);
t2(:,1)=1:range(ScanNum);
t2(:,2)=interp1(ScanNum(diff(ScanNum)>0),CellP(diff(ScanNum)>0),t2(:,1));
t2(:,3)=interp1(ScanNum(diff(ScanNum)>0),Tavg(diff(ScanNum)>0),t2(:,1));
save(PTEout,'t2','-ascii');
