function Qfact = load_QT(T, iso)
% Qfact = load_QT(T, iso);
% T is a column vector in Kelvin
% iso is a row of HITRAN isotopologue numbers
assert(size(T,2)==1);
assert(size(iso,1)==1);
DELIMITER = ' ';
HEADERLINES = 3;
ST = dbstack('-completenames');
QTpath = fileparts(ST(1).file);
Tref = 296.;
Qfact = zeros(length(T),length(iso));
for i = 1:length(iso)
    QTfile = sprintf('%s%cQT%cQT_%d.dat', QTpath, filesep, filesep, iso(i));
    if exist(QTfile,'file')
        QT = importdata(QTfile, DELIMITER, HEADERLINES);
        iref = find(QT.data(:,1) == Tref,1);
        if isempty(iref)
            error('Tref not present in input file %s', QTfile);
        end
        Qfact(:,i) = QT.data(iref,2) ./ ...
            interp1(QT.data(:,1),QT.data(:,2),T,'linear');
    else
        warning('ICOSfit:load_QT:NoFile', ...
            sprintf('Unable to locate QT table for isotopologue %d', ...
                iso(i)));
        Qfact(:,i) = (Tref./T).^1.5;
    end
end
