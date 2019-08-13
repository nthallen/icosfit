function rrcompare( base1, base2, scannum );
% rrcompare( base1, base2, scannum );
% Plots to compare fits using two different baseline assumptions.

path = mlf_path('base', scannum);
path1 = mlf_path(base1, scannum);
path2 = mlf_path(base2, scannum);
log1 = load(path1);
log2 = load(path2);
x1 = log1(:,1);
x2 = log2(:,1);
run = getrun;
% fprintf(1,'length 1 is %d, 2 is %d\n', length(x1), length(x2));
if length(x1) ~= length(x2)
  error(sprintf('X vectors have different lengths: %d and %d\n', ...
    length(x1), length(x2) ));
elseif any(x1 ~= x2)
  error(sprintf('X vectors are offset by %f\n', max(x1-x2)));
end
figure;
plot( x1, log1(:,4), x2, log2(:,4), x1, log1(:,2) );
title([ 'Baseline Comparison: ' path ' ' run]);
legend('Fit 1', 'Fit 2',4);
addfuncname;

figure;
plot( x1, log1(:,3), x2, log2(:,3) );
title([ 'Fits with different baselines: ' path ' ' run]);
legend('Fit 1', 'Fit 2',4);
addfuncname;

figure;
plot( x1, log1(:,4) - log2(:,4), x1, log1(:,3)-log2(:,3) );
title([ 'Baseline Comparisons: ' path ' ' run]);
legend('Difference between baselines', 'Difference between fits',4);
addfuncname;

figure;
plot(x1, log1(:,2)-log1(:,3), x2, log2(:,2)-log2(:,3));
title(['Residuals for different baselines: ' path ' ' run ]);
legend('Fit 1','Fit 2',4);
addfuncname;
return;

function addfuncname
xl = xlim;
yl = ylim;
x = xl(1) + .025 * diff(xl);
y = yl(1) + .05 * diff(yl);
text(x,y,'rrcompare()');
