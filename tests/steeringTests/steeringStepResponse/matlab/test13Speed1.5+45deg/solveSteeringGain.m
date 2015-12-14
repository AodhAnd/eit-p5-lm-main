%clear all;
%close all;
%clc;
%csvwrite('steering_step.csv',ScopeData)
% syms K
% 
% Kp = 1.8;
% ThetaRef = 0;

% Read the data from the test
Data1 = csvread('gain3Test1.csv');
Data2 = csvread('gain3Test2.csv');
Data3 = csvread('gain3Test3.csv');
Data4 = csvread('gain2Test1.csv');
Data5 = csvread('gain2Test2.csv');
Data6 = csvread('gain2Test3.csv');


t1     = Data1(:,1)/1000;
Theta1 = Data1(:,2);
t2     = Data2(:,1)/1000;
Theta2 = Data2(:,2);
t3     = Data3(:,1)/1000;
Theta3 = Data3(:,2);
t4     = Data4(:,1)/1000;
Theta4 = Data4(:,2);
t5     = Data5(:,1)/1000;
Theta5 = Data5(:,2);
t6     = Data6(:,1)/1000;
Theta6 = Data6(:,2);
%ThetaError = Data1(:,4);

% Plots
hold on
%P1 = plot(t1,Theta1);
%P1 = plot(t2,Theta2);
%P1 = plot(t3,Theta3);
P1 = plot(t4,Theta4,'r','linewidth',2);
P2 = plot(t5,Theta5,'color',[0,0.5,0],'linewidth',2);
P3 = plot(t6,Theta6,'b','linewidth',2);
%P2 = scatter(t,ThetaError);
% ThetaCalc = ThetaRef*Kp*K*exp(-Kp*K*t)

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Step response of steering','fontsize',14)
xlabel('Time [s]','fontsize',14)
ylabel('Angle [\circ]','fontsize',14)
% xlim([3 7]);
%legend('Theta at 1,1 m\cdot s^{-1}', 'Theta at 1,2 m\cdot s^{-1}', 'Theta at 1,3 m\cdot s^{-1}')
grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%% Gain calculations
%figure
syms K

Kp = 1.5;
ThetaRef = 0;

% Read the data from the test
%dat = dlmread('gainCalc.tsv','\t');


% Plots
%hold on
%P1 = scatter(dat(:,2),dat(:,5))
% P1 = scatter(ThetaError,Theta);
% ThetaCalc = ThetaRef*Kp*K*exp(-Kp*K*t)

%P = polyfit(dat(:,2),dat(:,5),1)
%x = [0:0.01:2.5];
%y = 0.4880 * x - 0.2173;

%plot(x,y);


% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Steering step response')

% xlim([3 7]);
legend('Test 1', 'Test 2','Test 3','location','southeast')
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
xlim([3 10]);