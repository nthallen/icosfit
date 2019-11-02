function params = icosfit_getconfig(ifile, varargin)
ifp = fopen(ifile,'r');
params = [];
while true
  tline = fgets(ifp);
  if isempty(tline) || isnumeric(tline)
    break;
  end
  n = regexp(tline, '([^= ]*) *= *([^;]*);','tokens');
  if iscell(n) && isscalar(n)
    n = n{1};
    if iscell(n) && length(n) == 2
      for i = 1:length(varargin)
        if strcmp(varargin{i},n{1})
          params.(n{1}) = n{2};
        end
      end
    end
  end
end
fclose(ifp);
