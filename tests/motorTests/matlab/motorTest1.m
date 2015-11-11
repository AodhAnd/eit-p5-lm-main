clc;
clear all;
clear home;

%          A     V
data = [
         -5.0  -0.71 ;
         -4.5  -0.65 ;
         -4.0  -0.59 ;
         -3.5  -0.54 ;
         -3.0  -0.43 ;
         -2.5  -0.36 ;
         -2.0  -0.27 ;
         -1.5  -0.20 ;
         -1.0  -0.14 ;
         -0.5  -0.07 ;
          0.5  0.16  ;
          1.0  0.34  ;
          1.5  0.53  ;
          2.0  0.62  ;
          2.5  0.64  ;
          3.0  0.75  ;
          3.5  0.78  ;
          4.0  0.80  ;
          4.5  0.83  ;
          5.0  0.88  ];

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
title('Armature Resistance')
xlabel('Current (A)')
ylabel('Voltage (V)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)