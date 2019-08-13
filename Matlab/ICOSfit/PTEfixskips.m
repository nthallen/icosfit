function PTEfixskips( ifile, ofile )
% PTEfixskips( ifile [, ofile ] )
% If ofile is omitted, result is written back over ifile.
if nargin < 2
  ofile = ifile;
end
PTE = load(ifile);
fr = PTE(:,5)+PTE(:,8)+PTE(:,10);
dfr = cumsum([ 0; round(diff(fr))]);
nfr = fr - dfr;
PTE(:,5) = PTE(:,5)-dfr;
figure;
plot(PTE(:,1),fr,'.-',PTE(:,1),nfr,'.-');
legend('before', 'after');
save(ofile, 'PTE', '-ASCII');
