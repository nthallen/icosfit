classdef baseline_etalon_analyzer < handle
  properties
    BOpt
    survey_idx
    npeaks
    fig
    ax
    uiT
    btn
    yrange
    select_lines
    enabled
  end

  methods
    function self = baseline_etalon_analyzer(BOpt)
      self.BOpt = BOpt;
      self.survey_idx = self.BOpt.IR.inp_idx;
      self.npeaks = 10;
      self.fig = [];
      self.ax = [];
      self.uiT = [];
      self.btn = [];
      self.yrange = [];
      % select_lines = [];
      self.enabled = false;
    end

    function periods = analyze(self, npeaks)
      % Analyzes the fit specified by base, performing a DFT on the fit residuals
      % and generating a plot to help identify key frequencies that should be
      % fit. Optionally generates a new baseline file incorporating the largest
      % frequency component.
      %
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
      % periods is empty or a vector of etalon periods in cm-1. These are used to
      % indicate in the DFT plot where etalons have previously been added. Note
      % that the 'frequency' is in cm and the period is in cm-1. The cm-1 values
      % are most readily 'readable' in an rrfit plot, so that is what I will
      % use.
      %
      % maxf is an optional limit on the maximum frequency for the DFT. This
      % could be informed by the minimum line widths, although I don't yet know
      % what the exact relations ship should be. Presumably 1/(4*min(HWHM)) would
      % be the frequency that most closely matches the narrowest line, but
      % somewhat higher frequencies are still likely to affect a line. Perhaps 5X
      % or 10X higher would be a good guess.
      %
      % outputdir is used when the baseline is being written to another
      % directory, as is true in baseline_optimizer.
      %
      % k is the skew matrix scale factor.
      if nargin < 2 || isempty(npeaks) || npeaks == 0
        npeaks = self.npeaks;
      end
      survey = self.BOpt.survey(self.survey_idx);
      base = survey.base;
      periods = survey.User.periods;

      fprintf(1,'analyze %s: existing periods:', base);
      fprintf(1,' %f',periods);
      fprintf(1,'\n');

      S = ICOS_setup(base);
      n_scans = length(S.scannum);
      % scani = 1:n_scans;
      if ~isempty(periods)
        if ~isvector(periods)
          error('periods input must be a vector or empty');
        elseif iscolumn(periods)
          periods = periods';
        end
      end

      % Identify line widths and consider limiting the maxf to an order of
      % magnitude beyond the minimum width. (That is only a valid limitation if
      % the run explores the full range of pressures.)
      lfreq =  1./(4*[max(S.Gvcalc);min(S.Gvcalc)]);
      mfreq = mean(lfreq);
      dfreq = diff(lfreq)/2;

      % n_scans = length(scani);
      D = load(mlf_path(base,S.scannum(1)));
      min_freq = 1/abs(D(1,2)-D(end,2));
      max_freq = min(1/mean(abs(diff(D(:,2))))/2, ...
        2/min(mean(S.Gv)));
%       if maxf > 0
%         max_freq = min(max_freq, maxf);
%       end
      freq = linspace(min_freq,max_freq,1024);
      % DFT = zeros(length(f),n_scans);
      DFT = zeros(length(freq),1);
      for i=1:n_scans
        D = load(mlf_path(base,S.scannum(i)));
        DFT = DFT + abs(dft(D(:,2),(D(:,4)-D(:,3)),freq));
      end
      DFT = DFT/n_scans;

      % Look for local maxima. Then we could evaluate based on height
      % relative to the local background or absolute height.
      dmag = diff(DFT);
      peakx = find(dmag(1:end-1)>0 & dmag(2:end)<0)+1;
      % Now for each local maxima, measure the height relative to the background
      N = length(peakx);
      abshghts = zeros(1,N);
      hghts = zeros(N,1);
      for i = 1:N
        x = peakx(i);
        abshghts(i) = DFT(i);
        ileft = find([-1;dmag(1:x-1)]<0,1,'last');
        iright = find([dmag(x:end);1]>0,1)+x-1;
        % hghts(i) = mag(x)-min(mag([ileft iright]));
        bmag = min(DFT([ileft iright]));
        hghts(i) = (DFT(x)-bmag)/bmag;
      end
      %
      [Rel,I] = sort(-hghts);
      [~,J] = sort(I(1:npeaks));
      Idx(J) = 1:npeaks;
      if ~iscolumn(Idx); Idx = Idx'; end
      X = peakx(I(1:npeaks));
      Freq = freq(X)';
      Abs = DFT(X);
      Add = false(size(X));
      Rel = -Rel(1:npeaks);

      self.yrange = [0 max(max(DFT))*1.1];
      self.fig = uifigure;
      self.fig.Position(3) = 800;
      
      g = uigridlayout(self.fig);
      g.RowHeight = {'1x'};
      g.ColumnWidth = {'1x','fit'};
      self.ax = uiaxes(g);
      semilogx(self.ax,freq,DFT,freq(X(1:npeaks)),DFT(X(1:npeaks)),'*');
      if ~isempty(periods)
        freqs = 1./periods;
        x = [freqs;freqs];
        y = self.yrange'*ones(size(periods));
        hold(self.ax,'on');
        plot(self.ax,x,y,'g');
      end
      % Display line widths
      Yvals = linspace(self.yrange(2),0,length(mfreq)+2);
      hold(self.ax,'on');
      errorbar(self.ax,mfreq,Yvals(2:end-1),dfreq,'horizontal','og');
      hold(self.ax,'off');
      grid(self.ax,'on');

      title(self.ax,sprintf('%s', base));
      xlabel(self.ax,'cm');

      gg = uigridlayout(g);
      gg.RowHeight = {'fit','1x','fit'};
      gg.ColumnWidth = {'fit'};
      T = table(Idx,Freq,Abs,Rel,Add);
      self.uiT = uitable(gg,'Data',T);
      self.uiT.ColumnSortable = true;
      self.uiT.ColumnEditable = [false false false false true];
      self.uiT.ColumnWidth = 'fit';
      self.select_lines = cell(npeaks,1);
      self.uiT.DisplayDataChangedFcn = @(src,evt)self.update_choices();

      self.btn = uibutton(gg,'Text','Add Selected Frequencies');
      self.btn.Layout.Row = 3;
      self.btn.ButtonPushedFcn = @(src,evt)self.add_selected();
      self.btn.Enable = 'off';
      % pause;
    end

    function update_choices(self)
      for i = 1:self.npeaks
        if self.uiT.Data.Add(i)
          idx = self.uiT.Data.Idx(i);
          if isempty(self.select_lines{idx})
            hold(self.ax,'on');
            freq = self.uiT.Data.Freq(i);
            self.select_lines{idx} = ...
              plot(self.ax,[freq freq],self.yrange,'r');
          end
        else
          idx = self.uiT.Data.Idx(i);
          if ~isempty(self.select_lines{idx})
            delete(self.select_lines{idx});
            self.select_lines{idx} = [];
          end
        end
      end
      if self.enabled && ~any(self.uiT.Data.Add)
        self.btn.Enable = 'off';
        self.enabled = true;
      elseif ~self.enabled && any(self.uiT.Data.Add)
        self.btn.Enable = 'on';
        self.enabled = false;
      end
    end

    function add_selected(self)
      fprintf(1,'Add Selected\n');
      ix = find(self.uiT.Data.Add);
      freqs = self.uiT.Data.Freq(ix);
      periods = 1./freqs;

      self.btn.Enable = 'off';
      self.uiT.ColumnEditable = false;
      self.enabled = false;
      drawnow;
      
      fprintf(1,'Adding %d frequencies:', length(freqs));
      fprintf(1, ' %f', freqs);
      fprintf(1, '\n Periods:');
      fprintf(1, ' %f', periods);
      fprintf(1, '\n');

      self.BOpt.add_etalon_periods(self.survey_idx, periods);
    end
  
  end
end
