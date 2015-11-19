clc;
clear all;
clear home;
close all;

%Scaling factor from ponds (p) or gram-force to Newton (N)
scale = 9.80665e-3;
%The motor constant
Kt = 0.0016;

%           p      A
data = [    50    2.5;
            50    3.0;
            200   3.5;
            200   4.0;
            350   4.5;
            370   4.5;
            500   5.0;
            530   5.0;
            620   5.5;
            630   5.5;
            780   6.0;
            800   6.0;
            950   6.5;
            960   6.5;
            1100  7.0;
            1050  7.0;
            1200  7.5  ];

x = data(:,2)*Kt;
y = data(:,1)*scale; % Newton

p = scatter( x, y,25,'b', '*' );

%xlim([0 8])

%Creating least square solution
h = lsline;
set( h, 'color', 'r', 'LineWidth', 1 );

%Using polyfit to calculate the equation for lsline
p = polyfit( x, y, 1 );
a = p(:,1)
b = p(:,2)
%Creating legend containing equation for lsline (%0.4f = 4 decimals)
legend('Data', sprintf( 'y = %0.4fx %0.4f', a, b ), 'Location', 'northwest' )

%Title and axis labels added
title('Friction in Drivetrain')
xlabel('Current (A)')
ylabel('Force (N)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)