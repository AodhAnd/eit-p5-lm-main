close all;
clear all;
clear home;
clc;

Step1 = csvread('steps.csv');
Step2 = csvread('noP2.csv');
PureP1 = csvread('pureP1.csv');
PureP2 = csvread('pureP2.csv');
PwithFF1 = csvread('PwithFF1.csv');
PwithFF2 = csvread('PwithFF2.csv');
% = csvread('noP1.csv');
%data1 = csvread('noP1.csv');

data = csvread('steps.csv', 9 , 0, [9 0 571 4]);

%Stepdata = [0.38 1.13 1.84 2.45 3 ; 7.89*0.2 7.75*0.4 7.52*0.6 7.29*0.8 6.97];

%p = scatter(Stepdata(2,:),Stepdata(1,:), 15, 'b', '*');
%x = Stepdata(1,:)'
%y = Stepdata(2,:)'
%hold
%Creating least square solution
%h = lsline
%set( h, 'color', 'r', 'LineWidth', 1 );
%hold;
plot(data(:,5)/1000,data(:,4));
%hold
%scatter(PureP1(:,6),PureP1(:,4));
%hold;
%scatter(PureP2(:,6),PureP2(:,4));
%hold
%scatter(PwithFF1(:,6),PwithFF1(:,4));
%hold;
%scatter(PwithFF2(:,6),PwithFF2(:,4));
%title('The Gain of each Speed Step')
title('Speed Step')
xlabel('Voltage [V]')
ylabel('Velocity [m \cdot s^{-1}]')
%p = polyfit( y, x, 1 );
%a = p(:,1)
%b = p(:,2)

%legend('Data points', sprintf( 'y = %0.3fx %0.3f', a, b ),'Location', 'southeast' )
legend('Data points','Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)