close all;
clear all;
clc;
data=csvread('Pgain3.csv');
P1=plot(data(:,1),data(:,2),'linewidth',2)

title('Distance Step with Lead Compensation')
xlabel('Time [s]')
ylabel('Distance from Line [m]')
xlim([0 10]);
ylim([0 1.5]);
legend('Simulation data', 'Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
set ( tauLine, 'color', '[0 0 1]', 'LineWidth', 2 );