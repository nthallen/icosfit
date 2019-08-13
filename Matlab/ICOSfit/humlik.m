function K = HUMLIK( X, Y );
% K = HUMLIK( X, Y );
% X is an array, Y is the Voigt Parameter.
% K is the calculated Faddeeva function with relative error less than 10^(-4).
% by an algorithm of R.J.Wells
% Voigt shape for a line at position X0 with doppler width Gd and lorentz
% width Gl and strength S would be HUMLIK((X-X0)/Gd, Gl/Gd)*S/Gd

if length(Y(:)) > 1
  error( 'Y must be a scalar' );
end
if size(X,2) > 1
  error( 'X must be a column vector' );
end

% Constants
RRTPI = 0.56418958;                                                % 1/sqrt(pi)
Y0 = 1.5; Y0PY0 = Y0+Y0; Y0Q = Y0*Y0;               % for CPF12 algorithm
C = [ 1.0117281, -0.75197147, 0.012557727,  0.010022008, -0.00024206814, 0.00000050084806 ];
S = [ 1.393237, 0.23115241, -0.15535147,  0.0062183662, 0.000091908299, -0.00000062752596 ];
T = [ 0.31424038, 0.94778839, 1.5976826, 2.2795071, 3.0206370, 3.8897249 ];

% Local variables
% INTEGER I, J                                                      ! Loop variables
% INTEGER RG1, RG2, RG3                                             ! y polynomial flags
% REAL ABX, XQ, YQ, YRRTPI                                          ! |x|, x^2, y^2, y/sqrt(pi)
% REAL XLIM0, XLIM1, XLIM2, XLIM3, XLIM4                            ! |x| on region boundaries
% REAL A0, D0, D2, E0, E2, E4, H0, H2, H4, H6                       ! W4 temporary variables
% REAL P0, P2, P4, P6, P8, Z0, Z2, Z4, Z6, Z8
% REAL XP(0:5), XM(0:5), YP(0:5), YM(0:5)                           ! CPF12 temporary values
% REAL MQ(0:5), PQ(0:5), MF(0:5), PF(0:5)
% REAL D, YF, YPY0, YPY0Q  

%**** Start of executable code *****************************************

      YQ  = Y*Y;                                                        % y^2
      YRRTPI = Y*RRTPI;                                                 % y/sqrt(pi)
      K = zeros(size(X));

      if Y >= 70.55                                                     % All points
        K = YRRTPI ./ ( X.*X + YQ );
        %disp('Y>=70.55');
		return;
      end

      RG1 = 1;                                                          % Set flags
      RG2 = 1;
      RG3 = 1;

      XLIM0 = sqrt ( 15100.0 + Y*(40.0 - Y*3.6) );                      % y<70.55
      if ( Y >= 8.425 )
        XLIM1 = 0.0;
      else
        XLIM1 = sqrt ( 164.0 - Y*(4.3 + Y*1.8) );
      end
      XLIM2 = 6.8 - Y;
      XLIM3 = 2.4*Y;
      XLIM4 = 18.1*Y + 1.65;
      if ( Y <= 0.000001 )                                              % When y<10^-6
       XLIM1 = XLIM0;                                                   % avoid W4 algorithm
       XLIM2 = XLIM0;
      end
%.....
      ABX = abs(X);                                                     % |x|
	  XQ = ABX.*ABX;
	  Region0 = ABX >= XLIM0;
	  Region1 = ABX < XLIM0 & ABX >= XLIM1;
	  Region2 = ABX < XLIM1 & ABX > XLIM2;
	  Region3 = ABX < XLIM3;
	  CPF12 =   ABX >= XLIM3 & ABX <= XLIM2;
      
      if any(Region0)
        %disp('Region0');
        K(Region0) = YRRTPI ./ ( XQ(Region0) + YQ );
      end

      if any(Region1)                                                  % Humlicek W4 Region 1
        %disp('Region1');
        A0 = YQ + 0.5;                                                 % Region 1 y-dependents
        D0 = A0*A0;
        D2 = YQ + YQ - 1.0;
        D = RRTPI ./ (D0 + XQ(Region1).*(D2 + XQ(Region1)));
        K(Region1) = D*Y.*(A0 + XQ(Region1));
	  end

      if any(Region2)                                                   % Humlicek W4 Region 2 
        %disp('Region2');
        H0 =  0.5625 + YQ*(4.5 + YQ*(10.5 + YQ*(6.0 + YQ)));            % Region 2 y-dependents
		H2 = -4.5    + YQ*(9.0 + YQ*( 6.0 + YQ* 4.0));
		H4 = 10.5    - YQ*(6.0 - YQ*  6.0);
		H6 = -6.0    + YQ* 4.0;
		E0 =  1.875  + YQ*(8.25 + YQ*(5.5 + YQ));
		E2 =  5.25   + YQ*(1.0  + YQ* 3.0);
		E4 =  0.75*H6;
		XQR2 = XQ(Region2);
        D = RRTPI ./ (H0 + XQR2.*(H2 + XQR2.*(H4 + XQR2.*(H6 + XQR2))));
        K(Region2) = D*Y   .*(E0 + XQR2.*(E2 + XQR2.*(E4 + XQR2)));
	  end

      if any(Region3)                                                   % Humlicek W4 Region 3
        % Region 3 y-dependents
        %disp('Region3');
		Z0 = 272.1014     + Y*(1280.829 + Y*(2802.870 + Y*(3764.966 ...
		    + Y*(3447.629 + Y*(2256.981 + Y*(1074.409 + Y*(369.1989 ...
		    + Y*(88.26741 + Y*(13.39880 + Y)))))))));
		Z2 = 211.678      + Y*(902.3066 + Y*(1758.336 + Y*(2037.310 ...
						  + Y*(1549.675 + Y*(793.4273 + Y*(266.2987 ...
						  + Y*(53.59518 + Y*5.0)))))));
		Z4 = 78.86585     + Y*(308.1852 + Y*(497.3014 + Y*(479.2576 ...
						  + Y*(269.2916 + Y*(80.39278 + Y*10.0)))));
		Z6 = 22.03523     + Y*(55.02933 + Y*(92.75679 + Y*(53.59518 ...
						  + Y*10.0)));
		Z8 = 1.496460     + Y*(13.39880 + Y*5.0);
		P0 = 153.5168     + Y*(549.3954 + Y*(919.4955 + Y*(946.8970 ...
		    + Y*(662.8097 + Y*(328.2151 + Y*(115.3772 + Y*(27.93941 ...
						  + Y*(4.264678 + Y*0.3183291))))))));
		P2 = -34.16955    + Y*(-1.322256+ Y*(124.5975 + Y*(189.7730 ...
						  + Y*(139.4665 + Y*(56.81652 + Y*(12.79458 ...
						  + Y*1.2733163))))));
		P4 = 2.584042     + Y*(10.46332 + Y*(24.01655 + Y*(29.81482 ...
						  + Y*(12.79568 + Y*1.9099744))));
		P6 = -0.07272979  + Y*(0.9377051+ Y*(4.266322 + Y*1.273316));
		P8 = 0.0005480304 + Y*0.3183291;
		XQR3 = XQ(Region3);
        D = 1.7724538 ./ (Z0 + XQR3.*(Z2 + XQR3.*(Z4 + XQR3.*(Z6 + XQR3.*(Z8+XQR3)))));
        K(Region3) = D.*(P0 + XQR3.*(P2 + XQR3.*(P4 + XQR3.*(P6 + XQR3*P8))));
	  end

      if any(CPF12)                                                   % Humlicek CPF12 algorithm
        YPY0 = Y + Y0;
        YPY0Q = YPY0*YPY0;
        K(CPF12) = 0.0;
		XCPF12 = X(CPF12)*ones(size(T));
		Col12 = ones(sum(CPF12),1);
		TCPF12 = Col12*T;
		D = XCPF12 - TCPF12;
		MQ = D.*D;
        MF = 1.0 ./ (MQ + YPY0Q);
        XM = MF.*D;
        YM = MF.*YPY0;
        D = XCPF12 + TCPF12;
        PQ = D.*D;
        PF = 1.0 ./ (PQ + YPY0Q);
        XP = PF.*D;
        YP = PF*YPY0;

        RegionI = CPF12 & ABX <= XLIM4;
	    RegionII = CPF12 & ~RegionI;
        if any(RegionI)                                           % Humlicek CPF12 Region I
          %disp('RegionI');
          RI = ABX(CPF12) <= XLIM4;
		  ColRI = ones(sum(RI),1);
		  K(RegionI) = sum(((ColRI*C).*(YM(RI,:)+YP(RI,:)) - (ColRI*S).*(XM(RI,:)-XP(RI,:)))')';
		end
		
		if any(RegionII)                                          % Humlicek CPF12 Region II
          %disp('RegionII');
          YF   = Y + Y0PY0;
		  RII = ABX(CPF12) > XLIM4;
		  ColRII = ones(sum(RII),1);
		  K(RegionII) = sum(( ...
           + ((ColRII*C).*(MQ(RII,:).*MF(RII,:)-Y0*YM(RII,:)) ...
		        + (ColRII*S).*YF.*XM(RII,:)) ./ (MQ(RII,:)+Y0Q) ...
           + ((ColRII*C).*(PQ(RII,:).*PF(RII,:)-Y0*YP(RII,:)) ...
		        - (ColRII*S).*YF.*XP(RII,:)) ./ (PQ(RII,:)+Y0Q))');
          K(RegionII) = Y*K(RegionII) + exp( -XQ(RegionII));
        end
       end % CPF12
%.....
