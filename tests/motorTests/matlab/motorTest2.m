clc;
clear all;
clear home;
close all;


M = csvread('motorTest2.csv',23,0);
%M(:,2) = M(:,2)*10


%I = M(:,2)+0.0562501;
%T = M(:,1)+0.0003-0.00011-1E-4;

I = M(:,2)
T = M(:,1)+1E-4

Imax = 6.7874999
R = 0.178

% 63.2% of max current:
Ip = Imax*.632

tau = 0.00067

%tau/R = L , where R = 0.178 Ohm

L = tau * R

%The ideal curve
Il = Imax*(1-exp(-T*R/L));
p2 = plot(T,Il)
set( p2, 'color', '[0 .5 0]', 'LineWidth', 2 ); %[0 1 0] = light green
hold                                            %[0 .5 0] = dark green

%The data
p1 = plot(T,I)
set( p1, 'color', 'b', 'LineWidth', 2 );
axis([0 5E-3 0 7])

%Time constant
r = refline( 0, Ip)
set( r, 'color', 'r', 'LineWidth', 1 );

%Title and axis labels added
title('Armature Inductance')
xlabel('Time (t)')
ylabel('Current (A)')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)