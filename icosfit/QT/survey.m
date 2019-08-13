function [T, QTcorr] = survey(fileToRead)
% [T,QTcorr] = survey(fileToRead)
DELIMITER = ' ';
HEADERLINES = 3;

% Import the file
newData = importdata(fileToRead, DELIMITER, HEADERLINES);
T = newData.data(:,1);
QT = newData.data(:,2);
i = find(T == 296,1);
if isempty(i)
    error('Tref not present in input file %s', fileToRead);
end
Qrat = QT(i)./QT;
Qrat_mdl = (296./T).^1.5;
QTcorr = Qrat./Qrat_mdl - 1;
% plot(T-273.15,Qrat./Qrat_mdl - 1);
