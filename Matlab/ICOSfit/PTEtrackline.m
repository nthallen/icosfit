function PTEout = PTEtrackline(PTE,scans,linepos)
% PTEout = PTEtrackline(PTE, scans, linepos);
% PTE: PTE matrix (e.g. from PTE = load('PTE.txt'))
% scans: Selected scans to include in output
% linepos: output from track_line()
% PTEout: New PTE data
%
% Save the output to a new PTE file via:
%   save PTEtrk.txt PTEout -ASCII

% match scans to rows of PTE
% calculate fringe number for each scan
% Make integral adjustments (ala PTEfixskips)

if size(scans,2) > 1
    scans = scans';
end
idx = interp1(PTE(:,1),1:size(PTE,1),scans,'nearest');
v = find(PTE(idx,1) == scans);
% Now idx(v) references rows of PTE
% scans(v) and linepos(v)
fr = zeros(size(v));
for i=1:length(v)
    fr(i) = etln_evalJ(PTE(idx(v(i)),5:11),linepos(v(i))/1000);
end
% fr = PTE(v,5)+PTE(v,8)+PTE(v,10)
dfr = cumsum([ 0; round(diff(fr))]);
nfr = fr - dfr;
PTEout = PTE(idx(v),:);
PTEout(:,5) = PTEout(:,5)-dfr;
figure;
ax = zeros(2,1);
ax(1) = nsubplot(2,1,1); plot(ax(1), PTE(idx(v),1),fr,'.-',PTE(idx(v),1),nfr,'.-');
legend(ax(1),'before','after');
ax(2) = nsubplot(2,1,2); plot(ax(2), PTE(idx(v(1:end-1)),1), diff(nfr),'.-');
