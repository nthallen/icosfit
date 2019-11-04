function icosfit_reconfig(ifile, ofile, varargin)
for i = 1:2:(length(varargin)-1)
  opts.(varargin{i}) = varargin{i+1};
end
flds = fields(opts);
ifp = fopen(ifile,'r');
ofp = fopen(ofile,'w');
while true
  tline = fgets(ifp);
  if isempty(tline) || isnumeric(tline)
    break;
  end
  hasfld = false;
  for i=1:length(flds)
    if contains(tline,flds{i})
      hasfld = true;
      break;
    end
  end
  if ~hasfld
    fprintf(ofp, '%s', tline);
  end
end
fclose(ifp);
for i=1:length(flds)
  fprintf(ofp, '%s = %s;\n', flds{i}, opts.(flds{i}));
end
fclose(ofp);
