%% Gain calculations
figure
syms K

Kp = 1.5;
ThetaRef = 0;

% Read the data from the test
dat = dlmread('gainCalc.tsv','\t');


% Plots
hold on
P1 = scatter(dat(:,2),dat(:,5))
% P1 = scatter(ThetaError,Theta);
% ThetaCalc = ThetaRef*Kp*K*exp(-Kp*K*t)

P = polyfit(dat(:,2),dat(:,5),1)
x = [0:0.01:2.5];
y = 0.5149 * x - 0.1925;

plot(x,y);

legend('Data','y = 05149x - 0.1925','Location', 'southeast', 'fontsize', 15)

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Steering Gain vs. Velocity', 'fontsize', 13)
ylabel('Steering Gain', 'fontsize', 12)
xlabel('Vehicle Velocity [m \cdot s^{-1}]', 'fontsize', 12)
% xlim([3 7]);
% legend('Theta error', 'Theta','Velocity of X m \cdot s^{-1}')
grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)