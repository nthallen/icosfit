function writebin(ofile, fe, hdr)
% writebin( ofile, fe );
% Writes the matrix fe to the file ofile in the
% standard binary format for ICOSfit.
% i 4 nrows
% i 4 ncols
% REPEAT ncols {
%   REPEAT nrows {
%     r 4 value
%   }
% }
%
% writebin(ofile, fe, hdr);
% Writes the matrix with the full SSP header info, where hdr
% is a struct containing the fields:
%  NF, NCoadd, NAvg, NSkL, NSkP, SerialNum, T_HtSink, T_FPGA, Status
fid = fopen(ofile, 'w');
if fid > 0
    if nargin < 3 || isempty(hdr)
        fwrite(fid, size(fe), 'integer*4' );
    else
        u16hdr = [ 6 1 size(fe,2)+hdr.NF*256 size(fe,1) ...
            hdr.NCoadd hdr.NAvg hdr.NSkL hdr.NSkP ...
            bitand(hdr.SerialNum,65535) floor(hdr.SerialNum/65536) ...
            hdr.T_HtSink hdr.T_FPGA ...
            bitand(hdr.Status,65535) floor(hdr.Status/65536) ];
        fwrite(fid, u16hdr, 'integer*2');
    end
    fwrite(fid, fe, 'real*4' );
    fclose(fid);
else
    error(['Error writing file: ' ofile ]);
end
