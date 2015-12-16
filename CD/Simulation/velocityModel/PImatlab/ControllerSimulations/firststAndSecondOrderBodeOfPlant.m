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

K = kt / (R * B + kt * ke );

tau = (R * J )/ (R * B + kt * ke );

num1 = K;
den1 = tau * s + 1;

H1 = num1/den1

num2 = kt;
den2 = L * J * s^2 + ( R * J + L * B ) * s + R * B + kt * ke;

H2 = num2/den2

bode(H1, 'r')

hold

bode(H2, 'b')

%margin(H1)
%margin(H2)

%adding legend
legend('1st Order Simulation', '2nd Order Simulation', 'Location', 'southwest' )



grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)



%Title and axis labels added
%%%%title('Bode Plot of 1^{st} and 2^{nd} Order Models')
%xlabel('Time [s]')
%ylabel('Velocity [m \cdot s^{-1}]')

% figure;
% 
% H3 = tf([ K ], [ tau  1 ])
% H4 = tf([kt], [L*J  R*J+L*B  R*B+kt*ke])
% pzplot(H3, H4)
% 
% figure;
% nyquist(H3, H4)
% 
% figure;
% [z,p,k] = tf2zp([kt], [L*J  R*J+L*B  R*B+kt*ke]);
% zplaneplot(z,p,{'s','+'});

 p1 = pole(H1)
 p2 = pole(H2)
 figure;
 %Plotting the unit circle
 theta=linspace( 0, 2*pi ,100 );
 rho=linspace( 1, 1, 100 );
 [x,y] = pol2cart(theta,rho);
 plot(x,y, 'LineWidth', 1, 'Color', [ 0 0 1 ])
 axis square
 
hold on;
 
plot(p1,0, '*', 'Color', '[ 1 0 0 ]')
 
 
 plot(p2(1,:), 0, 'o', 'Color', '[ 0 0 1 ]')
 
 
 plot(p2(2,:), 0, 'x', 'Color', '[ 0 .5 0 ]')
 
 xlim([-1.5e3 1])
 ylim([-.75e3 .75e3])
 axis square
 
 grid on
 set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)



