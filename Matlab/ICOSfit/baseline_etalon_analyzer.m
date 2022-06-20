classdef baseline_etalon_analyzer < handle
  properties
    BOpt
    npeaks
  end

  methods
    function self = baseline_etalon_analyzer(BOpt)
      self.BOpt = BOpt;
      self.npeaks = 10;
    end

    function periods = analyze(self, npeaks)
      if nargin < 2 || isempty(npeaks) || npeaks == 0
        npeaks = self.npeaks;
      end
      % baseline_add_etalon(base, oname[, scans[,periods]])
      survey = self.BOpt.survey(self.BOpt.IR.inp_idx);
      base = survey.base;
      % S = ICOS_setup(base);
      % scans = S.scannum;
      periods = survey.User.periods;

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

      % Load the existing baseline and perform sanity checks
      [~, vectors,p_coeffs,Ptype,PV,~] = readetlnbase(S.BaselineFile);
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
      if endsWith(S.output_cols{S.n_input_params+1},' Value: k_input')
        n_base_params = n_base_params + 1;
      end
      if n_base_params ~= S.n_base_params
        error('n_base_params do not agree');
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
      hghts = zeros(1,N);
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
      [H,I] = sort(-hghts);
      X = peakx(I);

      yrange = [0 max(max(DFT))*1.1];
      figure;
      plot(freq,DFT,freq(X(1:npeaks)),DFT(X(1:npeaks)),'*');
      if ~isempty(periods)
        freqs = 1./periods;
        x = [freqs;freqs];
        y = yrange'*ones(size(periods));
        hold on;
        plot(x,y,'g');
      end
      % Display line widths
      Yvals = linspace(yrange(2),0,length(lfreq)+2);
      hold on;
      errorbar(mfreq,Yvals(2:end-1),dfreq,'horizontal','og');
      hold off;
      grid on;

      title(sprintf('%s', base));
      xlabel('cm');
    end
  end
end
