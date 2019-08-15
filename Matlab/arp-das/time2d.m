function tout = time2d(t,m,s)
% tout = time2d(t);
% t is seconds since 1970 UTC
% tout is seconds since midnight UTC
%
% tout = time2d(h,m,s);
% tout is seconds
if nargin == 1
    t1 = t(find(~isnan(t), 1 ));
    day = fix(t1./(24*60*60));
    tout = t - day*60*24*60;
else
    tout = t*3600 + m*60 + s;
end