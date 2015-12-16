p = get(gcf, 'Position')           % These two lines makes the figuresappear the same
set(0, 'DefaultFigurePosition', p) % place on the screen as where you left them last
%clear all
%close all;
%clc;

csvwrite('SteeringAngular.csv', ScopeData2);
simData = csvread('SteeringAngular.csv', 0, 0);
simData(:,1) = simData(:,1)-9.6

data = csvread('gain3Test2.csv');%, 0, 0); 18 to 22    use step 16
data(:,1) = (data(:,1)-4035)/1000;

plot( simData(:,1), simData(:,2), 'r', 'LineWidth', 2);
hold on;
plot( data(:,1), data(:,2), 'b', 'LineWidth', 2);
scatter( data(:,1), data(:,2), 20, [0 .5 0], 'o' );

%Title and axis labels added
title('P-Controller Simulation and Implementation Compared')
xlabel('Time [s]')
ylabel('Angle [\circ]')

legend('Simulation data','Test data', 'Test data resolution', 'Location', 'southeast')

xlim([ 0.3 6 ]);

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)