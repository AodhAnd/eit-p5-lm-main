p = get(gcf, 'Position')           % These two lines makes the figuresappear the same
set(0, 'DefaultFigurePosition', p) % place on the screen as where you left them last
clear all
close all;
clc;

%csvwrite('simulationPIsingleStepTuned.csv', ScopeData4);
simData = csvread('simulationPIsingleStepTuned.csv', 0, 0);
simData(:,1) = simData(:,1)-2

data = csvread('LOG00299.csv'); % step 94 for calculated PI controller
                                % step 88 for tuned PI controller
                                % 

%data = csvread('LOG00217.csv');%, 0, 0); 18 to 22    use step 16
data(:,1) = (data(:,1)-4035)/1000;
%data1 = csvread('LOG00224.csv');%, 0, 0);
%data1(:,1) = (data1(:,1)-4035)/1000;
%data2 = csvread('LOG00225.csv');%, 0, 0);
%data2(:,1) = (data2(:,1)-4035)/1000;
%data3 = csvread('LOG00227.csv');%, 0, 0);
%data3(:,1) = (data3(:,1)-4035)/1000;

%data(:,3) = data(:,3);%-5.5;

[AX, vel, bat] = plotyy( simData(:,1), simData(:,2), data(:,1), data(:,3));
set(AX,'NextPlot','add')
plot(AX(1), data(:,1), data(:,2), 'Color', [0 0 1], 'LineWidth', 2);
pAdd = plot(AX(2), data(:,1), data(:,4) );
set(pAdd, 'Color', [1 0 0], 'LineWidth', 2 );


%pAdd = plot(AX(1), data(:,1), data(:,5) );
%set(pAdd, 'Color', [0 .5 0], 'LineWidth', 2 );

set(AX(1),'xlim',[0 9], 'ylim', [0 3], 'ycolor', [0 0 1]);
set(vel, 'Color', [0 .5 0], 'LineWidth', 2);
set(AX(2),'xlim',[0 9], 'ylim', [1.5 8], 'ycolor', [.7 0 0]);
set(bat, 'Color', [.3 0 0], 'LineWidth', 2);

hline = line([1 10], [1.4 1.4]);
set(hline, 'Color', [.3 .3 .3], 'LineWidth', 1, 'LineStyle', '--');

legend('Simulated step response', 'Measured step response', 'Input step to 1.4 m\cdot s^{-1}', 'Battery voltage', 'Controller output', 'Location', 'southeast')

hline = line([1 1], [0 1.4]);
set(hline, 'Color', [.3 .3 .3], 'LineWidth', 1, 'LineStyle', '--');

hline = line([1.129 1.129], [0 3]);
set(hline, 'Color', [0 0 0], 'LineWidth', 1.3, 'LineStyle', ':');

%%%%%plot( data(:,1), data(:,3), 'k', 'LineWidth', 2);
%scatter( data(:,1), data(:,2), 100, [0 .3 0], '.' );


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
title('Tuned PI-Controller and Simulation Comparrison')
xlabel('Time [s]')
ylabel(AX(1), 'Linear velocity [ m \cdot s^{-1} ]')
ylabel(AX(2), 'Voltage [ V ]')
%xlim([ 0 3 ]);

set(AX(1), 'Xgrid', 'on', 'Ygrid', 'on', 'ytick', [0 .5 1 1.5], 'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
set(AX(2), 'Xgrid', 'on', 'Ygrid', 'on', 'ytick', [3 3.5 4 4.5 5 5.5 6 6.5 7 7.5 8], 'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)