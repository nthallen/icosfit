function fullpath = findinpath( filename, pathdirs )
% fullpath = findinpath( filename, pathdirs )
% pathdirs is a cell array of directory names
for i=1:length(pathdirs)
  fullpath = [ pathdirs{i} filesep filename ];
  if exist(fullpath,'file')
    return;
  end
end
fullpath = '';
