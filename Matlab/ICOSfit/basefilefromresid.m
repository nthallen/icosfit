function [Unew,V,S]=basefilefromresid(region,suffix,nsvds,name)
%function [U,V,S]=basefile(region,nsvds,suffix)
xmin = [];
resids = [];
nscans = 0;
for j=1:length(region)
    base = [ 'ICOSout.' region{j} ];
    if ~isempty(suffix); base = [ base '.' suffix ]; end
    lines=[];
    by_molecule=0;
    ICOSsetup;
for i = scannum'
  path = mlf_path( base, i );
  f = load(path);
  nscans = nscans+1;
  if isempty(xmin)
    resids = f(:,3)-f(:,4)+f(:,5);
    xmin = f(1,1);
  else
    if f(1,1) < xmin
      nc = xmin-f(1,1);
      resids = [ NaN*zeros(3,size(resids,2)); resids ];
      xmin = f(1,1);
    end
    if f(end,1) >= xmin + size(resids,1)
      nc = f(end,1)-xmin-size(resids,1)+1;
      resids = [ resids; NaN*zeros(nc,size(resids,2)) ];
    end
    resids(f(:,1)-xmin+1,nscans) = f(:,3)-f(:,4)+f(:,5);
  end
end
end
x = xmin:xmin+size(resids,1)-1;
[I,J]=find(resids==0);
resids(unique(I),:)=NaN;
x=x(~isnan(resids(:,1)));
resids=resids(~isnan(resids(:,1)),:);
[U,S,V]=svds(resids,nsvds);
figure; semilogy(diag(S),'*');
figure; for i=1:size(U,2); nsubplot(size(U,2),1,i,1); plot(U(:,i)); end
addzoom
Unew = zeros(max(x),size(U,2));
Unew(x,:)=U;
writeskewbase(region{1},Unew,S,V);
if nargin>=3
    eval(sprintf('!mv sbase.dat sbase%i.%s.dat',scannum(j),name))
    disp(sprintf('Moved sbase file to sbase%i.%s.dat\n',scannum(1),name))
end
