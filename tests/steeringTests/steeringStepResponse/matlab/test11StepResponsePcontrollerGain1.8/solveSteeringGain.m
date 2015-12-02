clear all;
close all;
clc;

syms K

Kp = 1.8;
ThetaRef = 0;

% Read the data from the test
%Data1 = csvread('stepresponse1.2-60.csv');
%Data1 = csvread('stepresponse1.5-60.csv');
%Data1 = csvread('stepresponse1.8-60.csv');
%Data1 = csvread('stepresponse2.1-60.csv');
Data1 = csvread('stepresponse2.4-60.1.csv');
%Data1 = csvread('stepresponse2.4-60.2.csv');


t     = Data1(:,1);
Theta = Data1(:,3);
ThetaError = Data1(:,2);

% Plots
hold on
P1 = plot(t,Theta);
P2 = plot(t,ThetaError);
% ThetaCalc = ThetaRef*Kp*K*exp(-Kp*K*t)

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Step response of steering')
xlabel('Time [ms]')
ylabel('Azimuth [°]')
% xlim([3 7]);
legend('Velocity of X m \cdot s^{-1}', 'Velocity of X m \cdot s^{-1}','Velocity of X m \cdot s^{-1}')
grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%% Gain calculations
syms K

Kp = 2.1;
ThetaRef = 0;

% Read the data from the test
Data1 = csvread('stepresponse1.2-60.csv');

t     = Data1(:,1);
Theta = Data1(:,2);
ThetaError = Data1(:,3);

% Plots
%P1 = scatter(ThetaError,Theta);
% ThetaCalc = ThetaRef*Kp*K*exp(-Kp*K*t)

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Step response of steering')
xlabel('Error')
ylabel('Angle')
% xlim([3 7]);
legend('Theta error', 'Theta','Velocity of X m \cdot s^{-1}')
grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)