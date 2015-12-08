close all;
clear all;
clear home;
clc;

%FileData = load('matlab2.mat');
%csvwrite('SimulationVelocityDataadjusted.csv', ScopeData1);

SimulationData = csvread('SimulationVelocityDataadjusted.csv');

R = 0.178;      %The motor's internal resistance
L = 119.26e-6;  %The motor's inductance
Ke = 1.89e-3;   %the electromotive constant
Kt = 0.0016;   %The motor constant
Jm = 2.3891e-6; %Motor's inertia

rt = 0.166/(2*pi);
N = 187/4773;

Jtot = 5.5980e-06;

Btot = 4.7088e-6;

plot(SimulationData(:,1), SimulationData(:,2), 'LineWidth', 2)
hold on;
plot(SimulationData(:,1), SimulationData(:,3), 'LineWidth', 2)

xlim([1 1.004])
ylim([0 0.04 ])

%adding legend
legend('1st Order Simulation', '2nd Order Simulation', 'Location', 'southeast' )

%Title and axis labels added
title('Comparison of 1^{st} and 2^{nd} Order Models (Zoom)')
xlabel('Time [s]')
ylabel('Velocity [m \cdot s^{-1}]')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

