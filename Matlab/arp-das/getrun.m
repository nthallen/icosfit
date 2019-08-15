function run = getrun(noheader, co)
% run = getrun([noheader[, callbackobject]])
%  Extracts the run from the current working directory.
%  Callback Object may be explicitly specified for more
%  reliable results.
if nargin < 2
    co = gcbo;
    if nargin < 1
      noheader = 0;
    end
end
run = getrundir(co);
m = max(findstr(filesep,run))+1;
run = run([m:length(run)]);
if noheader == 0
  if run(length(run)) == 'F'
    run = [ 'Flight ' run(1:length(run)-1) ];
  else
    run = [ 'Run ' run ];
  end
end
