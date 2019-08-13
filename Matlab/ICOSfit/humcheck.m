function humcheck;
X0 = [-1000:1000]';
Ys = [.01 .1 .5 1 5 10 20 50];
Xs = [ 50 50 200 1000 1000 1000 1000 1000 ];
for i = 1:length(Ys)
  Y = Ys(i);
  X = X0 * Xs(i)/1000;
  [K,DKDX,DKDY,R] = humdev(X,Y);
  K1 = humlik(X,Y);
  dK = K-K1;
  figure;
  nsubplot(5,1,1); plot(X,K);
  title(sprintf('Y = %f', Y ));
  set(gca,'XTickLabel',[]);
  X1 = (X(1:end-1)+X(2:end))/2;
  DKDX1 = diff(K)./diff(X);
  nsubplot(5,1,2); plot(X,DKDX,X1,DKDX1);
  ylabel('dK/dX');
  set(gca,'XTickLabel',[],'YAxisLocation','right');
  nsubplot(5,1,3); plot(X,DKDY);
  ylabel('dK/dY');
  set(gca,'XTickLabel',[]);
  nsubplot(5,1,4); plot(X,R,'*'); ylim([ .5 6.5 ]);
  set(gca,'YAxisLocation','right', 'XTickLabel',[]);
  nsubplot(5,1,5); plot(X,dK);
  ylabel('dK');
  addzoom;
end
