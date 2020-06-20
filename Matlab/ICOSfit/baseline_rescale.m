function baseline_rescale(base, oname, scans, outputdir)
% baseline_rescale(base, oname, scans)
% base is the output directory of an icosfit run
% oname is the baseline name fragment. Output is written to
%   'sbase.oname.ptb'.
% scans optionally specifies which scan numbers should be included in the
%   analysis of the baseline parameter values. If specified, the scans must
%   be included in the specified icosfit run.
%
% The scans in the icosfit run must be numbered monitonically, either
% increasing or decreasing.
%
% It is assumed that any vectors in the input baseline file are sin, cos
% pairs that should be scaled together.
S = ICOS_setup(base);
if nargin < 3 || isempty(scans)
  scans = S.scannum;
end
if nargin < 4
  outputdir = '';
end
scani = interp1(S.scannum,1:length(S.scannum),scans,'nearest');
[nu, vectors,p_coeffs,Ptype,PV,Pscale] = readetlnbase(S.BaselineFile);
if Ptype ~= 0
  error('Cannot currently rescale polynomials of nu');
end
if p_coeffs ~= length(PV)
  error('p_coeffs ~= length(PV)');
end
n_base_params = p_coeffs;
if ~isempty(vectors)
  n_base_params = n_base_params + 1 + size(vectors,2);
end
if n_base_params ~= S.n_base_params
  error('n_base_params do not agree');
end
if mod(size(vectors,2),2) ~= 0
  error('Expected an even number of input vectors');
end
meanp = mean(S.fitdata(scani,S.n_input_params + (1:n_base_params)));
oPV = fliplr(meanp(1,n_base_params + (1-p_coeffs:0)));
i = 0;
for i = 0:(size(vectors,2)/2)-1
  vcols = 2*i+(1:2);
  mag = mean(sqrt(sum(S.fitdata(scani,S.n_input_params + 1 + vcols).^2,2)));
  if mag > 0
    vectors(:,vcols) = mag * vectors(:,vcols);
  end
end
writeetlnbase(oname,oPV,nu,vectors,[],[],outputdir);
