function save_waveform_params( waveform, varargin )
% save_waveform_params( waveform, var1, var1_value, var2, ...
%                                var2_value, ... );
% The waveform parameters are saved in the current directory.
% This file can be manually moved to the parent or grandparent directory if
% the parameters apply to more runs.
%
% Parameters currently in use include:
% matchline:
%   'holdoff', 4e-4
%   'SignalRegion', [round(wv.TzSamples + holdoff*SampleRate): ...
%                          wv.NetSamples - wv.TzSamples - 1]
% etln_fit:
%   'prefilterwidth', 5
%   'X', [10.2817    48.3    0   -2.6921  .1645924   -3.7796   .0689779 ]
%   'SignalRegion', [wv.TzSamples+100:wv.NetSamples-wv.TzSamples-20]
%   'threshold', .07
%   'TauLims', [.05 .01 1.0] (min, spacing, max)
%  (etln_fit7 used to use 'range' instead of 'SignalRegion')
%
% sensitivity:
%   'holdoff', 4e-4
%   'SignalRegion', []
%
% waves_editor:
%   'RampRegions'
%   'CurRamp'
fname = findinpath( [ waveform '_etln.mat' ], { '.', '..', '../..' } );
if ~isempty(fname)
  fprintf(1, 'Reading waveform configuration from %s\n', fname );
  vals = load(fname);
else
  vals = [];
end
for i = 2:2:length(varargin)
  fld = varargin{i-1};
  vals.(fld) = varargin{i};
end
if i < length(varargin)
  error('odd number of arguments');
end
save( [waveform '_etln.mat'], '-struct', 'vals' );
