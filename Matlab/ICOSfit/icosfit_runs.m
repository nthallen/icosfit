classdef icosfit_runs < handle
  % I want this class to do several things
  % 1: Organize data from multiple runs into an object
  % 2: Render the data in useful ways allowing user to focus on
  %   a: Specific values of inputs to the fit
  %   b: Specific fit paramters or other fit output
  % Strategy:
  %  Use menus, possibly with increment/decrement options
  %   input_parameters => values
  %   parameter => All of them (might be too long)
  %
  % Graphs:
  %   ax(1) overall errors relative to best fit vs epsilon2
  %   ax(2) parameter j values for selected input criteria I
  %   ax(3) parameter j differences between input criteria
  %  
  % To make this work, I need to have
  %   A set of run outputs
  %   An input criterion that distinguishes the runs, e.g.
  %     - values of epsilon2
  %     - successive baseline file optimizations
  % Overall, we would need to identify
  %   The input criterion
  %   Whether the values should be rendered linearly or logarithmically
  % For each run, we would need to identify
  %   The run directory
  %   The input criterion value
  %   A string representation of the input criterion
  properties
    survey % struct array containing: base, value, text
    criterion
    units % units for the input criterion (if any)
    scale % log or linear
    scannum
    n_scans % length(scannum)
    svals % sorted input criterion values
    ivals % sorted indices of survey elements
    n_vals % length(vals)
    params % cell array of parameter names sorted alphabetically
    n_params % length(params)

    % fit results
    use_times % boolean
    rtimes % real user and sys time vs epsilon2 values
    chi2 % n_scans x n_vals
    iterations % n_scans x n_vals
    nfev % number of function evaluations: n_scans x n_vals
    P % parameter values n_scans x n_vals x n_params
    % fixed % n_params x 1
    
    % figure stuff
    f % The current figure. Should be empty if none
    ax % The axes of f
    inp_idx % The index of the currently displayed input criterion
    param_idx % The index of the currently displayed parameter
  end
  methods
    function self = icosfit_runs(varargin)
      % Either need to pass in data or specify that collection
      % ieps2 = icosfit_runs(); % probably useless except internally
      % ieps2 = icosfit_runs(varargin);
      %   survey => struct array containing: base, value, text
      %   criterion => string describing the input criterion
      %   units => string defining input criterion units
      self.survey = [];
      self.criterion = 'unknown';
      self.units = '';
      self.scale = 'linear';
      for i = 1:2:length(varargin)-1
        arg = convertCharsToStrings(varargin{i});
        if ~isStringScalar(arg)
          error('Invalid input type for argument %d', i);
        elseif arg == "survey"
          self.survey = varargin{i+1};
        elseif arg == "criterion"
          self.criterion = varargin{i+1};
        elseif arg == "units"
          self.units = varargin{i+1};
        elseif arg == "scale"
          self.scale = varargin{i+1};
        else
          error('Unrecognized input at position %d', i);
        end
      end
      self.f = [];
      self.param_idx = 0;
      self.inp_idx = 0;
      [self.svals, self.ivals] = sort([self.survey.value]);
      self.n_vals = length(self.svals);
      %%
      % First need to build the list of fit parameters
      % For each parameter, need to identify the associated column for
      % each run. Want to cache this info, but don't need to store it
      % in the object
      cache(self.n_vals) = struct('S',[],'p_cols',[]);
      params = [];
      for i=1:self.n_vals
        base = self.survey(self.ivals(i)).base;
        S = ICOS_setup(base);
        cache(i).S = S;
        Sparams = regexprep(S.output_cols(S.p_cols),'^.* Value: ','');
        Spfix = regexprep(Sparams,'\[','_');
        Spfix = regexprep(Spfix,'\]','');
        for j=1:length(Sparams)
          if ~isfield(params, Spfix{j})
            p_cols = zeros(self.n_vals,1);
            p_cols(i) = S.p_cols(j);
            params.(Spfix{j}) = ...
              struct('name', Sparams{j}, 'p_cols', p_cols, ...
                'floats', any(S.fitdata(:,S.float_cols(j))));
          else
            params.(Spfix{j}).p_cols(i) = S.p_cols(j);
            if ~params.(Spfix{j}).floats
              params.(Spfix{j}).floats = any(S.fitdata(:,S.float_cols(j)));
            end
          end
        end
      end
      
      % Determine which params are floating and sort them
      all_p = fields(params);
      floats(length(all_p)) = false;
      for j = 1:length(all_p)
        floats(j) = params.(all_p{j}).floats;
      end
      self.n_params = sum(floats);
      [self.params,Iparams] = sort(all_p(floats));
      
      % Now build the following matrices:
      %   chi2(ncans,self.n_vals)
      %   iterations(nscans,self.n_vals)
      %   rtimes(self.n_vals,3)
      self.chi2 = [];
      for i=1:self.n_vals
        S = cache(i).S;
        if isempty(self.chi2)
          self.n_scans = length(S.scannum);
          self.chi2 = zeros(self.n_scans,self.n_vals);
          self.iterations = zeros(self.n_scans,self.n_vals);
          self.nfev = zeros(self.n_scans,self.n_vals);
          self.scannum = S.scannum;
          % param_cols = S.p_cols(Iparams);
          self.P = NaN*zeros(self.n_scans, self.n_vals, self.n_params);
          % would be good to not parameters that are unaffected
          % by epsilon2 (i.e. fixed)
          self.use_times = isfile([base '/icosfit.time.dat']);
          if self.use_times
            self.rtimes = zeros(3,self.n_vals);
          else
            self.rtimes = [];
          end
        end
        self.chi2(:,i) = sqrt(S.chi2);
        self.iterations(:,i) = S.info(:,5);
        self.nfev(:,i) = S.info(:,7);
        if self.use_times
          rtimes_in = load([base '/icosfit.time.dat'])/self.n_scans;
          rtimes_in = rtimes_in(:,1)*60 + rtimes_in(:,2);
          self.rtimes(:,i) = rtimes_in;
        end
        for j=1:self.n_params
          col = params.(self.params{j}).p_cols(i);
          if col > 0
            self.P(:,i,j) = S.fitdata(:,col);
          end
        end
      end
    end
    
    function show_times(self)
      figure;
      if self.use_times
        ax = [nsubplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3)];
        ut = 1;
        plot(ax(1),self.svals,self.rtimes');
        set(ax(1),'XTickLabels',[],'YAxisLocation','Left');
        xlabel(self.units);
        ylabel(ax(1),'Mean Seconds/Scan');
        legend(ax(1),'real','user','sys');
      else
        ax = [nsubplot(2,1,1) nsubplot(2,1,2)];
        ut = 0;
      end
      
      plot(ax(1+ut),self.svals,self.iterations','-*');
      ylabel(ax(1+ut),'Iterations');
      set(ax(1+ut),'XTickLabels',[],'YAxisLocation','Right');
      
      plot(ax(2+ut),self.svals,self.nfev','-*');
      xlabel(ax(2+ut), '\epsilon_2');
      ylabel(ax(2+ut), 'nfev');
      
      title(ax(1),sprintf('Fit Time vs %s', self.criterion));
      set(ax,'XScale',self.scale);
      linkaxes(ax,'x');
    end
    
    function show_params(self, inp_idx, param_idx)
      if isempty(self.f) || ~isgraphics(self.f)
        self.f = figure;
        self.ax = [subplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3)];
        self.inp_idx = 0;
        self.param_idx = 0;
        me = uimenu(gcf,'Text',self.criterion);
        for i=2:self.n_vals
          uimenu(me,'Text',self.survey(self.ivals(i)).text, ...
            'Callback', @(src,evt)pfcb(self,src,evt,i,0));
        end
        me = uimenu(gcf,'Text','Parameter');
        for i=1:self.n_params
          uimenu(me,'Text', self.params{i}, ...
            'Callback', @(src,evt)pfcb(self,src,evt,0,i));
        end
        uimenu(me,'Text', 'chi2', ...
          'Callback', @(src,evt)pfcb(self,src,evt,0,-1));
        uimenu(me,'Text', 'iterations', ...
          'Callback', @(src,evt)pfcb(self,src,evt,0,-2));
        uimenu(me,'Text', 'nfev', ...
          'Callback', @(src,evt)pfcb(self,src,evt,0,-3));
      end
      lax = self.ax;
      if nargin >= 2 && inp_idx >= 1
        self.inp_idx = inp_idx;
      end
      if self.inp_idx < 1
        self.inp_idx = self.n_vals;
      end
      if nargin >= 3 && param_idx ~= 0
        self.param_idx = param_idx;
      end
      if self.param_idx == 0
        self.param_idx = 1;
      end
      if self.param_idx > 0
        pname = self.params{self.param_idx};
        NN = self.P(:,:,self.param_idx);
      else
        if self.param_idx == -1
          pname = 'chi2';
        elseif self.param_idx == -2
          pname = 'iterations';
        else
          pname = 'nfev';
        end
        NN = self.(pname);
      end
      pname = strrep(pname, '_', '\_');
      refcols = find(any(~isnan(NN)));
      if isempty(refcols)
        refcol = 1;
      else
        refcol = refcols(1);
        if (self.inp_idx <= refcol || all(isnan(NN(:,self.inp_idx)))) && length(refcols) > 1
          self.inp_idx = refcols(2);
        end
      end
      val0txt = self.survey(self.ivals(refcol)).text;
      valtxt = self.survey(self.ivals(self.inp_idx)).text;
      NN0 = NN(:,refcol)*ones(1,self.n_vals);
      dNN = NN - NN0;
      errorbar(lax(1),self.svals,mean(dNN),std(dNN),'-*');
      set(lax(1),'XScale',self.scale,'XTick',self.svals,'XTickLabel',{ self.survey.text } );
      title(lax(1),sprintf('%s vs %s',pname,self.criterion));
      xlabel(lax(1),self.units);
      ylabel(lax(1),sprintf('\\Delta %s',pname));
      
      plot(lax(2),self.scannum,NN(:,[refcol self.inp_idx]));
      title(lax(2),sprintf('Parameter %s with %s = %s',pname,self.criterion, valtxt));
      ylabel(lax(2),sprintf('%s value',pname));
      legend(lax(2),val0txt, valtxt);
      set(lax(2),'XTickLabels',[]);
      
      plot(lax(3),self.scannum,dNN(:,self.inp_idx),'-*');
      set(lax(3),'YAxisLocation','Right');
      ylabel(lax(3),sprintf('\\Delta %s', pname));
      xlabel(lax(3),'Scan Number');
      linkaxes(lax(2:3),'x');
      shg;
    end
    
    function pfcb(self,~,~, inp_idx, param_idx)
      self.show_params(inp_idx, param_idx);
    end
  end
end
