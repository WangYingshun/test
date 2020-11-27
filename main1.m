clear;clc;
x0=[0 0 10]';
insectA = [0 0 1000;0.02 0 0;0 0.05 0.05;];
insectadult20 = insectA^(20*12)*x0;
insectratio=insectA^(10000)*x0;
insectratio = insectratio(2)/insectratio(3);
P = [0.25 0.2 0.1 0.2 0.2;0.17 0.27 0.22 0.21 0.15;0.22 0.26 0.21 0.14 0.25;0.18 0.17 0.27 0.35 0.25;0.18 0.10 0.20 0.10 0.15];
vecprice = null(P-eye(5));
vecprice = vecprice/vecprice(1)*100;
F = [0 1/3 1/3 1/2;1/2 0 1/3 0;1/2 1/3 0 1/2;0 1/3 1/3 0];
popvector = -null(F-eye(4));
Net = [0 1/2 1/4 1 1/3;
       1/3 0 1/4 0 0;
       1/3 1/2 0 0 1/3;
       1/3 0 1/4 0 1/3;
       0 0 1/4 0 0];
   Gvec = sum(Net,2);
   Net = [0 1/3 1/4 1 1/3;
       1/3 0 1/4 0 0;
       1/3 1/3 0 0 1/3;
       1/3 0 1/4 0 1/3;
       0 1/3 1/4 0 0];
   Gvec1  = sum(Net,2);
    Net = [0 1/2 1/4 1 1/3;
       1/4 0 1/4 0 0;
       1/4 1/2 0 0 1/3;
       1/4 0 1/4 0 1/3;
       1/4 0 1/4 0 0];
   Gvec3  = sum(Net,2);
   save assinment.mat;
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   