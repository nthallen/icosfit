function [ K, DKDX, DKDY, Reg ] = HUMDEV( X, Y );
% [ K, DKDX, DKDY ] = HUMDEV( X, Y );
% X is an array, Y is the Voigt Parameter

% *     To calculate the Faddeeva function and partial derivatives of the Voigt function for y>=0


if length(Y(:)) > 1
  error( 'Y must be a scalar' );
end
if size(X,2) > 1
  error( 'X must be a column vector' );
end

% Constants
RRTPI = 0.5641895835477563;                                   % 1/sqrt(pi)
Y0 = 1.5; Y0PY0 = Y0+Y0; Y0Q = Y0*Y0;               % for CPF12 algorithm
C = [ 1.0117281, -0.75197147, 0.012557727,  0.010022008, -0.00024206814, 0.00000050084806 ];
S = [ 1.393237, 0.23115241, -0.15535147,  0.0062183662, 0.000091908299, -0.00000062752596 ];
T = [ 0.31424038, 0.94778839, 1.5976826, 2.2795071, 3.0206370, 3.8897249 ];

%
%* Local variables
%      INTEGER I, J                                                      ! Loop variables
%      INTEGER RGB, RGC, RGD                                             ! y polynomial flags
%      REAL ABX, XQ, YQ                                                  ! |x|, x^2 and y^2
%      REAL XLIMA, XLIMB, XLIMC, XLIM4                                   ! x on region boundaries
%      REAL MT(0:5), MQ(0:5), PT(0:5), PQ(0:5)                           ! Temporary variables
%      REAL XP(0:5), XM(0:5), YP(0:5), YM(0:5), MF(0:5), PF(0:5)
%      REAL YP2Y0, YPY0, YPY0Q, YF1, YF2, MFQ, PFQ, D,  U, DUDY, DVDY
%      REAL A0, B1, C0, C2, D0, D1, D2, E0, E2, E4, F1, F3, F5
%      REAL G0, G2, G4, G6, H0, H2, H4, H6, P0, P2, P4, P6, P8
%      REAL Q1, Q3, Q5, Q7, R0, R2, W0, W2, W4, Z0, Z2, Z4, Z6, Z8
%      DOUBLE PRECISION DB

% ***** Start of executable code ****************************************

RGB = 1;
RGC = 1;
RGD = 1;
YQ  = Y*Y;                                                        % y^2
XLIMA = 146.7 - Y;                                                % Region A boundary
XLIMB = 24.0 - Y;                                                 % Region B boundary
XLIMC = 7.4 - Y;                                                  % Region C boundary
XLIM4 = 18.1*Y + 1.65;                                            % CPF12 I-II boundary
%.....
%     DO I = 0, N-1                                                     % Loop over all points
K = zeros(size(X));
L = zeros(size(X));
DKDX = zeros(size(X));
DKDY = zeros(size(X));
ABX = abs ( X );                                                 % |x|
XQ  = ABX.*ABX;                                                   % x^2
RegionA = ABX > XLIMA;
RegionB = ~RegionA & ABX > XLIMB;
R_notAB = ~RegionA & ~RegionB;
RegionC = ABX <= XLIMB & ABX > XLIMC;
RegionD = ~RegionA & ~RegionB & ~RegionC & ABX < 0.85;
CPF12 = ABX <= XLIMC & ABX >= 0.85; % ~RegionA & ~RegionB & ~RegionC & ~RegionD;
if any(RegionA)
  XA = X(RegionA);
  XQA = XQ(RegionA);
  D       = 1.0 ./ (XQ(RegionA) + YQ);
  D1      = D*RRTPI;
  K(RegionA)    = D1 * Y;
  L(RegionA)    = D1 .* X(RegionA);
  D1      = D1 .* D;
  DKDX(RegionA) = -D1 .* (Y+Y) .* X(RegionA);
  DKDY(RegionA) = D1 .* (XQ(RegionA)-YQ);
end
if any(RegionB)
  A0 = YQ + 0.5;                                                  % Region A y-dependents
  B1 = YQ - 0.5;
  D0 = A0*A0;                                                     % y^4 + y^2 + 0.25
  D2 = B1 + B1;                                                   % 2y^2 - 1
  C0 = 1.5   + YQ*(1.0 - D2);                                     % 1.5 + 2y^2 - 2y^4
  C2 = A0 + A0;                                                   % 2y^2 + 1
  R0 = 0.125 + YQ*(0.25 - YQ*(0.5 + YQ));
  R2 = 0.25  + YQ*(5.0  + YQ);
  % end of y-dependents
  XB = X(RegionB);
  XQB = XQ(RegionB);
  D       = 1.0 ./ (D0 + XQ(RegionB) .* (D2 + XQ(RegionB)));
  D1      = RRTPI*D;
  K(RegionB)    = D1.*(A0 + XQ(RegionB))*Y;
  L(RegionB)    = D1.*(B1 + XQ(RegionB)).*X(RegionB);
  D1            = D1.*D;
  DKDX(RegionB) = D1.*X(RegionB)*Y.*(C0 - (C2 + XQ(RegionB)).*(XQ(RegionB)+XQ(RegionB)));
  DKDY(RegionB) = D1.*(R0 - XQ(RegionB).*(R2 - XQ(RegionB).*(B1 + XQ(RegionB))));
end
if any(RegionC)
  RGC = 0;
  H0 =  0.5625 + YQ*( 4.5  + YQ*(10.5 + YQ*(6.0 + YQ)) );        % Region B y-dependents
  H2 = -4.5    + YQ*( 9.0  + YQ*( 6.0 + YQ* 4.0));
  H4 = 10.5    - YQ*( 6.0  - YQ*  6.0);
  H6 = -6.0    + YQ*  4.0;
  W0 =  1.875  + YQ*(24.25 + YQ*(27.5 + YQ* 7.0));
  W2 =  5.25   + YQ*( 3.0  + YQ* 15.0);
  W4 = -4.5    + YQ*  9.0;
  F1 = -1.875  + YQ*( 5.25 + YQ*( 4.5 + YQ));
  F3 =  8.25   - YQ*( 1.0  - YQ*  3.0);
  F5 = -5.5    + YQ*  3.0;
  E0 = Y*(1.875 + YQ*( 8.25 + YQ*( 5.5 + YQ)));
  E2 = Y*(5.25  + YQ*( 1.0  + YQ*  3.0));
  E4 = Y*0.75*H6;
  G0 = Y*(  9.0 + YQ*(42.0  + YQ*(36.0 + YQ* 8.0)));
  G2 = Y*( 18.0 + YQ*(24.0  + YQ* 24.0));
  G4 = Y*(-12.0 + YQ* 24.0);
  G6 = Y*   8.0;
  % end of y-dependents
  XC = X(RegionC);
  XQC = XQ(RegionC);
  U = E0 + XQ(RegionC) .* (E2 + XQ(RegionC) .* (E4 + XQ(RegionC)*Y));
  D = 1.0 ./ (H0 + XQ(RegionC) .* (H2 + XQ(RegionC) .* (H4 + XQ(RegionC) .* (H6 + XQ(RegionC)))));
  K(RegionC) = RRTPI*D.*U;
  L(RegionC) = RRTPI * D .* X(RegionC) .* (F1 + XQ(RegionC) .* (F3 + XQ(RegionC) .* (F5 + XQ(RegionC))));
  DUDY = W0 + XQ(RegionC) .* (W2 + XQ(RegionC) .* (W4 + XQ(RegionC)));
  DVDY = G0 + XQ(RegionC) .* (G2 + XQ(RegionC) .* (G4 + XQ(RegionC)*G6));
  DKDY(RegionC) = RRTPI*D .* (DUDY - D.*U.*DVDY);
end
if any(RegionD) % Region C y-dependents
  Z0 =     272.1014 + Y*(1280.829   + Y*(2802.870  + Y*(3764.966 ...
    + Y*(3447.629 + Y*(2256.981   + Y*(1074.409 ...
    + Y*(369.1989 + Y*(  88.26741 + Y*(  13.3988 + Y)))))))));
  Z2 =      211.678 + Y*( 902.3066  + Y*(1758.336  + Y*(2037.310 ...
    + Y*(1549.675 + Y*( 793.4273  + Y*( 266.2987 ...
    + Y*(  53.59518 + Y*    5.0)))))));
  Z4 =     78.86585 + Y*( 308.1852  + Y*( 497.3014 + Y*(479.2576 ...
    + Y*(269.2916 + Y*(  80.39278 + Y*   10.0)))));
  Z6 =     22.03523 + Y*(  55.02933 + Y*(  92.75679 ...
    + Y*(  53.59518 + Y*   10.0)));
  Z8 =     1.496460 + Y*(  13.39880 + Y*    5.0);
  P0 =     153.5168 + Y*( 549.3954  + Y*( 919.4955 + Y*(946.897 ...
    + Y*(662.8097 + Y*( 328.2151  + Y*( 115.3772 ...
    + Y*(27.93941 + Y*(   4.264678+ Y*    0.3183291))))))));
  P2 =    -34.16955 + Y*(  -1.322256+ Y*( 124.5975 + Y*(189.773 ...
    + Y*( 139.4665  + Y*(  56.81652 ...
    + Y*(  12.79458 + Y*    1.2733163))))));
  P4 =     2.584042 + Y*(  10.46332 + Y*(  24.01655 ...
    + Y*(29.81482 + Y*(  12.79568 + Y*    1.9099744))));
  P6 =  -0.07272979 + Y*(   0.9377051 ...
    + Y*(4.266322 + Y*    1.273316));
  P8 = 0.0005480304 + Y*    0.3183291;
  Q1 =     173.2355 + Y*( 508.2585  + Y*( 685.8378 ...
    + Y*(557.5178 + Y*( 301.3208  + Y*( 111.0528 ...
    + Y*( 27.6294 + Y*(   4.26413 + Y*    0.3183291)))))));
  Q3 =     18.97431 + Y*( 100.7375  + Y*( 160.4013 + Y*(130.8905 ...
    + Y*(55.88650 + Y*(  12.79239 + Y*    1.273316)))));
  Q5 =     7.985877 + Y*(  19.83766 + Y*(  28.88480 ...
    + Y*(  12.79239 + Y*    1.909974)));
  Q7 =    0.6276985 + Y*(   4.26413 + Y*    1.273316);
  % end of y-dependents
  XD = X(RegionD);
  XQD = XQ(RegionD);
  U    = 1.7724538*(P0 + XQD .* (P2 + XQD ...
    .* (P4 + XQD .* (P6 + XQD*P8))));
  D    = 1.0 ./ (Z0 + XQD .* (Z2 + XQD .* (Z4 + XQD ...
    .* (Z6 + XQD .* (Z8 + XQD)))));
  K(RegionD) = D .* U;
  L(RegionD) = 1.7724538 .* D .* X(RegionD) .* ...
    (Q1 + XQ(RegionD) .* (Q3 + XQ(RegionD) .* (Q5 + XQ(RegionD) ...
    .* (Q7 + XQ(RegionD)*0.3183291))));
  DKDY(RegionD) = 2 * ( X(RegionD) .* L(RegionD) + Y*K(RegionD) - RRTPI );
end
if any(CPF12)
  YPY0  = Y + Y0;
  YPY0Q = YPY0*YPY0;
  XCPF12 = X(CPF12)*ones(1,6);
  col = ones(sum(CPF12),1);
  MT = XCPF12 - col*T;
  MQ = MT .* MT;
  MF = 1.0 ./ (MQ + YPY0Q);
  XM = MF .* MT;
  YM = MF * YPY0;
  PT = XCPF12 + col*T;
  PQ = PT .* PT;
  PF = 1.0 ./ (PQ + YPY0Q);
  XP = PF .* PT;
  YP = PF * YPY0;
  L(CPF12) = sum(((col*C).*(XM+XP) + (col*S).*(YM-YP))')';
  
  %### Figure out how to sort this mess out
  %######################
  RegionI = CPF12 & ABX <= XLIM4;
  RegionII = CPF12 & ~RegionI;
  if any(RegionI)
    RIi = RegionI(CPF12);
    YF1 = YPY0 + YPY0;
    YF2 = YPY0Q + YPY0Q;
    MFQ = MF(RIi,:) .* MF(RIi,:);
    PFQ = PF(RIi,:) .* PF(RIi,:);
    clI = ones(sum(RIi),1);
    K(RegionI) = sum(((clI*C).*(YM(RIi,:)+YP(RIi,:)) - (clI*S).*(XM(RIi,:)-XP(RIi,:)))')';
    DKDY(RegionI) = sum(((clI*C).*(MF(RIi,:)+PF(RIi,:)-YF2*(MFQ + PFQ)) ...
      + (clI*S).*YF1.*(MT(RIi,:).*MFQ - PT(RIi,:).*PFQ))')';
  end
  if any(RegionII)                       % Humlicek CPF12 Region II
    YP2Y0 = Y + Y0PY0;
    RIIi = RegionII(CPF12);
    clII = ones(sum(RIIi),1);
    K(RegionII) = Y * sum((((clII*C).*(MQ(RIIi,:).*MF(RIIi,:) - Y0*YM(RIIi,:)) ...
      + (clII*YP2Y0*S).*XM(RIIi,:)) ...
      ./ (MQ(RIIi,:) + Y0Q) ...
      + ((clII*C).*(PQ(RIIi,:).*PF(RIIi,:) - Y0*YP(RIIi,:)) ...
      - (clII*YP2Y0*S).*XP(RIIi,:)) ...
      ./ (PQ(RIIi,:)+Y0Q))')' + exp(-XQ(RegionII,:));
    DKDY(RegionII) = 2 * ( X(RegionII) .* L(RegionII) + Y * K(RegionII) - RRTPI );
  end
end
if any(R_notAB)
  DKDX(R_notAB) = 2 * ( Y * L(R_notAB) - X(R_notAB) .* K(R_notAB) );
end
if nargout > 3
  Reg = zeros(size(X));
  RegCt = zeros(size(X));
  Reg(RegionA) = 1;
  Reg(RegionB) = 2;
  Reg(RegionC) = 3;
  Reg(RegionD) = 4;
  if any(CPF12)
    Reg(RegionI) = 5;
    Reg(RegionII) = 6;
  end
  RegCt(RegionA) = RegCt(RegionA)+1;
  RegCt(RegionB) = RegCt(RegionB)+1;
  RegCt(RegionC) = RegCt(RegionC)+1;
  RegCt(RegionD) = RegCt(RegionD)+1;
  if any(CPF12)
    RegCt(RegionI) = RegCt(RegionI)+1;
    RegCt(RegionII) = RegCt(RegionII)+1;
  end
  if any(RegCt) ~= 1
    error('Apparent region overlap');
  end
end
