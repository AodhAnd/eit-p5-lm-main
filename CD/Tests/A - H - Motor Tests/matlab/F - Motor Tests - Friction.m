clc;
clear all;
clear home;

% RPM to rad/s
scale = (2*pi)/60;
Kt = 0.0016;

%        V    RPM
data = [ 1.7  3684  ;
         2.2  8063  ;
         2.6  12021 ;
         3.3  16746 ;
         4.1  21966 ;
         4.8  26420 ;
         5.6  31447 ]

data(:,2) = data(:,2)*scale %rad/s
data(:,1) = data(:,1)*Kt

x = data(:,2);
y = data(:,1);
p = scatter( x, y,25,'b', '*' );

%Creating least square solution
h = lsline;
set( h, 'color', 'r', 'LineWidth', 1 );

%Using polyfit to calculate the equation for lsline
p = polyfit( x, y, 1 );
a = p(:,1)
b = p(:,2)
%Creating legend containing equation for lsline (%0.4f = 4 decimals)
legend('Data', sprintf( 'y = %0.1d x + %0.4f', a, b ), 'Location', 'northwest' )

%Title and axis labels added
title('Motor Friction')
xlabel('Angular Velocity (rad/s)')
ylabel('K_t\cdoti_a = Friction Torque (N\cdotm)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%y = 2.2e-06*x + 0.0016

%B = 2.2e-06
%and
%coloumb friction = 0.0016