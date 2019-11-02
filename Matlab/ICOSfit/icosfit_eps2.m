classdef icosfit_eps2 < handle
  % I want this class to do several things
  % 1: Organize data from icosfit_survey into an object
  % 2: Render the data in useful ways allowing user to focus on
  %   a: Specific values of epsilon2
  %   b: Specific paramters
  % Strategy:
  %  Use menus, possibly with increment/decrement options
  %   eps2 => values
  %   parameter => All of them (might be too long)
  %
  % Graphs:
  %   ax(1) overall errors relative to best fit vs epsilon2
  %   ax(2) parameter j values for best fit and selected epsilon2
  %   ax(3) parameter j differences between epsilon2 and best fit
  % 3: Render other useful data:
  %   a: time/iterations/nfev vs epsilon2
  %  
  properties
    survey_base % defaults to ICOSout.survey
    scannum
    seps2 % sorted epsilon2 values
    n_scans % length(scannum)
    n_eps2 % length(seps2)
    params % cell array of parameter names sorted alphabetically
    n_params % length(params)

    % fit results
    rtimes % real user and sys time vs epsilon2 values
    chi2 % n_scans x n_eps2
    iterations % n_scans x n_eps2
    nfev % number of function evaluations: n_scans x n_eps2
    P % parameter values n_scans x n_eps2 x n_params
    fixed % n_params x 1
    
    % figure stuff
    f % The current figure. Should be empty if none
    ax % The axes of f
    eps2_idx % The index of the currently displayed eps2
    param_idx % The index of the currently displayed parameter
  end
  methods
    function self = icosfit_eps2(varargin)
      % Either need to pass in data or specify that collection
      % ieps2 = icosfit_eps2(); % probably useless except internally
      % ieps2 = icosfit_eps2('collect');
      % ieps2 = icosfit_eps2('survey_base', 'folder_name');
      collect = false;
      self.survey_base = 'ICOSout.survey';
      i = 1;
      while i <= length(varargin)
        arg = convertCharsToStrings(varargin{i});
        if ~isStringScalar(arg)
          error('Invalid input type for argument %d', i);
        elseif arg == "collect"
          collect = true;
          i = i+1;
        elseif arg == "survey_base"
          if i == length(varargin)
            error('survey_base without argument');
          end
          self.survey_base = varargin{i+1};
          i = i+2;
        else
          error('Unrecognized input at position %d', i);
        end
      end
      self.f = [];
      self.param_idx = 0;
      self.eps2_idx = 0;
      if collect
        D = dir([self.survey_base '/' self.survey_base '.*']);
        self.n_eps2 = size(D,1);
        eps2 = zeros(self.n_eps2,1);
        for i=1:self.n_eps2
          fname = D(i).name;
          parts = split(fname,'.');
          eps2(i) = str2double(parts{3});
        end
        [self.seps2,Ieps2] = sort(eps2);
        %%
        % Now build the following matrices:
        %   chi2(ncans,self.n_eps2)
        %   iterations(nscans,self.n_eps2)
        %   rtimes(self.n_eps2,3)
        self.chi2 = [];
        for i=1:self.n_eps2
          base = [ self.survey_base '/' D(Ieps2(i)).name];
          S = ICOS_setup(base);
          if isempty(self.chi2)
            self.n_scans = length(S.scannum);
            self.chi2 = zeros(self.n_scans,self.n_eps2);
            self.iterations = zeros(self.n_scans,self.n_eps2);
            self.nfev = zeros(self.n_scans,self.n_eps2);
            self.rtimes = zeros(3,self.n_eps2);
            self.scannum = S.scannum;
            params = regexprep(S.output_cols(S.p_cols),'^.* Value: ','');
            [self.params,Iparams] = sort(params);
            param_cols = S.p_cols(Iparams);
            self.n_params = length(param_cols);
            self.P = zeros(self.n_scans, self.n_eps2, self.n_params);
            % would be good to not parameters that are unaffected
            % by epsilon2 (i.e. fixed)
            self.fixed = false(self.n_params,1);
          end
          self.chi2(:,i) = sqrt(S.chi2);
          self.iterations(:,i) = S.info(:,5);
          self.nfev(:,i) = S.info(:,7);
          rtimes_in = load([base '/icosfit.time.dat'])/self.n_scans;
          rtimes_in = rtimes_in(:,1)*60 + rtimes_in(:,2);
          self.rtimes(:,i) = rtimes_in;
          for j=1:self.n_params
            self.P(:,i,j) = S.fitdata(:,param_cols(j));
          end
        end
        % check for fixed parameters
        for j=1:self.n_params
          P = self.P(:,:,j);
          P0 = P(:,1)*ones(1,self.n_eps2);
          self.fixed(j) = all(all(P==P0));
        end
      end
    end
    
    function show_times(self)
      figure;
      ax = [nsubplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3)];
      semilogx(ax(1),self.seps2,self.rtimes');
      set(ax(1),'XTickLabels',[],'YAxisLocation','Left');
      title(ax(1),'Fit Time vs \epsilon_2');
      xlabel('\epsilon_2');
      ylabel(ax(1),'Mean Seconds/Scan');
      legend(ax(1),'real','user','sys');
      
      semilogx(ax(2),self.seps2,self.iterations','-*');
      ylabel(ax(2),'Iterations');
      set(ax(2),'XTickLabels',[],'YAxisLocation','Right');
      
      semilogx(ax(3),self.seps2,self.nfev','-*');
      xlabel(ax(3), '\epsilon_2');
      ylabel(ax(3), 'nfev');
      
      linkaxes(ax,'x');
    end
    
    function show_params(self, eps2_idx, param_idx)
      if isempty(self.f) || ~isgraphics(self.f)
        self.f = figure;
        self.ax = [subplot(3,1,1) nsubplot(3,1,2) nsubplot(3,1,3)];
        self.eps2_idx = 0;
        self.param_idx = 0;
        me = uimenu(gcf,'Text','epsilon2');
        for i=2:self.n_eps2
          uimenu(me,'Text',sprintf('%.0e',self.seps2(i)), ...
            'Callback', @(src,evt)pfcb(self,src,evt,i,0));
        end
        me = uimenu(gcf,'Text','Parameter');
        for i=1:self.n_params
          if ~self.fixed(i)
            uimenu(me,'Text', self.params{i}, ...
              'Callback', @(src,evt)pfcb(self,src,evt,0,i));
          end
        end
        uimenu(me,'Text', 'chi2', ...
          'Callback', @(src,evt)pfcb(self,src,evt,0,-1));
        uimenu(me,'Text', 'iterations', ...
          'Callback', @(src,evt)pfcb(self,src,evt,0,-2));
        uimenu(me,'Text', 'nfev', ...
          'Callback', @(src,evt)pfcb(self,src,evt,0,-3));
      end
      lax = self.ax;
      if nargin >= 2 && eps2_idx >= 1
        self.eps2_idx = eps2_idx;
      end
      if self.eps2_idx < 1
        self.eps2_idx = self.n_eps2;
      end
      if nargin >= 3 && param_idx ~= 0
        self.param_idx = param_idx;
      end
      if self.param_idx == 0
        self.param_idx = find(~self.fixed,1);
      end
      eps20txt = sprintf('%.0e',self.seps2(1));
      eps2txt = sprintf('%.0e',self.seps2(self.eps2_idx));
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
      NN0 = NN(:,1)*ones(1,self.n_eps2);
      dNN = NN - NN0;
      errorbar(lax(1),self.seps2,mean(dNN),std(dNN),'-*');
      set(lax(1),'XScale','log');
      title(lax(1),sprintf('%s vs \\epsilon_2',pname));
      xlabel(lax(1),'\epsilon_2');
      ylabel(lax(1),sprintf('%s error',pname));
      
      plot(lax(2),self.scannum,NN(:,[1 self.eps2_idx]));
      title(lax(2),sprintf('Parameter %s \\epsilon_2 = %s',pname,eps2txt));
      ylabel(lax(2),sprintf('%s value',pname));
      legend(lax(2),eps20txt, eps2txt);
      set(lax(2),'XTickLabels',[]);
      
      plot(lax(3),self.scannum,dNN(:,self.eps2_idx),'-*');
      set(lax(3),'YAxisLocation','Right');
      ylabel(lax(3),sprintf('\\Delta %s', pname));
      linkaxes(lax(2:3),'x');
      shg;
    end
    
    function pfcb(self,~,~, eps2_idx, param_idx)
      self.show_params(eps2_idx, param_idx);
    end
  end
end
