close all;
clear all;
clear home;
clc;

Step2 = csvread('step2.csv');
hold
P1=plot(Step2(:,6)/1000,(Step2(:,5)+Step2(:,4))/2, 'b')

TconstLine = [4 6 ; 1.42 1.42];
tauLine = plot(TconstLine(1,:), TconstLine(2,:));

title('System step response')
xlabel('Time [s]')
ylabel('Velocity [m \cdot s^{-1}]')
xlim([4 6]);
legend('Data','Time constant', 'Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
set ( tauLine, 'color', '[0 0 1]', 'LineWidth', 2 );

