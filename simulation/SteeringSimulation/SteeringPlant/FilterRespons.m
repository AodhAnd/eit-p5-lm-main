close all;
clear all;
clc;



v= 1.4
Ks = 0.5149 * v - 0.1925
%offset = 1360 + 270

 %csvwrite('Filtersimulation.csv',ScopeData);
 %datasim = csvread('sim1.csv');
% 
% Data1 = csvread('stepResponse1670.csv');
% Data2 = csvread('stepResponse1670.2.csv');
 FilterSim = csvread('Filtersimulation.csv');
% Datasim = csvread('sim1.csv');
% 
    time = FilterSim(:,1);
    Data1 = FilterSim(:,2);
    Data2 = FilterSim(:,3);
    
% 
% time   = Data1(:,1);
% angle  = Data1(:,2);
% time2  = Data2(:,1);
% angle2 = Data2(:,2);
% timesim  = Datasim(:,1)*1000;
% anglesim = Datasim(:,2);
% 
% hold;
% P1 = scatter(time,angle,'b');
% P2 = scatter(time2,angle2,'g');
% Psim = plot(timesim,anglesim,'LineWidth',2,'color','r');
% 
    plot(time,Data1);
    hold
    plot(time,Data2);
% 
% xlim([2000 10000]);
% ylim([-50 150]);
% 
% title('Step response at a PWM of 1670 m \cdot s{-1}')
% xlabel('Time [ms]')
% ylabel('Angle [°]')
% 
% legend('First test', 'Second test','Simulation','Location', 'northwest' )
% grid on
% set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)