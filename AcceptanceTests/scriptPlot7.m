clear all;
close all;
clc;

% Read the data from the test
data = csvread('test7.csv');


%put the data according to their position
distance = data(:,1);
angle = data(:,2);

% Plots
hold on
P1 = scatter(distance,angle);


% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Angle vs distance')
xlabel('Distance [cm]')
ylabel('Angle [°]')
%xlim([-100 2500]);
%ylim([-100 2500]);
%legend('')
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
