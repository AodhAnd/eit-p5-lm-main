clear all;
close all;
clc;

% Read the data from the test
data = csvread('test2.csv');


%put the data according to their position
time = data(:,1);
paquage = data(:,2);



% Plots
hold on
P1 = scatter(time,paquage);


% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Communication Protocol')
%xlabel('Numer of tries')
ylabel('Returned error')
%xlim([-100 2500]);
%ylim([-100 2500]);
%legend('Paquets sended')
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
