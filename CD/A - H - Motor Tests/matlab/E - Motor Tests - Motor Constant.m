clc;
clear all;
clear home;

scale = 0.2; %100 Ncm per 5 V --> 0.2 Nm/V

%        A     V
data = [ 1   0.107   ;
         2   0.113   ;
         3   0.118   ; 
         4   0.122   ;
         5   0.131   ; 
         6   0.142   ;
         7   0.149   ; 
         8   0.158   ;
         9   0.169   ; 
         10  0.180   ]

data(:,2) = data(:,2)*scale
x = data(:,1);
y = data(:,2);

p = scatter( x, y,25,'b', '*' );

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
title('Motor Constant')
xlabel('Current (A)')
ylabel('Voltage (V)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)