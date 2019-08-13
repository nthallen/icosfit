function index = mlf_index(path)
  parts = strsplit(path,{'/', '\', '.'});
  try
    index = base2dec(parts{end-3},10)*3600 + ...
      base2dec(parts{end-2},10)*60 + ...
      base2dec(parts{end-1},10) + 1;
  catch
    error('Input path "%s" is incompatible', path);
  end
