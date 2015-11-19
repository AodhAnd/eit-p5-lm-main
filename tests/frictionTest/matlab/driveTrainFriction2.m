clc;
clear all;
clear home;
close all;

%                    A
data = [  %0.14     3.7; %---- These data is when the vehicle runs
          %0.17     3.8; %     crocket(without breaking)
          %0.25     3.9;
          %0.33     4.0;
          %0.39     4.1;
          %0.42     4.2;
          %0.61     4.3;
          0.67     5.8;  %---- These data is when the vehicle runs straight
          0.69     5.9;  %     (width breaking)
          0.75     6.0;
          0.78     6.1;
          0.83     6.2;
          0.86     6.3;
          0.86     6.4;
          0.89     6.5;
          0.89     6.6;
          0.92     6.7;
          0.92     6.8;
          0.94     6.9;
          0.97     7.0;
          1.00     7.1  
                        ];
      
      
y = data(:,2)*0.0016;  % <-- kt
x = data(:,1);

p = scatter( x, y,25,'b', '*' );

%xlim([0 7.5])

%Creating least square solution
h = lsline;
set( h, 'color', 'r', 'LineWidth', 1 );

%Using polyfit to calculate the equation for lsline
p = polyfit( x, y, 1 );
a = p(:,1)
b = p(:,2)
%Creating legend containing equation for lsline (%0.4f = 4 decimals)
legend('Data', sprintf( 'y = %0.4fx + %0.4f', a, b ), 'Location', 'northwest' )

%Title and axis labels added
title('Friction in Drivetrain')
xlabel('Velocity (m/s)')
ylabel('Torque (N)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)