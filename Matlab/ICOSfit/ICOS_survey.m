classdef ICOS_survey < handle
  properties
    model % the modeled spectrum: includes trans and nu (was YData and XData)
    data = struct(...
            'range', [], ...
            'icos', [], ...
            'nu', [], ...
            'dnu', [], ...
            'nu0', []);
    % range: The starting and ending scan numbers
    % icos: The coadded scans
    % nu: The relative wavenumbers
    % dnu: Value added to nu that places the scan relative to the model
    %   If zero, this region has not yet been placed
    % nu0: Last X position select in S.position. This will be treated
    %   as a fixed point when scaling the etalon FSR in S.calibrat
    fig % The figure where we are drawing
    ax % The axis where we are drawing
    X % The sample number range
    fsr_correction
  end
  
  methods
    function S = ICOS_survey(varargin)
      % S = survey([options]);
      % Initializes the survey object, loads the scan data and
      % draws the initial view with the first scan field
      ISopts.settle = 3;
      ISopts.wv = [];
      ISopts.rng = [];
      for i=1:2:length(varargin)-1
        if isfield(ISopts, varargin{i})
          ISopts.(varargin{i}) = varargin{i+1};
        end
      end
      load H2Ospectrum.mat
      S.model.trans = L.YData;
      S.model.nu = L.XData;
      S.fig = figure;
      S.ax = gca;
      S.X = 200:1050;
      if isempty(ISopts.wv)
        [wv,rng] = waves_used;
      else
        wv = ISopts.wv;
        rng = ISopts.rng;
      end
      nrng = length(rng);
      allscans = listscans;
      nregions = 0;
      S.fsr_correction = 1;
      for i=1:nrng
        for j=1:size(rng(i).ranges,1)
          nregions = nregions + 1;
          title(S.ax,sprintf('%s: Loading region %d %s', getrun, nregions, ...
            strrep(wv(i).Name,'_','\_')));
          drawnow;
          range = rng(i).ranges(j,:);
          range(1) = range(1)+ISopts.settle;
          iscans = range(1):range(2);
          oscans = interp1(allscans,allscans,iscans,'nearest');
          scans = oscans(iscans==oscans);
          icoss = loadscans(scans);
          icos = mean(icoss,2);
          nu = get_nu(range(1),S.X);
          S.data(nregions) = struct(...
            'range', range, ...
            'icos', icos, ...
            'nu', nu, ...
            'dnu', 0, ...
            'nu0', []);
        end
      end
      S.display1;
    end
    
    function display1(S)
      % S.display1;
      % Draws the transmission plot with already positioned scans
      if isempty(S.fig) || ~ishandle(S.fig)
        S.fig = figure;
        S.ax = gca;
      end
      hold(S.ax,'off');
      plot(S.ax, S.model.nu, S.model.trans);
      xlabel(S.ax,'cm^{-1}');
      ylabel(S.ax,'Transmission');
      title(S.ax,'Initial display');
      set(S.ax,'Xdir','reverse');
      modelrng = [min(S.model.trans),max(S.model.trans)];
      tgtrng = modelrng-diff(modelrng);
      nregions = length(S.data);
      hold(S.ax,'on');
      for i = 1:nregions
        if S.data(i).dnu > 0
          raw = S.data(i).icos;
          raw = raw(S.X);
          drng = [min(raw),max(raw)];
          tgticos = interp1(drng,tgtrng,raw);
          plot(S.ax,(S.data(i).nu-S.data(i).nu0)*S.fsr_correction+ ...
            S.data(i).dnu,tgticos,'b');
        end
      end
      hold(S.ax,'off');
    end
     
    function display2(S)
      % S.display2;
      % Draws the transmission plot with already positioned scans
      if isempty(S.fig) || ~ishandle(S.fig)
        S.fig = figure;
      end
      clf(S.fig);
      ax1 = nsubplot(3,1,1);
      S.ax = nsubplot(3,1,[3,2]);
      % hold(S.ax,'off');
      plot(ax1, S.model.nu, S.model.trans);
      xlabel(S.ax,'cm^{-1}');
      title(ax1,getrun);
      ylabel(ax1,'Transmission');
      set(ax1,'Xticklabel',[],'yaxislocation','right','Xdir','reverse');
      nregions = length(S.data);
      for i = 1:nregions
        if S.data(i).dnu > 0
          raw = S.data(i).icos;
          raw = raw(S.X);
          plot(S.ax,(S.data(i).nu-S.data(i).nu0) * S.fsr_correction + ...
            S.data(i).dnu,raw,'b');
          hold(S.ax,'on');
        end
      end
      set(S.ax,'Xdir','reverse');
      xlabel(S.ax,'cm^{-1}');
      ylabel(S.ax,'SSP lsbs');
      hold(S.ax,'off');
      linkaxes([ax1 S.ax],'x');
      grid(ax1,'on');
      grid(S.ax,'on');
    end
   
    function position(S, region)
      if region > length(S.data)
        error('region out of range');
      end
      dnu = S.data(region).dnu;
      S.data(region).dnu = 0;
      S.display1;
      if dnu == 0
        dnu = mean(S.model.nu)-mean(S.data(region).nu);
      end
      if isempty(S.data(region).nu0)
        S.data(region).nu0 = mean(S.data(region).nu);
      end
      S.data(region).dnu = dnu;
      modelrng = [min(S.model.trans),max(S.model.trans)];
      tgtrng = modelrng-diff(modelrng);
      raw = S.data(region).icos;
      raw = raw(S.X);
      drng = [min(raw),max(raw)];
      tgticos = interp1(drng,tgtrng,raw);
      nulims = [min(S.data(region).nu),max(S.data(region).nu)]- ...
        S.data(region).nu0;
      hold(S.ax,'on');
      h1 = plot(S.ax,(S.data(region).nu-S.data(region).nu0) * ...
        S.fsr_correction+S.data(region).dnu,tgticos,'r');
      y = [tgtrng(1),100];
      h3 = plot(S.ax,dnu*[1,1],y,'k');
      set(gca,'xlim',(nulims+diff(nulims)*.05*[-1,1])+dnu);
      [x0,~] = ginput(1);
      h3.XData = x0*[1,1];
      S.data(region).nu0 = (x0 - S.data(region).dnu)/S.fsr_correction ...
        + S.data(region).nu0;
      S.data(region).dnu = x0;
      dnu = x0;
      nulims = [min(S.data(region).nu),max(S.data(region).nu)]- ...
        S.data(region).nu0;
      while 1
        set(gca,'xlim',nulims+diff(nulims)*.05*[-1,1]+dnu);
        [x,~] = ginput(1);
        if isempty(x)
          break;
        end
        dx = x-x0;
        h1.XData = h1.XData+dx;
        h3.XData = x*[1,1];
        x0 = x;
        dnu = dnu + dx;
        S.data(region).dnu = dnu;
      end
    end
    
    function calibrate(S, region)
      % S.calibrate(region)
      % Allow scaling of FSR to span across multiple lines
      if region > length(S.data)
        error('region out of range');
      end
      dnu = S.data(region).dnu;
      S.data(region).dnu = 0;
      S.display1;
      if dnu == 0
        dnu = mean(S.model.nu)-mean(S.data(region).nu);
      end
      S.data(region).dnu = dnu;
      modelrng = [min(S.model.trans),max(S.model.trans)];
      tgtrng = modelrng-diff(modelrng);
      raw = S.data(region).icos;
      raw = raw(S.X);
      drng = [min(raw),max(raw)];
      tgticos = interp1(drng,tgtrng,raw);
      nulims = [min(S.data(region).nu),max(S.data(region).nu)]- ...
        S.data(region).nu0;
      hold(S.ax,'on');
      h1 = plot(S.ax,(S.data(region).nu-S.data(region).nu0) * ...
        S.fsr_correction+S.data(region).dnu,tgticos,'r');
      y = [tgtrng(1),100];
      set(gca,'xlim',nulims+diff(nulims)*.05*[-1,1]+dnu);
      if isempty(S.data(region).nu0)
        [nu0,~] = ginput(1);
        S.data(region).nu0 = nu0 - S.data(region).dnu;
        S.data(region).dnu = nu0;
      else
        nu0 = S.data(region).dnu;
      end
      h3 = plot(S.ax,nu0*[1,1],y,'k'); % Vertical on fixed point
      [nu1,~] = ginput(1);
      h4 = plot(S.ax,nu1*[1,1],y,'g'); % Vertical on second line
      title(S.ax,sprintf('FSR correction: %.4f', S.fsr_correction));
      while 1
        % set(gca,'xlim',nulims+diff(nulims)*.05*[-1,1]+dnu);
        [nu2,~] = ginput(1);
        if isempty(nu2)
          break;
        end
        dx = nu2-nu1;
        new_fsr_correction = S.fsr_correction*(nu2-nu0)/(nu1-nu0);
        h1.XData = (h1.XData - dnu)* ...
          new_fsr_correction/S.fsr_correction + dnu;
        h4.XData = (h4.XData-nu0)*new_fsr_correction/S.fsr_correction ...
          + nu0;
        title(S.ax,sprintf('FSR correction: %.4f, now %.4f', ...
          S.fsr_correction, new_fsr_correction));
        % h3.XData = x*[1,1];
        %x0 = x;
        %dnu = dnu + dx;
        %S.data(region).dnu = dnu;
      end
      S.fsr_correction = new_fsr_correction;
    end
  end
end
