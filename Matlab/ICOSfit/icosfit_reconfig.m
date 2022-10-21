function icosfit_reconfig(ifile, ofile, varargin)
% icosfit_reconfig(ifile, ofile, opt1, val1, opt2, val2 ...);
% Reads ifile and writes to ofile replacing lines defining
% the specified options with the new value.
% If ofile is empty, ifile is modified in place with a backup stored
% in ifile.bak.
oldlines = {};
newlines = {};
nlines = 0;
keywords = {};
patterns = {};
pattern_values = {};
npatterns = 0;

% 1 1  7181.155780  1.505e-20 0.1008   136.7617 0.71 -0.012510 355544
for i = 1:2:(length(varargin)-1)
  if contains(varargin{i}, ...
      regexpPattern('\d+ +\d+ +[0-9.]+ +[-0-9.e]+ +[0-9.]+ +[0-9.]+ +[0-9.]+ +[-0-9.]+ +[0-9]+'))
    nlines = nlines+1;
    oldlines{nlines} = varargin{i};
    newlines{nlines} = varargin{i+1};
  elseif contains(varargin{i},' ')
    error('Illegal option: "%s"', varargin{i});
  else
    npatterns = npatterns+1;
    keywords{npatterns} = varargin{i};
    patterns{npatterns} = regexpPattern(['\<' varargin{i} '\>']);
    pattern_values{npatterns} = varargin{i+1};
    % opts.(varargin{i}) = varargin{i+1};
  end
end

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
    for i=1:length(oldlines)
      if contains(tline,oldlines{i})
        tline = replace(tline,oldlines{i},newlines{i});
        break;
      end
    end
    for i=1:length(patterns)
      if contains(tline,patterns{i})
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
for i=1:npatterns
  if isempty(pattern_values{i})
    fprintf(ofp, '%s;\n', flds{i});
  else
    fprintf(ofp, '%s = %s;\n', keywords{i}, pattern_values{i});
  end
end
fclose(ofp);

if isempty(ofile)
  bakfile = [ ifile '.bak' ];
  if exist(bakfile,'file'); delete(bakfile); end
  movefile(ifile, bakfile);
  movefile(ofname, ifile);
end
