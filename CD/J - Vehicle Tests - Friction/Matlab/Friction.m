clc;
clear all;
clear home;

rt = 0.166/(2*pi)
N = 4773/187
Kt = 0.0016

V = [1.0  , 1.2  , 1.4  , 1.6  , 1.8  , 2.0  , 2.2  , 2.4  , 2.6  , 2.8  , 3.0  , 3.2  , 3.4  , 3.6]'; % Vehicle's velocity (km.hâ?»Â¹)
Ia = [4.12 , 4.38 , 4.63 , 4.77 , 4.93 , 5.09 , 5.21 , 5.35 , 5.33 , 5.60 , 5.81 , 5.89 , 6.12 , 6.42]'; % Supplied current

%        V    A
data = [ V    Ia ]

data(:,1) = ((data(:,1)* 10^(3)) / 3600)* N/rt %rad/s
data(:,2) = data(:,2)*Kt %N*m

x = data(:,1);
y = data(:,2);
p = scatter( x, y, 25, 'b', '*' );

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
title('Total Friction')
xlabel('Angular Velocity (rad\cdot s^{-1})')
ylabel('K_t\cdoti_a = Torque (N\cdotm)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)