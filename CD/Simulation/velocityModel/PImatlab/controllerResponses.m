%csvwrite('simulation4.csv', ScopeData1);
%%
clear all
close all;
clc;

simData = csvread('simulation4.csv', 0, 0);
simData(:,1) = simData(:,1)-2;

hold on;
plot( simData(:,1), simData(:,2), 'color', [1  0 0], 'LineWidth', 2, 'LineStyle', '-');
hline = refline(0,1.4);
set( hline, 'Color', [.1 .1 .1], 'LineStyle', '--', 'LineWidth', 1);
plot( simData(:,1), simData(:,3), 'color', [0  0 1], 'LineWidth', 2, 'LineStyle', '-');
plot( simData(:,1), simData(:,4), 'color', [0 .5 0], 'LineWidth', 2, 'LineStyle', '-');
plot( simData(:,1), simData(:,5), 'color', [0  0 0], 'LineWidth', 3, 'LineStyle', ':');


%Title and axis labels added
title('Different Controller Step Responses')
xlabel('Time [s]')
ylabel('Linear Velocity [ m \cdot s^{-1} ]')

legend('The plant', 'Refference at 1.4  m \cdot s^{-1}', 'P-controller', 'Feed forword P-controller', 'PI-controller', 'Location', 'southeast')

xlim([ 0 5 ]);
ylim([ 0 1.5 ]);

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)