function K=voigt3(v,v0,delvD,delvL)
%function K=voigt3(v,v0,delvD,delvL)
    x = sqrt(log(2))*(v-v0)/delvD;
    y = sqrt(log(2))*delvL/delvD;
    K=humlik(x',y);
    % K=K./trapz(v,K);
