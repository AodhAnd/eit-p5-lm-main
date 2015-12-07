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
y = 0.4880 * x - 0.2173;

plot(x,y);


% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Steering gain')
ylabel('Steering gain')
xlabel('Vehicle velocity')
% xlim([3 7]);
% legend('Theta error', 'Theta','Velocity of X m \cdot s^{-1}')
grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)