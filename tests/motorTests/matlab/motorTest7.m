clear all;
clc;
clear home;

% Motor velosity measured in V over time:
% Used range 2: 1V = 10E3 RPM
scale = (10E3/60)*2*pi; % (rad/s)/V

M = csvread('motorTest7.csv', 60, 0, [60 0 871 1])

M(:,2)= M(:,2)*scale; % rad/s
M(:,1) = M(:,1)+0.722; % moving data to start at 0 on time axis

t = M(:,1)
rad = M(:,2)

%f = fit(t,rad,'exp1')
%plot(f,t,rad)


Wo = 3063.05283725005 % rad/s
% The friction:
B = 2.2e-06
%coloumb friction
tauC = 0.0016

%initializing vector of zeros for containing the inertia(s)
J = zeros(812,1);

%calculating the inertia at each point
for x = 50:812
    J(x-49) = ((B*t(x))/ ( log( (B*Wo + tauC) / (B*rad(x) + tauC) )));
end

%Plotting the inertia against rotational velocity (rad/s)
p = scatter( rad, J, 1, 'b', '+' );


%limmiting x-axis to remove zero results
xlim([168 3500])

%The average value of moment of inertia
I = sum(J)/762

%Title and axis labels added
title('Moment of Inertia')
xlabel('Angular Velocity (rad/s)')
ylabel('Inertia (kg\cdotm^2)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
hold

%creating vector width the same average value (inertia) .. for plotting
 for x = 1:812
     K(x) = sum(J)/762;
 end

%plotting the average
h = plot(rad,K)
set( h, 'color', 'r', 'LineWidth', 1.5 );

%adding legend
legend('Data', sprintf( 'J = %0.4d ', I ), 'Location', 'southeast' )







