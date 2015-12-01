syms K

Kp = 2.1;
ThetaRef = 0;

% Read the data from the test
Data1 = readcsv('steeringStep');

t     = Data1(:,1);
Theta = Data1(:,2);
ThetaError = Data(:,3);

% Plots
P1 = plot(t,Theta);
% ThetaCalc = ThetaRef*Kp*K*exp(-Kp*K*t)

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Step response of steering')
xlabel('Time [ms]')
ylabel('Azimuth [°]')
% xlim([3 7]);
legend('Velocity of X m \cdot s^{-1}', 'Velocity of X m \cdot s^{-1}','Velocity of X m \cdot s^{-1}')
grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

