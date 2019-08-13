function [Unew,V,S]=basefile(region,nsvds,suffix,range)
%function [U,V,S]=basefile(region,nsvds,suffix,range)
if isnumeric(region)
  scannum = region;
else
  scannum = fitline('region',region);
end
[data]=loadscans([],scannum);
if nargin<4
    range=300:1831;
end
[U,S,V]=svds(data(range,:),nsvds);
figure; semilogy(diag(S),'*');
figure; for i=1:size(U,2); nsubplot(size(U,2),1,i,1); plot(U(:,i)); end
addzoom
Unew = zeros(length(data),size(U,2));
Unew(range,:)=U;
cellparams=load_cell_cfg;
if cellparams.MirrorLoss == 0
    writebase('sbase.dat',U,S,V);
else
    writeskewbase(region,Unew,S,V);
end
if nargin>=3
    eval(sprintf('!mv sbase.dat sbase%i.%s.dat',scannum(1),suffix))
    disp(sprintf('Moved sbase file to sbase%i.%s.dat\n',scannum(1),suffix))
end
