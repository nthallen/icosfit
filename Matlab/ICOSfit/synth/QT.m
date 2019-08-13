classdef QT < handle
  % Q = QT;
  % Qfact = Q.QTratio(T, iso);
  % where T is a column of temperatures in Kelvin,
  % iso is a row of isotopologue numbers

  % QT is derived from handle in order to hold state without explicit
  % reassignment. We hold onto the QT tables in order to avoid
  % reloading the files on every call.
  properties
    tables % struct of QT tables
    QTref % struct of Q(Tref) values
    QTpath % directory
  end
  properties ( Constant = true )
    Tref = 296.;
  end
  
  methods
    function qt = QT
      ST = dbstack('-completenames');
      qt.QTpath = [ fileparts(ST(1).file) filesep '..' filesep 'QT' filesep ];
    end
    
    function Qfact = QTratio(qt,T,iso)
      assert(iscolumn(T));
      assert(isrow(iso));
      Qfact = zeros(length(T),length(iso));
      for i = 1:length(iso)
        QTname = sprintf('QT_%d', iso(i));
        if ~isfield(qt.tables, QTname)
          QTfile = [qt.QTpath QTname '.dat'];
          if exist(QTfile,'file')
            DELIMITER = ' ';
            HEADERLINES = 3;
            QTF = importdata(QTfile, DELIMITER, HEADERLINES);
            iref = find(QTF.data(:,1) == qt.Tref,1);
            if isempty(iref)
              error('Tref not present in input file %s', QTfile);
            end
            qt.tables.(QTname) = QTF.data;
            qt.QTref.(QTname) = QTF.data(iref,2);
          else
            warning('ICOSfit:load_QT:NoFile', ...
              'Unable to locate QT table for isotopologue %d', ...
              iso(i));
            qt.tables.(QTname) = [];
          end
        end
        if isempty(qt.tables.(QTname))
          Qfact(:,i) = (qt.Tref./T).^1.5;
        else
          Qfact(:,i) = qt.QTref.(QTname) ./ ...
            interp1(qt.tables.(QTname)(:,1),qt.tables.(QTname)(:,2), ...
            T,'linear');
        end
      end
            
    end
  end
end