function [s]=archiveICOSdata(s,line_name,t_res,varargin)

% function archiveICOSdata(struct,line_name,t_res,[prefix,suffix,mname,scomments,ncomments,iname])
%
% Produces archive ascii file for upload to ESPO archive.
% If called with no arguments, GUI is launched (not ready yet!)
% INPUTS
%   struct == struct array created using combineICOSoutline.m
%   line_name == txt file with which lines to use. The names should coorespond to the
%           names in struct (i.e. H2O.a, CH4.c,).
%   t_res == time_resolution of output data. Program uses binavg to
%           average data contained within time bins. t_res=0 will use RAW resolution and is the default.
%   iname == Instrument Name (Default: 'HUICOS')
%   mname == Mission Name (Default: 'CR_AVE')
%   scomments == special comments file (Default: ./scomments.txt)
%   ncomments == normal comments file (Default: ../ncomments.txt)
%   prefix == prefix for .WB57 file (Default: 'IC')
%   suffix == suffix for .WB57 file (Default: '')
%
% OUTPUT
%   produces file in ESPO form with name ICyyyymmdd.WB57 or
%                       {prefix}yyyymmdd{suffix}.WB57
lines=[];
if nargin == 0
    disp('Error: no GUI yet, please enter ICOSout directory and line numbers')
    return;
end
if nargin < 3
    t_res = 0; %Use RAW resolution
end

%Defaults
prefix='IC';
suffix='';
iname = 'HUICOS'; % Instrument name
mname = 'TC4'; % Mission name
if nargin<4
    scomments =  importdata('../scomments.txt','\n');% special comments
    ncomments =  importdata('../ncomments.txt','\n');% normal comments
end
if nargin>3    
    prefix = varargin{1};
    suffix = varargin{2};
    if nargin>5
        mname = varargin{3};
    end
    if nargin>6
        scomments =  importdata(varargin{4},'\n');% special comments
    else
        scomments =  importdata('scomments.txt','\n');% special comments
    end
    if nargin>7
        ncomments =  importdata(varargin{5},'\n');% normal comments
    else
        ncomments =  importdata('../ncomments.txt','\n');% normal comments
    end
    if nargin>8
        iname = varargin{6};
    end
end
delta_text='permil';
line_name=importdata(line_name,'\n');
line_name_mol=line_name(find(strncmp(line_name,'D',1)==0));
line_name_delta=line_name(find(strncmp(line_name,'D',1)==1));
wv=waves_used(eval(['s.' line_name{1} '.cpci14(10)']));

for i = 1:length(line_name_delta)
    t_h2o=time2d(eval(['s.' line_name_delta{i}(3:7) '.time']));
    d_h2o=eval(['s.' line_name_delta{i}(3:7) '.data']);
    %d_h2o=d_h2o-eval(['s.' line_name_delta{i}(3:7) '.drift_correction']);
    d_h2o=d_h2o*eval(['s.' line_name_delta{i}(3:7) '.cal']);
    u_h2o=eval(['s.' line_name_delta{i}(3:7) '.uncertainty']);
    [t,u_h2o]=binavg(t_h2o,u_h2o,t_res,min(t_h2o),max(t_h2o));
    [t,delta(:,1)] = binavg(t_h2o,d_h2o,t_res,min(t_h2o),max(t_h2o));
    t_iso=time2d(eval(['s.' line_name_delta{i}(9:end) '.time']));
    d_iso=eval(['s.' line_name_delta{i}(9:end) '.data']);
    d_iso=d_iso*eval(['s.' line_name_delta{i}(9:end) '.abundance']);
    %d_iso=d_iso-eval(['s.' line_name_delta{i}(9:end) '.drift_correction']);
    d_iso=d_iso*eval(['s.' line_name_delta{i}(9:end) '.cal']);
    u_iso=eval(['s.' line_name_delta{i}(9:end) '.uncertainty']);
    [t,u_iso]=binavg(t_iso,u_iso,t_res,min(t_h2o),max(t_h2o));
    Rsmow=eval(['s.' line_name_delta{i}(9:end) '.abundance']);
    [t,delta(:,2)] = binavg(t_iso,d_iso,t_res,min(t_h2o),max(t_h2o));
    [t,cpci]=binavg(t_h2o,eval(['s.' line_name_delta{i}(3:7) '.cpci14']),t_res,min(t_h2o),max(t_h2o));
    eval(['s.' line_name_delta{i} '.data = ((delta(:,2)./delta(:,1))/Rsmow-1)*1000;']);
    eval(['s.' line_name_delta{i} '.time = t;']);
    eval(['s.' line_name_delta{i} '.cpci14 = cpci;']);
    eval(['s.' line_name_delta{i} '.multiplier = 1;']);
    eval(['s.' line_name_delta{i} '.cal = 1;']);
    eval(['s.' line_name_delta{i} '.drift_correction = 0;']);
    eval(['s.' line_name_delta{i} '.precision = 1;']);
    eval(['s.' line_name_delta{i} '.abundance = 1;']);
    eval(['s.' line_name_delta{i} '.unit = delta_text;']);
    if strcmp(line_name_delta{i}(9:end-2),'HDO')
        text=' d-D ';
    elseif strcmp(line_name_delta{i}(9:end-2),'H218O')
        text='  d-18O';
        elseif strcmp(line_name_delta{i}(9:end-2),'H217O')
            text='  d-17O';
    end;
    eval(['s.' line_name_delta{i} '.text = text;']);
    v0= [NaN];
    eval(['s.' line_name_delta{i} '.v0 = v0;']);
    uncertainty=(u_iso./delta(:,2)+u_h2o./delta(:,1)).*((delta(:,2)./delta(:,1))/Rsmow)*1000;
    eval(['s.' line_name_delta{i} '.uncertainty = uncertainty;']);
    %Optional Purge of Data
    %Purge del18O less than 10 ppmv water vapor
%     if strcmp(line_name_delta{i}(9:end-2),'H218O')
%         k=find(s.H2O.a.data*s.H2O.a.cal*1e6<10);
%         eval(['s.' line_name_delta{i} '.data(k) = NaN;']);
%         eval(['s.' line_name_delta{i} '.uncertainty(k) = NaN;']);
%     end
end 
clear d_iso d_h2o delta t_iso t_h2o;

t = time2d(eval(['s.' line_name{1} '.time']));
t0=min(t);
tend=max(t);
for i = 1:length(line_name)
    temp=eval(['s.' line_name{i}]);
    v0(i)=temp.v0;
    t=time2d(temp.time);
    d=temp.data*temp.cal*temp.abundance;
    %d=d-eval(['s.' line_name{i} '.drift_correction']);
    [t,data(:,i)] = binavg(t,d,t_res,t0,tend);
    if t_res ~= 0
        prec = temp.precision/sqrt(t_res/(wv.NCoadd/wv.FTrigger));
        prec = num2str(prec,'%e');
        prec = str2num(prec(:,end-1:end));
        precision(i) = 1./(10.^(prec));
    else
        precision(i) = temp.precision/10;
    end
    multiplier(i) = temp.multiplier;
    [t,UNCERTAINTYsubmit(:,i)]=binavg(time2d(temp.time),temp.uncertainty*temp.multiplier,t_res,t0,tend);
end

% create .WB57 file

fltdate=datestr(eval(['s.' line_name{1} '.time(1)/86400'])+datenum('1-Jan-1970'),29);
fltday=fltdate([1:4,6:7,9:10]); 
% Filters
ICOSsubmit=data.*(ones(size(data,1),1)*multiplier);
ICOSsubmit=ICOSsubmit.*(ones(size(data,1),1)*(1./precision));
if t_res~=0
UNCERTAINTYsubmit=UNCERTAINTYsubmit.*(ones(size(data,1),1)*(1./precision))/sqrt(t_res/.4);
else
UNCERTAINTYsubmit=UNCERTAINTYsubmit.*(ones(size(data,1),1)*(1./precision));
end
filename=[prefix fltday suffix '.WB57'];
disp(['Archive filename is ' filename])
disp(['Archive for ' iname ' instrument during ' mname])
format 

i=isnan(ICOSsubmit);
%[m,n]=find(i==1);
if (isempty(i)==0)
    ICOSsubmit(i)=9999999;
    UNCERTAINTYsubmit(i)=9999999;
end
i=isnan(UNCERTAINTYsubmit);
if (isempty(i)==0)
    UNCERTAINTYsubmit(i)=9999999;
end


fid=fopen(filename,'w');
fprintf(fid,'%i 1001 \n',12+2*length(line_name)+1+length(scomments)+1+length(ncomments)+1 );	% # of lines in head (NLHEAD) = 24
fprintf(fid,'Sayres, D.S.,  Hanisco, T.F.,  St. Clair, J.M.,  O''Brien, A.,  Allen, N.T.,  J.G. Anderson \n');
fprintf(fid,'Harvard University, Cambridge, MA 02138, Tel (617) 495-5922 \n');
fprintf(fid,'%s \n',iname);	% instrument name (SNAME)
fprintf(fid,'%s \n',mname);	% mission name (MNAME)
fprintf(fid,'1 1 \n');					% stupid stuff about volumes of data
today=fix(clock);						% create creation date
rdate=[int2str(today(1)),' ', int2str(today(2)),' ', int2str(today(3))];
fprintf(fid,[fltday(1:4),' ',fltday(5:6),' ',fltday(7:8),'  ',rdate '\n']);
fprintf(fid,'0 \n');					% non-uniform time intervals
fprintf(fid,'Elapsed time (sec) from 0 GMT on flight day \n');	% independent variable  
fprintf(fid,'%i \n',2*length(line_name));		% dependent variables
fprintf(fid,'%0.3f ',[precision; precision]); % scale factor to multiply values by   
fprintf(fid,' \n');
fprintf(fid,'%i ',9999999*ones(1,2*length(line_name))); % NaN variable    
fprintf(fid,' \n');
for i = 1:length(line_name) 
    text=eval(['s.' line_name{i} '.text']);
    isoname{i}=[text, '  U-' strtrim(text)];
    unit=eval(['s.' line_name{i} '.unit']);
    v0=eval(['s.' line_name{i} '.v0']);
    fprintf(fid,'%s Volume Mixing Ratio (%s)- line %0.4f cm-1; HITRAN correction factor = %0.4f \n',text,unit,v0,eval(['s.' line_name{i} '.cal']));
    fprintf(fid,'%s Uncertainty (%s)\n', text, unit);
end
fprintf(fid,'%i \n',length(scomments));  % number of special comment lines 
for j = 1:length(scomments)
    fprintf(fid,sprintf('%s \n',scomments{j}));
end
fprintf(fid,'%i \n',length(ncomments)+1);  % number of normal comment lines 
for k = 1:length(ncomments)
    fprintf(fid,'%s \n',ncomments{k});
end
fprintf(fid,'   Time ');
fprintf(fid,'   %s ',isoname{:});
fprintf(fid,'\n');
for i = 1:length(t)
    fprintf(fid,'%7.1f  ',t(i));
    fprintf(fid,'%7.0f  ',[ICOSsubmit(i,:); UNCERTAINTYsubmit(i,:)]);  
    fprintf(fid,'\n');
end
fclose(fid);
  

