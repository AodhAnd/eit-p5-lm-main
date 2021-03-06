close all;
clear all;
clc;

Data1 = csvread('test15deg.2.csv');
%Data2 = csvread('zigzag1600and1070.3.csv');
%Data3 = csvread('test1650.csv');

Step1(:,2) = Data1(:,4)+180;    %angle
%for(
%if(Step1(:,2)>360) {Step1(:,2) = Step1(:,2) - 180;}
Step1(:,1) = Data1(:,3);    %time
%Step2(:,2) = Data2(:,1);
%Step2(:,1) = Data2(:,4);
%Step3(:,2) = Data3(:,1);
%Step3(:,1) = Data3(:,4);

hold;
P1 = scatter(Step1(:,1),Step1(:,2));
%P2 = plot(Step2(:,1),Step2(:,2));
%P3 = plot(Step3(:,1),Step3(:,2));
grid on
set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
%set( P2, 'color', '[0 .5 0]', 'LineWidth', 2 );
%set( P3, 'color', '[0 0 1]', 'LineWidth', 2 );

title('Step response steering with control')
xlabel('Time [s]')
ylabel('Angle')
% xlim([3 7]);
%legend('Voltage step', 'P control','P control with Feed forward','Location', 'southeast' )

set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)