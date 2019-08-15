function run = getrundir(co)
% run = getrundir([callbackObject]);
% Determines run based on the current directory. If
% callbackObject is given or gcbo returns an object and
% the containing figure has the tag 'eng_ui' or 'scan_viewer',
% the directory is read from the figure's UserData.
run = '';
if nargin < 1
    co = gcbo;
end
while ~isempty(co)
    try
      t = [ get(co,'type') '/' get(co,'tag') ];
      if strcmp(t, 'figure/eng_ui') || strcmp(t, 'figure/scan_viewer')
        run = get(co, 'UserData');
        break;
      end
      co = get(co, 'Parent');
    catch err
      break;
    end
end
% Otherwise, use the current directory
if isempty(run)
  run = pwd;
end
