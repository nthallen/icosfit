function eng2PT
%This is a generic eng to PT file conversion program.
%A specific program for each instrument/axis will need to be written.
%Probably best to put it into the axis directory.
% eng2PT
% Reads eng_1.mat and creates a specific PT.mat appropriate
% for use with the icosfit utilities.
E = load('eng_1.mat'); %for example hcieng_1.mat
E10 = load('eng_10.mat');
PT.TPT = E.Teng_1; %for example Thcieng_1
PT.ScanNum = E.SSP_Num; %for example SSP_C_Num
PT.QCLI_Wave = E.QCLI_Wave; %for example QCLI_C_Wave
PT.CellP = E10.CCelLP; %cell pressure (in Torr) to use for fit
PT.Tavg = 273.15 + (E10.CCel1T + E10.CCel2T)/2; %gas temp (in K) to use for fit
save PT.mat -STRUCT PT
