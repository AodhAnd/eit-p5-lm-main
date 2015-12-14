p = get(gcf, 'Position')           % These two lines makes the figuresappear the same
set(0, 'DefaultFigurePosition', p) % place on the screen as where you left them last
clear all
close all;
clc;

%csvwrite('simulationPImultiStep.csv', ScopeData14);
%simData = csvread('simulationPImultiStep.csv', 0, 0);
%simData(:,1) = simData(:,1)-2

data = csvread('LOG00288.csv');

%data = csvread('LOG00217.csv');%, 0, 0); 18 to 22    use step 16
data(:,1) = (data(:,1)-4035)/1000;
%data1 = csvread('LOG00224.csv');%, 0, 0);
%data1(:,1) = (data1(:,1)-4035)/1000;
%data2 = csvread('LOG00225.csv');%, 0, 0);
%data2(:,1) = (data2(:,1)-4035)/1000;
%data3 = csvread('LOG00227.csv');%, 0, 0);
%data3(:,1) = (data3(:,1)-4035)/1000;

%data(:,3) = data(:,3);%-5.5;

%plot( simData(:,1), simData(:,2), 'r', 'LineWidth', 2);

[AX, vel, bat] = plotyy( data(:,1), data(:,2), data(:,1), data(:,3));
set(AX,'NextPlot','add')
%pAdd = plot(AX(2), data(:,1), data(:,4) );
%set(pAdd, 'Color', [0 0 0], 'LineWidth', 2 );
%pAdd = plot(AX(1), data(:,1), data(:,5) );
%set(pAdd, 'Color', [0 .5 0], 'LineWidth', 2 );

set(AX(1),'xlim',[0 9.2], 'ylim', [0 3], 'ycolor', [0 0 1]);
set(vel, 'Color', [0 0 1], 'LineWidth', 2);
set(AX(2),'xlim',[0 9.2], 'ylim', [6.3 7.5], 'ycolor', [0 0 0]);
set(bat, 'Color', [0 0 0], 'LineWidth', 2);
%hline = line([1.144 1.144], [0 3]);
%set(hline, 'Color', [.3 .3 .3], 'LineWidth', 1, 'LineStyle', '--');
hline = line([0 10], [1.4 1.4]);
set(hline, 'Color', [.3 .3 .3], 'LineWidth', 1, 'LineStyle', '--');

%%%%%plot( data(:,1), data(:,3), 'k', 'LineWidth', 2);
%scatter( data(:,1), data(:,2), 100, [0 .3 0], '.' );
legend('Simulation data', 'Refference at 1.4 m\cdot s^{-1}', 'Battery voltage', 'Location', 'southeast')

%plot( simData(:,1), simData(:,4), 'r', 'LineWidth', 2);
%plot( data1(:,1), data1(:,2), 'b', 'LineWidth', 2);
%scatter( data1(:,1), data1(:,2), 100, [0 .3 0], '.' );

%plot( simData(:,1), simData(:,6), 'r', 'LineWidth', 2);
%plot( data2(:,1), data2(:,2), 'b', 'LineWidth', 2);
%scatter( data2(:,1), data2(:,2), 100, [0 .3 0], '.' );

%plot( simData(:,1), simData(:,8), 'r', 'LineWidth', 2);
%plot( data3(:,1), data3(:,2), 'b', 'LineWidth', 2);
%scatter( data3(:,1), data3(:,2), 100, [0 .3 0], '.' );

%Title and axis labels added
title('Tuned PI-Controller and Battery Voltage')
xlabel('Time [s]')
ylabel(AX(1), 'Linear Velocity [ m \cdot s^{-1} ]')
ylabel(AX(2), 'Battery Voltage [ V ]')
%xlim([ 0 3 ]);

set(AX(1), 'Xgrid', 'on', 'Ygrid', 'on', 'ytick', [0 .5 1 1.5], 'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
set(AX(2), 'Xgrid', 'on', 'Ygrid', 'on', 'ytick', [6.9 7 7.1 7.2 7.3 7.4 7.5], 'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)