clc;
clear all;
clear home;
close all;

% Motor velosity measured in V over time:
% Used range 2: 1V = 10E3 RPM
scale = (10E3/60)*2*pi; % (rad/s)/V

data = csvread('motorTest8.csv', 450, 0, [450 0 700 2] );

sec = data(:,1);
v1  = data(:,2)*scale; % (rad/s)
v2  = data(:,3);

%rad/s vs time --> time constant

p = scatter( v2, v1, 12, 'b', '*' );

h = lsline;
set( h, 'color', 'r', 'LineWidth', 1 );

%Using polyfit to calculate the equation for lsline
p = polyfit( v2, v1, 1 );
a = p(:,1)
b = p(:,2)
%Creating legend containing equation for lsline (%0.4f = 4 decimals)
legend('Data', sprintf( 'y = %0.2fx %0.2f', a, b ), 'Location', 'northwest' )

%limmiting the axes to remove zero results
ylim([0 2500])
xlim([0 5.5])

%Title and axis labels added
title('Motor Gain')
ylabel('Angular Velocity (rad/s)')
xlabel('Motor Voltage (V)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%Gain = hældning: 569.19