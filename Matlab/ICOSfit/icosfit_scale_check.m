function icosfit_scale_check(base)
% icosfit_scale_check(base)
% Produces a figure to compare fit parameter values to their scale values.
% icosfit (and the underlying levmar library) perform best when the
% parameter values are 'close' to their scale values. The generated figure
% is a box plot of the log base 10 of the ratio of the absolute value of
% the parameter values to their dscale values. 'close' then would include
% values plotted between -1 and 1 (i.e. ratios between 0.1 and 10). Of
% course if a parameter takes values crossing zero, there are bound to be
% some values much less than -1.
% The figure displays only parameters that are not fixed for the fit.
S = ICOS_setup(base);
if S.ICOSfit_format_ver < 4
  error('Fit requires ICOSfit format verison 4, was %d', ...
    S.ICOSfit_format_ver);
end
if ~bitand(S.Verbosity,32)
  error('Fit requires Verbosity bit value 32');
end
floating_params = find(any(S.fitdata(:,S.float_cols)));
p_vals = abs(S.fitdata(:,S.p_cols(floating_params)));
p_scales = S.fitdata(:,S.scale_cols(floating_params));
params = regexprep(S.output_cols(S.p_cols(floating_params)),'^.* Value: ','');
%
figure;
boxplot(log10(p_vals ./ p_scales));
set(gca,'XTickLabels',params,'XTickLabelRotation',75);
title(sprintf('%s: log10(|Value|/Scale) by parameter', base));
