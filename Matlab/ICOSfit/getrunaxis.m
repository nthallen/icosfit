function axisname = getrunaxis(co)
% axisname = getrunaxis;
% axisname = getrunaxis(co);
% Returns the basename of parent directory of getrundir
if nargin < 1
    rd = getrundir;
else
    rd = getrundir(co);
end
m = findstr(filesep,rd);
axisname = rd(m(end-1)+1:m(end)-1);
