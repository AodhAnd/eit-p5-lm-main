p = get(gcf, 'Position')           % These two lines makes the figuresappear the same
set(0, 'DefaultFigurePosition', p) % place on the screen as where you left them last
clear all
close all;
clc;

%csvwrite('simulationPImultiStepNew.csv', ScopeData14);
simData = csvread('simulationPImultiStepNew.csv', 0, 0);
simData(:,1) = simData(:,1)-2

%data = csvread('LOG00238.csv');

data = csvread('1point0mPRsec.csv');%, 0, 0); 18 to 22    use step 16
data(:,1) = (data(:,1)-4035)/1000;
data1 = csvread('1point5mPRsec.csv');%, 0, 0);
data1(:,1) = (data1(:,1)-4035)/1000;
data2 = csvread('2point0mPRsec.csv');%, 0, 0);
data2(:,1) = (data2(:,1)-4035)/1000;
data3 = csvread('2point5mPRsec.csv');%, 0, 0);
data3(:,1) = (data3(:,1)-4035)/1000;

%data(:,3) = data(:,3);%-5.5;

hold on;
%[AX, vel, bat] = plotyy( data(:,1), data(:,2), data(:,1), data(:,3));
%set(AX(1),'xlim',[0 3], 'ylim', [0 3], 'ycolor', [0 0 1]);
%set(vel, 'Color', [0 0 1], 'LineWidth', 2);
%set(AX(2),'xlim',[0 3], 'ylim', [3 8], 'ycolor', [1 0 0]);
%set(bat, 'Color', [1 0 0], 'LineWidth', 2);
%hline = line([1.144 1.144], [0 3]);
%set(hline, 'Color', [.3 .3 .3], 'LineWidth', 1, 'LineStyle', '--');

plot( simData(:,1), simData(:,2), 'r', 'LineWidth', 2);
plot( data(:,1), data(:,2), 'b', 'LineWidth', 2);
scatter( data(:,1), data(:,2), 20, [0 .3 0], 'o' );

plot( simData(:,1), simData(:,3), 'r', 'LineWidth', 2);
legend('Simulation data','Test data', 'Test data resolution', 'Location', 'southeast')
plot( data1(:,1), data1(:,2), 'b', 'LineWidth', 2);
scatter( data1(:,1), data1(:,2), 20, [0 .3 0], 'o' );

plot( simData(:,1), simData(:,4), 'r', 'LineWidth', 2);
plot( data2(:,1), data2(:,2), 'b', 'LineWidth', 2);
scatter( data2(:,1), data2(:,2), 20, [0 .3 0], 'o' );

plot( simData(:,1), simData(:,5), 'r', 'LineWidth', 2);
plot( data3(:,1), data3(:,2), 'b', 'LineWidth', 2);
scatter( data3(:,1), data3(:,2), 20, [0 .3 0], 'o' );


%Title and axis labels added
title('PI-Controller Simulation and Implementation Compared')
xlabel('Time [s]')
ylabel('Linear Velocity [ m \cdot s^{-1} ]')
%ylabel(AX(2), 'Battery Voltage [ V ]')

xlim([ 0.5 3 ]);

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6, 'ytick', [0 .25 .5 .75 1 1.25 1.5 1.75 2 2.25 2.5])

%xlim([ 0 3 ]);

%set(AX(1), 'Xgrid', 'on', 'Ygrid', 'on', 'ytick', [0 .5 1 1.5 2], 'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
%set(AX(2), 'Xgrid', 'on', 'Ygrid', 'on', 'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)