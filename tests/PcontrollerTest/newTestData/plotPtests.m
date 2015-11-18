close all;
clear all;
clear home;
clc;

Step1 = csvread('step1.csv');
Step2 = csvread('step2.csv');
PureP1 = csvread('pureP1.csv');
PureP2 = csvread('pureP2.csv');
PwithFF1 = csvread('feedFW1.csv');
PwithFF2 = csvread('feedFW2.csv');
%Ptest = csvread('Ptest.csv'); Yesterday = to fast
% = csvread('noP1.csv');
%data1 = csvread('noP1.csv');

%scatter(Step1(:,6),(Step1(:,5)+Step1(:,4))/2);
%hold;
%scatter(Step2(:,6)/1000,(Step2(:,5)+Step2(:,4))/2, 15,'b','*') 
hold
P1=plot(Step2(:,6)/1000,(Step2(:,5)+Step2(:,4))/2, 'b')

%hold;
%scatter(Step1(:,6),Step1(:,4));
%scatter(Step2(:,6),Step2(:,4));
%hold
%scatter(PureP1(:,6),PureP1(:,4));
%hold
%scatter(PureP2(:,6),PureP2(:,4));
%hold
%scatter(PwithFF1(:,6),PwithFF1(:,4));
%scatter(PureP1(:,6)/1000,(PureP1(:,4)+PureP1(:,5))/2,15,'r', '*')
P2=plot(PureP1(:,6)/1000,(PureP1(:,4)+PureP1(:,5))/2,'r')

%scatter(PwithFF1(:,6)/1000,(PwithFF1(:,4)+PwithFF1(:,5))/2,15,[0 0.5 0], '*')
P3=plot(PwithFF1(:,6)/1000,(PwithFF1(:,4)+PwithFF1(:,5))/2)
set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
set( P2, 'color', '[0 .5 0]', 'LineWidth', 2 );
set( P3, 'color', '[0 0 1]', 'LineWidth', 2 );

title('Step response with and without control')
xlabel('Time [s]')
ylabel('Velocity [m \cdot s^{-1}]')
xlim([3 7]);
legend('Voltage step', 'P control','P control with Feed forward','Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)