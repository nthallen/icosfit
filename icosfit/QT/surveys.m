files = dir('QT*.dat');
nfiles = length(files);
legends = cell(nfiles,1);
colornum = [ 1 2 4 6 ];
colors = 'rgbc';
for i=1:nfiles
    filename = files(i).name;
    isonumstr = filename(4:end-4);
    isonum = str2num(isonumstr);
    molnum = str2num(isonumstr(1:end-1));
    coloridx = find(colornum == molnum, 1);
    [T,QTcorr] = survey(filename);
    iso = isovals(isonum);
    legends{i} = iso.name;
    plot(T-273.15,QTcorr*100,colors(coloridx));
    hold on;
end
legend(legends,'Location','SouthEast');
xlabel('Celcius');
ylabel('Percent Correction');
title('Correction from (T_{ref}/T)^{1.5}');
hold off;
