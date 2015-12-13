clear all
close all;
clc;

%csvwrite('simulation.csv', ScopeData8);
simData = csvread('simulation.csv', 0, 0);
simData(:,1) = simData(:,1)-1

%data = csvread('LOG00212.csv');%, 0, 0);
%data(:,1) = (data(:,1)-4140)/1000;

%plot( data(:,1), data(:,2), 'b', 'LineWidth', 2);
%hold on;
%scatter( data(:,1), data(:,2), 20, [0 0 0], '+' );

plot( simData(:,1), simData(:,2), 'b', 'LineWidth', 2);
hold on;
plot( simData(:,1), simData(:,3), 'r', 'LineWidth', 2);

%plot( simData(:,1)+.25, simData(:,2), 'r');


%Title and axis labels added
title('Modeled System Step Responses')
xlabel('Time (s)')
ylabel('Linear Velocity [ m \cdot s^{-1} ]')

legend('Simulation with values originating from 2nd order model', 'Simulation with values from holistic system tests', 'Location', 'southeast')

xlim([ 0 5 ]);

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)