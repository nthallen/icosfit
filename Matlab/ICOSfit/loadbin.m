function [fe, hdr] = loadbin( ifile )
% fe = loadbin( ifile );
% [fe, hdr] = loadbin(ifile);
% Reports data written in the format of the Anderson Group's
% SSP board drivers.
%
% Returns an empty matrix if the file cannot be read.
% 
% This version supports two different file formats.
% The first format consists of two uint32 values defining the number of
% rows and columns followed by the data as 32-bit floats in
% column order.
%
% The second format includes all the information from the raw SSP
% records. This header consists of 7 32-bit words. The first 6 match
% the first six words of the SSP header, and the 7th word is the
% status word that is reported at the end of the SSP record.
%
% When the 'hdr' output is requested, the header values are
% decoded into mnemonic fields of the hdr struct.
fid = fopen(ifile, 'r');
format = -1;
hdr_out = [];
if fid > 0
  try
    [ data, count ] = fread(fid,2,'uint32',0,'l');
    if count ~= 2
        error('MATLAB:huarp:readerr','Unable to read header');
    end
    if data(1) == 6
        % early version of the SSP format
        format = 0;
    elseif data(1) == hex2dec('10006')
        format = 1;
    end
    if format >= 0 && data(2) > 255
        datadim = ...
          [ bitand(data(2),hex2dec('FFFF0000'))/hex2dec('10000') ...
              bitand(data(2),255) ];
        hdr_out.NF = bitand(data(2),hex2dec('FF00'))/256;
        [data, count] = fread(fid,10,'uint16',0,'l');
        if count ~= 10
            error('MATLAB:huarp:readerr','Unable to read header');
        end
        if nargout >= 2
            hdr_out.NCoadd = data(1);
            hdr_out.NAvg = data(2);
            hdr_out.NSkL = data(3);
            hdr_out.NSkP = data(4);
            hdr_out.SerialNum = data(5) + data(6)*65536;
            hdr_out.T_HtSink = data(7);
            hdr_out.T_FPGA = data(8);
            hdr_out.Status = data(9);
        end
    else
        datadim = data';
    end
    fe = fread(fid,datadim,'float32',0,'l');
  catch
    fe = [];
  end
  fclose(fid);
else
  fe = [];
end
if nargout >= 2
    hdr = hdr_out;
end