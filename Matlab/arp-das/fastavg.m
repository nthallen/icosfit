function [avgout, std] = fastavg( data, binsize )
% function avgout = fastavg( data, binsize )
% data is a row or column vector
% binsize is an integer specifying how many points to average
% avgout is a column vector
if size(data,1)>1
   data=data';
end
small = length(data) + 1;
big = binsize * ceil(length(data)/binsize);
data(small:big) = nan * (small:big);
p = reshape( data, binsize, length(data)/binsize);
v = isnan(p);
so = sum(~v);
% i = find(isnan(p));
p(v) = 0;
soz = ( so == 0 );
so = so + soz; % prevent divide by zero
avgout = ( sum(p)./so )';
avgout(soz) = NaN;
if nargin > 1
    std = sqrt(sum(p.*p)./so - avgout'.^2);
    std(soz) = NaN;
end
