p = get(gcf, 'Position')           % These two lines makes the figuresappear the same
set(0, 'DefaultFigurePosition', p) % place on the screen as where you left them last
close all;
clear all;
clear home;
clc;

s=tf('s');

R = 0.178;      %The motor's internal resistance
L = 119.26e-6;  %The motor's inductance
ke = 1.89e-3;   %the electromotive constant
kt = 0.0016;   %The motor constant
rt = 0.166/(2*pi);
N = 187/4773;
J = 5.5980e-06;
B = 4.7088e-6;

%K = kt / (R * B + kt * ke )
K = 0.486;
tau = 0.211;
%tau = (R * J )/ (R * B + kt * ke )

num1 = K;
den1 = tau * s + 1;

H1 = num1/den1

x = 1;%Design parameter

Kp = 1/K      %/(K*x)    % Originally 1/K
Ki = Kp/tau % Originally Kp/tau
%proportional controller
H2 = Kp * H1

%proportional controller with feed forward:
H3 = ((1/K)+Kp)*H1

%proportional integral controller (PI)
H4 = (Kp+(Ki/s))*H1
%%
figHnd = figure;
bode(H1, 'b')
% get and display the handles of the figure
bodeHnd = get(figHnd, 'Children')
hold on

bode(H2, '--r')
bode(H3, '--g')
bode(H4, '--m')


%Title and axis labels added
title('Bode Plot of Model and Controllers')

%adding legend use bodeHnd(2) to place the legend in phase plot and bodeHnd(3) to place it in the magnitude plot
legend(bodeHnd(3), '1st Order Model', 'With Proportional Controller', 'Width Feed Forward', 'Proportional Integral Controller', 'Location', 'northeast' )

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

hold off
%Tuned PI
Kp = 0.8;
Ki = 6;
H5 = (Kp+(Ki/s))*H1

figHnd = figure;
bode(H4, 'b') %, {10e0 10e5}
% get and display the handles of the figure
bodeHnd = get(figHnd, 'Children')
ylim(bodeHnd(2), [ -180 0 ]);



%bode(H5, 'b')

%[gain1 phase1] = margin(H4)
%[gain2 phase2] = margin(H5)
%margin(H5)

%Title and axis labels added
title('Bode Plot of PI-Controller')

%adding legend use bodeHnd(2) to place the legend in phase plot and bodeHnd(3) to place it in the magnitude plot
%legend(bodeHnd(3), 'Proportional Integral Controller', 'Location', 'northeast' )

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)



