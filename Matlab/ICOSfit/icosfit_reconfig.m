function icosfit_reconfig(ifile, ofile, varargin)
% icosfit_reconfig(ifile, ofile, opt1, val1, opt2, val2 ...);
% Reads ifile and writes to ofile replacing lines defining
% the specified options with the new value.
% If ofile is empty, ifile is modified in place with a backup stored
% in ifile.bak.
for i = 1:2:(length(varargin)-1)
  opts.(varargin{i}) = varargin{i+1};
end
flds = fields(opts);
ifp = fopen(ifile,'r');
if ifp < 0; error('Unable to read file "%s"', ifile); end
if isempty(ofile)
  ofname = [ ifile '.new' ];
else
  ofname = ofile;
end
ofp = fopen(ofname,'w');
if ofp < 0; error('Unable to write to file "%s"', ofile); end
while true
  tline = fgets(ifp);
  if isempty(tline) || isnumeric(tline)
    break;
  end
  hasfld = false;
  if isempty(regexp(tline,'^ *#','once'))
    for i=1:length(flds)
      if contains(tline,flds{i})
        hasfld = true;
        break;
      end
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

if isempty(ofile)
  bakfile = [ ifile '.bak' ];
  if exist(bakfile,'file'); delete(bakfile); end
  movefile(ifile, bakfile);
  movefile(ofname, ifile);
end
