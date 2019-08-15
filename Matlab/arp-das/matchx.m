function matchx(ax, save_code)
% matchx([ax]);
% Set xlimits on all axes in ax (except for legends and backgrounds)
% to match the current axes. If ax is omitted, matches all axes on
% the current figure.
if nargin<1 || isempty(ax)
  ax = findobj(gcf,'type','axes','tag','')';
end
if nargin > 1
    if save_code == 1
        xl = xlim(ax(1));
        assignin('base', 'mlazxlim', xl);
        return;
    elseif save_code == 2
        if evalin('base', 'exist(''mlazxlim'',''var'')')
            xl = evalin('base','mlazxlim');
        else
            error('HUARP:MATCHX','Xlimit not saved');
            return;
        end
    elseif save_code ==3
        set(ax,'XLimMode','auto');
        return;
    else
        error('HUARP:MATCHX','Invalid save_code');
    end
else
    xl = xlim;
end
set(ax,'XLim',xl);
% for i=ax
%   % Tag 'legend' is set by legend
%   % Tag 'nlegend' is set by nlegend
%   % Tab 'background' is set by ne_setup
%   tag = get(i,'Tag');
%   if ~strcmp(tag,'legend') && ~strcmp(tag,'nlegend') && ~strcmp(tag,'background')
%     set(i, 'XLim', xl );
%   end
% end
shg;
