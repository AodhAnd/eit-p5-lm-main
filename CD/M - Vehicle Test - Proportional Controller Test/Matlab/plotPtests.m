close all;
clear all;
clear home;
clc;

Step2 = csvread('step2.csv');
PureP2 = csvread('pureP2.csv');
PwithFF1 = csvread('feedFW1.csv');

hold
P1=plot(Step2(:,6)/1000,(Step2(:,5)+Step2(:,4))/2, 'b')
P2=plot(PureP2(:,6)/1000,(PureP2(:,4)+PureP2(:,5))/2,'r')
P3=plot(PwithFF1(:,6)/1000,(PwithFF1(:,4)+PwithFF1(:,5))/2,'g')

xlim([3 7]);
grid on

legend('Voltage step', 'P control','P control with Feed forward','Location', 'southeast' )

set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
set( P2, 'color', '[0 .5 0]', 'LineWidth', 2 );
set( P3, 'color', '[0 0 1]', 'LineWidth', 2 );


title('Step response with and without control')
xlabel('Time [s]')
ylabel('Velocity [m \cdot s^{-1}]')

set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)