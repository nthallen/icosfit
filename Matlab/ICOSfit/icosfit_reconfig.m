function icosfit_reconfig(ifile, ofile, varargin)
% icosfit_reconfig(ifile, ofile, opt1, val1, opt2, val2 ...);
% Reads ifile and writes to ofile replacing lines defining
% the specified options with the new value.
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
  if isempty(opts.(flds{i}))
    fprintf(ofp, '%s;\n', flds{i});
  else
    fprintf(ofp, '%s = %s;\n', flds{i}, opts.(flds{i}));
  end
end
fclose(ofp);
