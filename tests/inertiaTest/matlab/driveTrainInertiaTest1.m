clear all
close all;
clc;

rt = 0.166/(2*pi)
N = 4773/187

data1 = csvread('data3.1.csv'); %data from unplugging motor
data2 = csvread('data3.2.csv'); %data from shutting motor off in program

left1  = data1(:,2);
right1 = data1(:,3);
leftRight1 = ((data1(:,2)+data1(:,3))/2)* N/rt; % [rad/s] (for motor)
time1  = (data1(:,4)-3390)/1000; % [s]

left2  = data2(:,2);
right2 = data2(:,3);
leftRight2 = ((data2(:,2)+data2(:,3))/2)* N/rt;
time2  = (data2(:,4)-1220)/1000; % [s]

sLeft = scatter( time1, leftRight1, 12, 'b', '*' );
hold
sRight = scatter( time2, leftRight2, 12, 'r', '*' );

Wo = 2.3* N/rt    %2.3 is the max velocity in m/s (steady state)
% The friction:
B = 4.7088e-06
%coloumb friction
tauC = 0.0055

xlim([-.050 5.05])
%ylim([0 4.5])

%Title and axis labels added
title('System Step Response')
xlabel('Time (s)')
ylabel('Angular Velocity (rad\cdot s^{-1})')

%adding legend
legend('Data (unplugging motor)', 'Data (disabling motor in software)', 'Location', 'southeast' )

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)