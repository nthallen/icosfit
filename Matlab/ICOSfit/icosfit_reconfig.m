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
  hasfld = '';
  for i=1:length(flds)
    if contains(tline,flds{i})
      hasfld = flds{i};
      break;
    end
  end
  if isempty(hasfld)
    fprintf(ofp, '%s', tline);
  else
    fprintf(ofp, '%s = %s;\n', hasfld, opts.(hasfld));
  end
end
fclose(ifp);
fclose(ofp);
