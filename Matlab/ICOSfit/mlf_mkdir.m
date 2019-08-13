function mlf_mkdir( base, fileno )
% mlf_mkdir( base, fileno );
% Creates directories as necessary in preparation for writing the
% specified file number. The actual path to the file can be determined
% by mlf_path( base, fileno);
%
% Assumes n_levels = 3 and n_files = 60.
fileno = fileno-1;
n_files = 60;
l3 = mod(fileno,n_files);
fileno = (fileno - l3)/n_files; % should now evenly divide
l2 = mod(fileno,n_files);
fileno = (fileno - l2)/n_files;
if ~exist( base, 'dir' )
  if ~mkdir(base)
    error('Could not create base');
  end
end
l1p = sprintf( '%s/%02d', base, fileno );
if ~exist( l1p, 'dir' )
  if ~mkdir( l1p )
    error(['Could not create ' l1p ]);
  end
end
l2p = sprintf( '%s/%02d/%02d', base, fileno, l2 );
if ~exist( l2p, 'dir' )
  if ~mkdir( l2p )
    error(['Could not create ' l2p ]);
  end
end
