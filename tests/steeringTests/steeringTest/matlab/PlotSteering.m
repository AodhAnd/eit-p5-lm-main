clc;
clear all;
clear home;

data=csvread('full right to straight in 10us steps.csv');

time = data(:,4) / 1000;
left = data(:,2);
right = data(:,3);
p = scatter( time, left, 25, 'b', '*' );
hold;
q = scatter( time, right,25, 'r', '*');

%Creating least square solution
%h = lsline;
%set( h, 'color', 'r', 'LineWidth', 1 );

%Using polyfit to calculate the equation for lsline
% p = polyfit( x, y, 1 );
% a = p(:,1)
% b = p(:,2)
%Creating legend containing equation for lsline (%0.4f = 4 decimals)
%legend('Data', sprintf( 'y = %0.1d x + %0.4f', a, b ), 'Location', 'northwest' )

%Title and axis labels added
title('Steering belt velocity')
xlabel('Time (s)')
ylabel('Linear Velocity (m\cdot s^{-1})')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .1)