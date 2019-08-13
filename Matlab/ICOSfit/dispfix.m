function fdata = dispfix( base );
% fitdata = dispfix( base, by_molecule );
% is by_molecule relevant?
% I'll simply try to display each fit parameter as a single line of points
% color-coded for fit or free.
% by_molecule defaults to 1
% If set to 2, will be partitioned by isotopomer
% If set to 0, all parameters will be shown on one plot
% If base is omitted, will default to 'ICOSout'
by_molecule=0;
ICOSsetup;
run = getrun;

% v = [0:nlines-1]*n_line_params + inputparams+ n_base_params + 1;
% vf0 = inputparams+2*n_base_params+n_lines*n_line_params;
% select = [ 0 1 2 3 ];
n_line_params = n_line_params + n_abs_line_params;
n_base_params = n_base_params + n_abs_params;
vf = [1:n_lines*n_line_params] + n_input_params+2*n_base_params+n_lines*n_line_params;
% vf = v + n_base_params + n_line_params;
% scannum = fitdata(:,6);
nfit = length(scannum);
bv = fitdata(:,vf);
bv = [ reshape(bv', n_line_params, nfit*n_lines )' 2*ones(nfit*n_lines,1)];
bv = reshape(bv', n_lines*(n_line_params+1), nfit);
figure;
colormap([ 0 0 .75; 0 1 1; 0 0 0]);
nsubplot( 1,4,1,[1 3]);
h = image(scannum([1 nfit]), [1/(n_line_params+1) n_lines]+.5, bv+1 );
%set(h,'CDataMapping','Scaled');
set(gca, 'YTick', [1:n_lines]);
xlabel('Scan Number');
ylabel('Line Number' );
title([ 'Free Parameters: ' run '/' base]);
nsubplot( 1, 4, 1, 4 );
colormap([ 0 0 .75; 0 1 1; 0 0 0]);
image( 1.5, 1, 1 ); hold on;
image( 1.5, 3, 2 );
text( 3, 1, 'Fixed');
text( 3, 3, 'Free');
text( 1, 5, 'Parameters:' );
text( 2, 7, 'Location');
text( 2, 9, '\gamma_{ED}');
text( 2, 11, 'NumDensity');
text( 2, 13, '\gamma_L');
xlim([ 0 7]-1); ylim([-2 30]);
set(gca,'Visible','off');
if nargout >= 1
  fddata = fitdata;
end
