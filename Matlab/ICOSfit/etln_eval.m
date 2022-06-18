function FN = etln_eval(PTE,x)
% FN = etln_eval(PTE,x);
% PTE is the contents of a PTEFile starting at the sample offset column
% It should contain at least 8 columns.
% x should be a row vector of sample numbers. This function will apply
% the sample offset and scale the input to match the parameters.
if ~isrow(x)
  error('x must be a row vector');
end
if size(PTE,2) < 8
  error('PTE must have at least 8 columns');
end
if any(PTE(:,1) ~= PTE(1,1))
  error('The sample offset in PTE column 1 should be constant');
end
xx = (x - PTE(1,1))/1000;
xx2 = xx.*xx;
col = ones(1,length(xx));
FNpoly = PTE(:,2) + PTE(:,3)*xx + PTE(:,4)*xx2;
FNexp1 = (PTE(:,5)*col).*exp((-1./PTE(:,6))*xx);
FNexp2 = (PTE(:,7)*col).*exp((-1./PTE(:,8))*xx);
FN = FNpoly + FNexp1 + FNexp2;
