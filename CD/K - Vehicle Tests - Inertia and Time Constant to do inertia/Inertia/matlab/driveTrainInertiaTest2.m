clear all
close all;
clc;

rt = 0.166/(2*pi)
N = 4773/187

data = csvread('data4.1.csv', 237, 0, [237 0 302 3])
left  = data(:,2);
right = data(:,3);
leftRight = ((data(:,2)+data(:,3))/2)* N/rt;
time  = data(:,4)-3390;

Wo = 2.3* N/rt
% The friction:
B = 4.7088e-06
%coloumb friction
tauC = 0.0055
%5.5980e-06
%initializing vector of zeros for containing the inertia(s)
J = zeros(66,1);

%calculating the inertia at each point
for x = 2:66
    J(x) = ((B*time(x)*0.001)/ ( log( (B*Wo + tauC) / (B*leftRight(x) + tauC) )));
end

%Plotting the inertia against rotational velocity (rad/s)
p = scatter( leftRight, J, 5, 'b', '*' );
hold;
%ylim([-1 25])
%ylim([0 4.5])

%creating vector width the same average value (inertia) .. for plotting
 for x = 1:66
     K(x) = sum(J)/66;
 end

%plotting the average
h = plot(leftRight,K)
set( h, 'color', 'r', 'LineWidth', 1.5 );

%Title and axis labels added
title('Moment of Inertia')
xlabel('Angular Velocity (rad/s)')
ylabel('Inertia (kg\cdotm^2)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)