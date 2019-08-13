function S = isovals( isos, field )
% S = isovals(isos,field);
% returns the elements of the Isotope table
% isos is a vector of isotopomer numbers ala hitran
% field is one of name, text, abundance, weight, multiplier, unit, precision.

global ISO_DEFS

if isempty(ISO_DEFS)
  add_iso( 10, 'H_2O', '  H2O  ', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 11, 'H_2O', '  H2O  ', 0.997317, 18.010565, 1e6, 'ppm', 0.1 );
  add_iso( 12, 'H_2{}^{18}O', ' H218O ', 0.00199983, 20.014811, 1e9, 'ppb', 0.1);
  add_iso( 13, 'H_2{}^{17}O', ' H217O ', 0.000372, 19.01478, 1e9, 'ppb', 0.1 );
  add_iso( 14, 'HDO', '  HDO  ', 0.00031069, 19.01674, 1e9, 'ppb', 0.1 );
  add_iso( 15, 'HD^{18}O', ' HD18O ', 0.000000623003, 21.020985, 1e9, 'ppb', 0.1 );
  add_iso( 16, 'HD^{17}O', ' HD17O ', 0.000000115853, 20.020956, 1e9, 'ppb', 0.1 );
  add_iso( 20, 'CO_2', '  CO2  ', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 21, 'CO_2', '  CO2  ', .984200, 44, 1e6, 'ppm', 0.1 );
  add_iso( 22, '^{13}CO_2', '  13CO2  ', .011060, 45, 1e6, 'ppm', 0.1 );
  add_iso( 23, 'CO^{18}O', '  CO18O  ', .003947, 46, 1e6, 'ppm', 0.1 );
  add_iso( 24, 'CO^{17}O', '  CO17O  ', .000734, 45, 1e6, 'ppm', 0.1 );
  add_iso( 30, 'O_3', '  O3   ', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 31, 'O_3', '  O3   ', 0.992901, 48, 1e9, 'ppb', 0.1 );
  add_iso( 40, 'N_2O', '  N2O  ', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 41, 'N_2O', '  N2O  ', .990333E+00, 44, 1e6, 'ppm', 0.1 );
  add_iso( 42, 'N^{15}NO', '  N15NO  ', .0036409E+00, 45, 1e6, 'ppm', 0.1 );
  add_iso( 43, '^{15}NNO', '  15NNO  ', .0036409E+00, 45, 1e6, 'ppm', 0.1 );
  add_iso( 44, 'N_2^{18}O', '  N218O  ', .00198582E+00, 46, 1e6, 'ppm', 0.1 );
  add_iso( 45, 'N_2^{17}O', '  N217O  ', .000369E+00, 45, 1e6, 'ppm', 0.1 );
  add_iso( 50, 'CO','CO', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 60, 'CH_4', '  CH4  ', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 61, 'CH_4', '  CH4  ', 0.98827, 16, 1e6, 'ppm', 0.1 );
  add_iso( 62, '^{13}CH_4', '13CH4', 0.011103100000, 17.034655, 1e6, 'ppm', 0.1 );
  add_iso( 63, '^{12}CH_3D', '12CH3D', 0.000615751000, 17.037476, 1e6, 'ppm', 0.1 );
  add_iso( 70, 'O2','O2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 80, 'NO','NO', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 81, 'NO','NO', 0.993974, 29.997990, 1e6, 'ppm', 0.1 );
  add_iso( 90, 'SO2','SO2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 100, 'NO_2','NO2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 101, 'NO_2','NO2', 0.991616, 45.992905, 1e6, 'ppm', 0.1 );
  add_iso( 110, 'NH3','NH3', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 120, 'HNO3','HNO3', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 130, 'OH','OH', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 131, 'OH','OH', 0.997473, 17.002741, 1e6, 'ppm', 0.1 );
  add_iso( 140, 'HF','HF', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 150, 'HCl','HCl', 1.0, 35.976677, 1e9, 'ppt', 0.1 );
  add_iso( 151, 'H{}^{35}Cl','H35Cl', 0.757587, 35.976677, 1e9, 'ppt', 0.1 );
  add_iso( 152, 'H{}^{37}Cl','H37Cl', 0.242257, 37.973728, 1e9, 'ppt', 0.1 );
  add_iso( 153, 'D{}^{35}Cl','D35Cl', 0.00018005, 36.983, 1e9, 'ppt', 0.1 );
  add_iso( 154, 'D{}^{37}Cl','D37Cl', 0.000037735, 38.98, 1e9, 'ppt', 0.1 );
  add_iso( 160, 'HBr','HBr', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 170, 'HI','HI', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 180, 'ClO','ClO', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 190, 'OCS','OCS', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 200, 'H2CO','H2CO', 1.0, 30, 1e9, 'ppb', 0.1 );
  add_iso( 201, 'H2CO','H2CO', 0.986237, 30.010565, 1e9, 'ppb', 0.1 );
  add_iso( 202, 'H2^{13}CO','H213CO', 0.0110802, 31.013920, 1e9, 'ppb', 0.1 );
  add_iso( 203, 'H2C^{18}O','H2C18O', 0.00197761, 32.014812, 1e9, 'ppb', 0.1 );
  add_iso( 210, 'HOCl','HOCl', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 220, 'N2','N2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 230, 'HCN','HCN', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 240, 'CH3Cl','CH3Cl', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 250, 'H2O2','H2O2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 260, 'C2H2','C2H2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 270, 'C2H6','C2H6', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 280, 'PH3','PH3', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 290, 'COF2','COF2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 300, 'SF6','SF6', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 310, 'H2S','H2S', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 320, 'HCOOH','HCOOH', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 330, 'HO2','HO2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 340, 'O','O', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 350, 'ClONO2','ClONO2', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 360, 'NO+','NO+', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 370, 'HOBr','HOBr', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 380, 'C2H4','C2H4', 1.0, 0, 1e6, 'ppm', 0.1 );
  add_iso( 390, 'CH3OH','CH3OH', 1.0, 0, 1e6, 'ppm', 0.1 );
end

if size(isos,1) > 1
  isos = isos';
end
ids = [ ISO_DEFS.id ];
idno = interp1(ids, 1:length(ids), isos, 'nearest' );
unmatched = find(isnan(idno));
matched = find(~isnan(idno));
unmatched = [ unmatched find( ids(idno(matched)) ~= isos(matched) ) ];
idno(unmatched) = 1;
if nargin >= 2 && strcmp( field, 'name')
  S = { ISO_DEFS(idno).name }';
  for i = unmatched
    mol = floor(isos(i)/10)*10;
    molid = find(ids == mol);
    if isempty(molid)
      S{i} = sprintf('iso %d',isos(i));
    else
      S{i} = sprintf('%s[%d]', ISO_DEFS(molid(1)).name, isos(i)-molid(1));
    end
  end
  return;
end

if ~isempty(unmatched)
  error('Unable to identify isotope: %d\n', isos(unmatched));
end

if nargin < 2
  S = ISO_DEFS(idno);
elseif strcmp( field, 'name' )
  S = { ISO_DEFS(idno).name }';
elseif strcmp( field, 'text' )
  S = { ISO_DEFS(idno).text }';
elseif strcmp( field, 'abundance' )
  S = [ ISO_DEFS(idno).abundance ]';
elseif strcmp( field, 'weight' )
  S = [ ISO_DEFS(idno).weight ]';
elseif strcmp( field, 'multiplier' )
  S = [ ISO_DEFS(idno).multiplier ]';
  elseif strcmp( field, 'unit' )
  S = { ISO_DEFS(idno).unit }';
  elseif strcmp( field, 'precision' )
  S = [ ISO_DEFS(idno).precision ]';
else
  error( [ 'Unrecognized field: ' field ]);
end

return
end

function add_iso( id, name, text, abundance, weight, multiplier, unit, precision )

global ISO_DEFS;
s = struct( 'id', id, 'name', name, 'text', text, 'abundance', abundance, 'weight', weight, 'multiplier', multiplier, 'unit', unit, 'precision', precision );
if ~isempty(ISO_DEFS)
  ISO_DEFS = [ ISO_DEFS; s ];
else
  ISO_DEFS = s;
end
return
end
