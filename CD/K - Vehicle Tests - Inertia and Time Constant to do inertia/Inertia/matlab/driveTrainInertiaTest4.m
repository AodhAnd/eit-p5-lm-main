clear all
close all;
clc;

rt = 0.166/(2*pi)
N = 4773/187

data2 = csvread('data4.1.csv');%, 0, 0);

left2  = data2(:,2);
right2 = data2(:,3);
leftRight2 = ((data2(:,2)+data2(:,3)))%;/2)* N/rt;
time2  = data2(:,4)-1220;

sRight = scatter( time2, leftRight2, 12, 'r', '*' );

%%%%%%%%%%Rising Edge Time Constant%%%%%%%%%%
%2.4 m/s is the max velocity(steady state)
%point to read the time constant:
%2.4*.632 = 1.5168 [m/s]
%the value in time here is:
%1564 [ms]
%the value in time where the rising edge starts is:
%43 [ms]
%So the time constant is: 1564 - 43 = 1521 [ms]
tau1 =  1.5212 %[s]

%%%%%%%%%%Rising Edge Time Constant%%%%%%%%%%
%2.4 m/s is the max velocity (steady state)
%point to read the time constant:
%2.4*(1-.632) = 0.4560 [m/s]
%the value in time here is:
%6252 [ms]
%the value in time where the falling edge starts is:
%5000 [ms]
%So the time constant is: 5000 - 6252 = 1252 [ms]
tau2 = 1.252  %[s]

%ylim([-1 25])
%ylim([0 4.5])

%Title and axis labels added
title('Moment of Inertia')
xlabel('Angular Velocity (rad/s)')
ylabel('Inertia (kg\cdotm^2)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)