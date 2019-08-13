function [var_data,t_int]=allan_var_plot(data,time,varargin)

%function [var_data,t_int]=allan_var_plot(data,time)
%create allan variance plot given data and time
%Time is assumed to be in seconds.

maxint_t=(max(time)-min(time))/5; %maximum integration time is total time/10.
min_t=round(diff(time(1:2))*10)/10; %initial integration time equals minimum time differance to nearest 1/10th second.
max_tt=min_t;
inc=1;
j=1;
while maxint_t > max_tt
    inc=min_t;
    if min_t==0.1;
        inc=0.1;
    elseif min_t==1;
        inc=1;
    elseif min_t==10;
        inc=5;
    elseif min_t==100;
        inc=10;
    elseif min_t==1000;
        inc=50;
    else
        inc=50;
    end
    max_tt=max_tt*10;
    if max_tt>maxint_t; max_tt=maxint_t; end
    for i=min_t:inc:max_tt
        [t_avg,data_avg]=binavg(time,data,i);
        var_data(j)=nanvar(data_avg);
        t_int(j)=i;
        j=j+1;
    end
    min_t=min_t*10;
end

%create plot
figure
nsubplot(3,1,[1,1],1);
plot(time-min(time),data)
axis tight
set(gca,'XAxisLocation','top')
xlabel('Time(s)')
ylabel('Data (units)')
box off
nsubplot(3,1,[3,2],1);
loglog(t_int,var_data)
hold on
t_i=round(diff(time(1:2))*10)/10;
x=[t_i,t_i*10,t_i*100,t_i*1e3,t_i*1e4];
var_i=nanvar(data);
%y=[var_i,var_i/sqrt(10),var_i/sqrt(100),var_i/sqrt(1e3),var_i/sqrt(1e4)];
y2=[var_i,var_i/10,var_i/100,var_i/1e3,var_i/1e4];
xlabel('Integration Time (s)')
ylabel('Variance (\sigma^2)')
%plot(x,y,'--')
plot(x,y2,'-.')
if nargin==2
  text(t_i*5e2,var_i,['\sigma(' num2str(t_i) '-sec) = ' num2str(nanstd(data))]);
  text(t_i*5e2,var_i/2,['\sigma(' num2str(t_i*10) '-sec) = ' num2str(nanstd(fastavg(data,10)))]);
  text(t_i*5e2,var_i/4,['\sigma(' num2str(t_i*100) '-sec) = ' num2str(nanstd(fastavg(data,100)))]);
elseif nargin==3
  text(t_i*5e2,var_i,['\sigma(' num2str(t_i) '-sec) = ' num2str(nanstd(data))]);
  text(t_i*5e2,var_i/2,['\tau_{Allan} = ' num2str(varargin{1}) ' s']);
  [t_allan,data_allan]=binavg(time,data,varargin{1});
  text(t_i*5e2,var_i/4,['\sigma_{Allan} = ', num2str(nanstd(data_allan))]);
end
box off