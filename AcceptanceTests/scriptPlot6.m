clear all;
close all;
clc;

% Read the data from the test
coord = csvread('test6.csv');


%put the data according to their position
X1 = coord(:,1);
Y1 = coord(:,2);
X2 = coord(:,3);
Y2 = coord(:,4);
X3 = coord(:,5);
Y3 = coord(:,6);
X4 = coord(:,7);
Y4 = coord(:,8);


%circles
theta = 0:0.1:2*pi
radius = 250
Xc1 = radius * cos(theta);
Yc1 = radius * sin(theta);
Xc2 = 2000 + (radius * cos(theta));
Yc2 = radius * sin(theta);
Xc3 = radius * cos(theta);
Yc3 = 2000 + (radius * sin(theta));



% Plots
hold on
P1 = scatter(X1,Y1);
P2 = scatter(X2,Y2);
P3 = scatter(X3,Y3);
P4 = scatter(X4,Y4);

Pc1 = plot(Xc1,Yc1);
Pc2 = plot(Xc2,Yc2);
Pc3 = plot(Xc3,Yc3);

axis equal;

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Route planning')
xlabel('X position')
ylabel('Y position')
%xlim([-100 2500]);
%ylim([-100 2500]);
legend('1st part','2nd part','3rd part','4th part')
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
