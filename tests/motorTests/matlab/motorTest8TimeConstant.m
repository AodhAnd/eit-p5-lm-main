clc;
clear all;
clear home;
close all;

% Motor velosity measured in V over time:
% Used range 2: 1V = 10E3 RPM
scale = (10E3/60)*2*pi; % (rad/s)/V

data = csvread('motorTest8.csv', 450, 0, [450 0 1001 2] );

data(:,1) = data(:,1)-0.06;
data(:,2)  = (data(:,2)+0.04375)*scale; % (rad/s)
sec = data(:,1);
v1 = data(:,2);
v2  = data(:,3);

%rad/s vs time --> time constant

p = scatter( sec, v1, 7, 'b', '+' );

%limmiting the axes to remove zero results
%ylim([0 2500])
xlim([0 1.2])

%Title and axis labels added
title('Mechanical Time Constant')
ylabel('Angular Velocity (rad/s)')
xlabel('Time (s)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
hold
r = refline( 0, 2372.55695192979*.632)
set( r, 'color', 'r', 'LineWidth', 1 );

%Creating legend containing equation for lsline (%0.4f = 4 decimals)
legend('Data', 'Time Constant', 'Location', 'southeast' )

%Time constant: 0.238 s