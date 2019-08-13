function combineICOSout(outdir,regions,suffix)
% function combineICOSout(outdir,'ICOSout.1','ICOSout.2',...);
% 
% Combines multiple ICOSout directories into one directory called outdir. 
% ICOSout directories must have the same number of parameters and lines.
if nargin<3
	disp('Error: You must specify at least 2 directories to combine')
end
data=[];
for i=1:length(regions)
    name=['ICOSout.' regions{i} '.' suffix];
    temp=load([name '/ICOSsum.dat']);
    data((1+length(data)):(length(data)+length(temp)),:) = temp;
end

mkdir(outdir)
fid=fopen([outdir '/ICOSsum.dat'],'w');
for j=1:length(data)
    fprintf(fid,' %i ',data(j,:));
    fprintf(fid,'\n');
end
fclose(fid);
eval(['!cp ' name '/ICOSconfig.m ' outdir]);
