function p=mlf_path( base, fileno, suffix );
% p = mlf_path( base, fileno[, suffix] );
% Returns the full path to the specified file number stored in
% the Multi-Level-File hierarchy used by various Anderson Group
% instruments. The object is to avoid having too many individual files in
% one directory. This is motivated by past experience where filesystem
% performance deteriorated badly as the size of directories rose. More
% recent analysis suggests that modern file systems do not suffer from this
% shortcoming, so this effort may be unnecessary or even somewhat
% counter-productive. Advantages I can think of include:
%   GUI file browsing tools won't hang counting thousands of files
%   dircksum records directory entries in useful chunks
%
% Assumes n_levels = 3 and n_files = 60.
% suffix defaults to '.dat'
% See Also: mlf_mkdir
if nargin < 3
  suffix = '.dat';
end
fileno = fileno-1;
n_files = 60;
l3 = mod(fileno,n_files);
fileno = (fileno - l3)/n_files; % should now evenly divide
l2 = mod(fileno,n_files);
fileno = (fileno - l2)/n_files;
p = sprintf( '%s/%02d/%02d/%02d%s', base, fileno, l2, l3, suffix );
