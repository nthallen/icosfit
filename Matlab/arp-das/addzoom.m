function addzoom(use_match, use_save)
% addzoom
%  Adds some zoom control menus and a 'MatchX' menu item to
%  the current figure.
% addzoom(use_match, use_save)
%  use_match set to zero to omit MatchX menu
%  use_save set nonzero to include saveX/restoreX menu
if nargin < 1
    use_match = 1;
end
if nargin < 2
    use_save = 0;
end
h = uimenu('label','Zoom');
uimenu(h,'label','On','Callback','zoom off; zoom on;');
uimenu(h,'label','Off','Callback','zoom off;');
uimenu(h,'label','X','Callback','zoom off; zoom xon;');
uimenu(h,'label','Y','Callback','zoom off; zoom yon;');
if use_save
    uimenu(h,'label','Save X','Callback','matchx([],1);');
    uimenu(h,'label','Restore X','Callback','matchx([],2);');
    uimenu(h,'label','Auto X','Callback','matchx([],3);');
end
if use_match
    uimenu('label','MatchX','Callback','matchx;');
end