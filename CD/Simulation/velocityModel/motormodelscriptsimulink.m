clear home;
close all;
clear all;
clc;

%%%%%%%%%%%% Motor %%%%%%%%%%%%

R = 0.178;      %The motor's internal resistance
L = 119.26e-6;  %The motor's inductance
Ke = 1.89e-3;   %the electromotive constant
Kt = 0.0016;   %The motor constant
Jm = 2.3891e-6; %Motor's inertia
LJ=5.5980e-06*119.26e-6
RJ=0.178*5.5980e-06
LB=119.26e-6*4.7088e-6
RB=0.178*4.7088e-6
KK=Kt*Ke
SS=LB+RJ
LJ/(KK+RB)
%Bm = 2.2e-6;    %Motor friction
%Nm = 187;        %Number of teeth on the gear G_m

%%%%%%%%%%%% DriveTrain %%%%%%%

%Jd = 10;
%Bd = ?;
%Nd = 2;

%%%%%%%%%%%% Total system %%%%%%
rt = 0.166/(2*pi)
N = 187/4773
Rbat = 0%.11;
%M = 2932;

%Bmass = ?;
%Jmass = M * rt;

%Jtot = Jm + N^2*(Jd + Jmass);
Jtot = 5.5980e-06;
%Btot = 11*10e-6;
Btot = 4.7088e-6;
%Btot = Bm + N^2*(Bd + Bmass);

syms s;

s = tf('s');
H = (Kt /(L*Jtot*s^2 +(L*Btot + R*Jtot)*s + R*Btot+Kt*Ke));

opt = stepDataOptions('StepAmplitude',7.2)
step(H,opt)

G = 3000/7.2;  % = 416.6667 [rad * s^-1 * V^-1]

%rad/s *  (V /// rad / s)  =  V

tau = 0.258; %[s]



