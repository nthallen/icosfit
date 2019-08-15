function a = nsubplot( nYbins, nXbins, Ybin, Xbin, XSpace, YSpace )
% a = nsubplot( nYbins, nXbins, Ybin, Xbin [, XSpace[, YSpace]] );
% Like subplot(), but doesn't leave any space between
% the figures. It is left up to the user to shut off
% Xticklabel's for all but the bottom plot and do other
% cleanup things, like clear the topmost ylabel.
% Ybin and Xbin can be 2x1 vectors with the second element
% indicating how many bins to allocate to this subplot.
if nargin < 6
  YSpace = 0;
  if nargin < 5
    XSpace = 0;
    if nargin == 3
      Xbin = mod(Ybin-1, nXbins)+1;
      Ybin = floor((Ybin-1)/nXbins)*nXbins+1;
    end
  end
end

LM = .1 - XSpace;
RM = .1;
TM = .1;
BM = .1 - YSpace;
AW = (1 - (LM + RM))/nXbins;
AH = (1 - (TM + BM))/nYbins;
if length(Ybin) > 1
  NY = Ybin(2);
else
  NY = 1;
end
if length(Xbin) > 1
  NX = Xbin(2);
else
  NX = 1;
end
a = axes('position', ...
  [ LM+(Xbin(1)-1)*AW+XSpace  BM+(nYbins-Ybin(1))*AH+YSpace ...
    AW*NX-XSpace AH*NY-YSpace ] );
