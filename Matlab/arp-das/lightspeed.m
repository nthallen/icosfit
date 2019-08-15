function c = lightspeed( length, duration );
% c = lightspeed( [meters[, seconds]] );
% Returns the speed of light in cm/sec. For other units,
% either do the math yourself or pass in the length
% unit in meters and the time unit in seconds.
% Hence mph = lightspeed( 1609.3, 3600 );
if nargin < 2
  duration = 1; % sec
  if nargin < 1
    length = 1e-2; % cm
  end
end
c = 2.99792458e8 * duration/length;
