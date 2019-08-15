function normalize(flist, fontsize, markersize )
% Normalize a figure for printing
% normalize
%   normalize the current figure
% normalize( f [, fontsize [, markersize ]] )
%   normalize figure(s) f, optionally specifying the
%   font size (defaults to 12) and marker size (defaults to 4). 

if nargin < 3
  markersize = 4;
  if nargin < 2
    fontsize = 12;
    if nargin < 1
      flist = gcf;
    end
  end
end
if size(flist,1) > 1; flist = flist'; end

for f = flist
  figure(f);
  set(f,'resizefcn',''); % to defend against legend resizing
  FU = get(f,'PaperUnits');
  set(f,'PaperUnits','points');
  PP = get(f,'PaperPosition');
  set(f,'PaperUnits',FU);
  
  alist = findobj(f,'type','axes');
  for ax = alist'
    set(ax,'Units','normalized');
    if version('-release') < 12
      AP = get(ax,'Position');
      set(ax,'PlotBoxAspectRatioMode', 'manual');
      set(ax,'PlotBoxAspectRatio',[ AP(3)*PP(3) AP(4)*PP(4) 1 ] );
      texts = [ ax; get(ax,'xlabel'); get(ax,'ylabel'); get(ax,'title'); ...
          findobj(ax,'type','text') ];
      for t = texts'
        tp = get( t, 'position' );
        set(t,'FontUnits','normalized' );
        set(t,'FontSize',fontsize/(AP(4)*PP(4)));
        % tp1 = get( t, 'position' );
      end
    end
    set( findobj(ax,'type','line'),'MarkerSize', markersize);
  end
  
  % Adjust the position
  pos = get( f, 'position' );
  PPrat = PP(4)/PP(3);
  prat = pos(4)/pos(3);
  if PPrat > prat
    pos(3) = pos(4)/PPrat;
  else
    pos(4) = pos(3)*PPrat;
  end
  set( f, 'position', pos );
end
