clear all;
clc;
clear home;
close all;

data1 = csvread('quarter1.csv');
data2 = csvread('quarter2.csv');
data3 = csvread('quarter3.csv');
data4 = csvread('quarter4.csv');


figure = plot(data1(:,1),data1(:,2),'.','markerSize',15);
set(figure,'color','b');
hold on;
figure2 = plot(data2(:,1),data2(:,2),'.','markerSize',15);
set(figure2,'color','r');
figure3 = plot(data3(:,1),data3(:,2),'.','markerSize',15);
set(figure3,'color','k');
figure4 = plot(data4(:,1),data4(:,2),'.','markerSize',15);
set(figure4,'color','g');
%hold;
figure0 = plot(0,0,'o','markeredgecolor','k','marker','*','markerSize',10);
set(figure0,'color','k');

axis equal


grid on
xlim ([-400 400]);
ylim ([-400 400]);
zlim ([-800 800]);

%Creating legend containing equation for lsline (%0.4f = 4 decimals)
%legend('Data', sprintf( 'y = %0.4fx + %0.4f', a, b ), 'Location', 'northwest' )

%Title and axis labels added
title('Plot of magnitude with circle quarters','fontsize',12)
xlabel('X [G]','fontsize',12)
ylabel('Y [G]','fontsize',12)
zlabel('Z [G]','fontsize',12)

grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
