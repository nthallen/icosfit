function PTEfixtemp(PTEif,PTEof,PTfile,Tname)
% Program to update temperatures in the PTE file from a new PT file. 
% normal usage 
% >> PTEfixtemp
%    if no arguments given program assumes PTEfile name of PTE.txt and
%    writes to same file name.
%    assumes PT.mat is the name of the PT file and Tavg is the temperature
%    vector
% optional usage
% >> PTEfixtemp('PTEif','PTEof','PTfile','Tname')
%    where PTEif is name of input PTE file; default 'PTE.txt'
%          PTEof is name of output PTE file; default same as PTEif
%          PTfile is name of PT.mat file; default PT.mat
%          Tname is name of temperature vectorl default is Tavg
%

if nargin==0
    PTEif='PTE.txt';
    PTEof='PTE.txt';
    PTfile='PT.mat';
    Tname='Tavg';
elseif nargin==1
    PTEof=PTEif;
    PTfile='PT.mat';
    Tname='Tavg';
elseif nargin==2
    PTfile='PT.mat';
    Tname='Tavg';
elseif nargin==3
    Tname='Tavg';
end
if isempty(PTEof)
    PTEof=PTEif;
end

PTE=load(PTEif);
PT=load(PTfile);

V = [false; diff(PT.ScanNum)>0];
PTE(:,3)=interp1(PT.ScanNum(V),PT.(Tname)(V),PTE(:,1));

save(PTEof,'PTE','-ascii')
