close all;
clear all;
clear home;
clc;

Step = csvread('step.csv');
hold
P1=scatter(Step(:,6)/1000,(Step(:,5)+Step(:,4))/2, 'r')

title('System step response')
xlabel('Time [s]')
ylabel('Velocity [m \cdot s^{-1}]')
xlim([2.5 6]);
legend('Data','Time constant', 'Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
set ( tauLine, 'color', '[0 0 1]', 'LineWidth', 2 );
