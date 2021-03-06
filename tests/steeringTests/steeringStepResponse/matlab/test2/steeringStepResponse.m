close all;
clear all;
clc;

Data1 = csvread('run2.1600.csv');
%Data3 = csvread('test1650.csv');
%Data2= csvread('test1600.csv');

Step1(:,2) = Data1(:,1);
Step1(:,1) = Data1(:,4);
%Step2(:,2) = Data2(:,1);
%Step2(:,1) = Data2(:,4);
%Step3(:,2) = Data3(:,1);
%Step3(:,1) = Data3(:,4);

hold;
P1 = scatter(Step1(:,1),Step1(:,2));
%P2 = plot(Step2(:,1),Step2(:,2));
%P3 = plot(Step3(:,1),Step3(:,2));

set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
%set( P2, 'color', '[0 .5 0]', 'LineWidth', 2 );
%set( P3, 'color', '[0 0 1]', 'LineWidth', 2 );

title('Step response with and without control')
xlabel('Time [s]')
ylabel('Velocity [m \cdot s^{-1}]')
% xlim([3 7]);
legend('Voltage step', 'P control','P control with Feed forward','Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)