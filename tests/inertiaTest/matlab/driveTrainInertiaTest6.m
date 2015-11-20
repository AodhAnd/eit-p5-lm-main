clear all
close all;
clc;

rt = 0.166/(2*pi)
N = 4773/187

data2 = csvread('data4.2.csv');%, 0, 0);

left2  = data2(:,2);
right2 = data2(:,3);
leftRight2 = ((data2(:,2)+data2(:,3))/2)* N/rt;
time2  = data2(:,4);

sRight = scatter( time2, leftRight2, 12, 'r', '*' );

%%%%%%%%%%Faling Edge Time Constant%%%%%%%%%%
%2.4 m/s is the max velocity(steady state)
%point to read the time constant:
%2.82*(1-.632) = 1.0378 [m/s]
%the value in time here is:
%10916 [ms]
%the value in time where the faling edge starts is:
%10054 [ms]
%So the time constant is: 10916 - 10054 = 862 [ms]
tau1 =  0.862 %[s]


%ylim([-1 25])
%ylim([0 4.5])

%Title and axis labels added
title('Moment of Inertia')
xlabel('Angular Velocity (rad/s)')
ylabel('Inertia (kg\cdotm^2)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)