function [ t_avg, data_avg ] = binavg ( t, data, t_res,varargin )

% function [ t_avg, data_avg ] = binavg ( t, data, t_res, [t_min, t_max] )
t0=min(t);
tend=max(t);
if nargin>3
    t0=varargin{1};
    tend=varargin{2};
end
j=1;
for i = t0:t_res:tend
    data_avg(j,:)=nanmean( data( find( t >= i & t < i+t_res ) ,: ),1 );
    t_avg(j)=i+t_res/2;
    j=j+1;
end
