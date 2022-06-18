function A = TuningRateAnalysis(PTEfile,scan_stride,sample_stride)
% TuningRateAnalysis(PTEfile);
% TuningRateAnalysis(PTEfile,scan_stride);
% TuningRateAnalysis(PTEfile,scan_stride,sample_stride);
% scan_stride is factor by which to reduce the number of scans.
% sample_stride is the factor by which to reduce the number of samples.
% If the product of scans * samples exceeds 5e6, system performance
% can seriously degrade.
% Selects the scan with the minimum standard deviation of the percent
% difference from the mean tuning rate, and writes that out to PTEref.txt
if nargin < 1
  PTEfile = 'PTE.txt';
end
if nargin < 2
  scan_stride = 1;
end
if nargin < 3
  sample_stride = 1;
end
%%
PTE = load(PTEfile);
%%
wvs = waves_used(PTE(:,1));
%%
S0 = PTE(1,4);
S1 = wvs.NetSamples - wvs.TzSamples;
S = S0:sample_stride:S1;
scans_idx = 1:scan_stride:size(PTE,1);
scans = PTE(scans_idx,1);
% if length(scans)*length(S) > 5e6
%   fprintf(1,'Requested scans*samples = %d*%d = %.2e.\nConsider increasing the scan_stride or sample_stride\n', ...
%     length(scans),length(S),length(scans)*length(S));
%   return;
% end
x = (S - S0)/1000;
x1 = ones(1,length(x));
dFNdx = PTE(scans_idx,6)*x1 + ...
        PTE(scans_idx,7)*x + ...
        ((-PTE(scans_idx,8)./PTE(scans_idx,9))*x1).*exp(-(PTE(scans_idx,9).^(-1))*x) + ...
        ((-PTE(scans_idx,10)./PTE(scans_idx,11))*x1).*exp(-(PTE(scans_idx,11).^(-1))*x);
%%
% figure; plot(S,dFNdx');
% xlabel('Sample Number');
% ylabel('Fringes/Sample');
%%
% figure; plot(PTE(scans_idx,1),dFNdx);
% xlabel('Scan Number');
% ylabel('Fringes/Sample');
%%
mean_dFNdx = ones(size(dFNdx,1),1)*mean(dFNdx);
ddFNdx = 100*(dFNdx - mean_dFNdx)./mean_dFNdx;
% figure;
% plot(PTE(scans_idx,1),ddFNdx);
% xlabel('Scan Number');
% ylabel('Pct dev from mean');
%%
% skip = [1 1]; % initial scans and samples to skip
% samp_idx = skip(2):length(S);
% x_lims = S(samp_idx([1 end]));
% scan_idx = skip(1):size(PTE,1);
% y_lims = PTE(scan_idx([1 end]),1);
% imagesc(x_lims, y_lims, ddFNdx(scan_idx,samp_idx));
% title('Tuning Rate Variability');
% ylabel('Scan Number');
% xlabel('Sample Number');
% c = colorbar;
% c.Label.String = 'Percent Deviation from Mean';
% shg;
%%
% figure;
% mesh(S,PTE(scans_idx,1),ddFNdx);
% xlabel('Sample Number');
% ylabel('Scan Number');
% title('Percent deviation from Mean');
if nargout > 0
  A.Sample = S;
  A.ScanNum = PTE(scans_idx,1);
  A.ddFNdx = ddFNdx;
end
%%
stds = std(ddFNdx,0,2);
stdsmini = find(stds == min(stds),1);
ref = PTE(scans_idx(stdsmini),:);
save PTEref.txt ref -ASCII
fprintf(1, ...
  'PTEref.txt chosen from scan %d having standard deviation of the\n', ...
  ref(1));
fprintf(1,'percent difference from the mean tuning rate of %.3f\n', min(stds));
%%
% figure;
% plot(S,ddFNdx,'k',S,ddFNdx(stdsmini,:),'r');
