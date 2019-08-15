function f = fmedianf( g, np )
% f = fmedianf( g, np );
% g is a column vector or matrix.
% np is the number of points on each side.
% f is then the result of a 2*np+1 point median filter
% applied to the columns of g.
v = ~isnan(g);
f = g;
for j = 1:size(g,2)
  if sum(v(:,j)) > np
    g1 = g(v(:,j),j);
    lg = length(g1);
    V = zeros(lg,2*np+1);
    V(:,1) = g1;
    for i = 1:np
      V(:,[2*i 2*i+1]) = ...
        [ [ ones(i,1)*g1(1,1); g1(1:lg-i,1) ] ...
          [ g1(i+1:lg,1); ones(i,1)*g1(lg,1) ] ];
    end
    f(v(:,j),j) = median( V, 2 );
  else
    f(v(:,j),j) = median(g(v(:,j),j));
  end
end
