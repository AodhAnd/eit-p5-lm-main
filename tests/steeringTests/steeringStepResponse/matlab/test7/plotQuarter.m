clear all;
clc;
clear home;

origin = [0,0,0];


data1 = csvread('quarter1.4.csv');
data2 = csvread('quarter2.4.csv');
data3 = csvread('quarter3.4.csv');
data4 = csvread('quarter4.4.csv');

%truedata = csvread('fullturnflat1.csv');

%figure = plot3(truedata(:,2),truedata(:,4),truedata(:,6),'bd');
%set(figure,'color','b');
%figure2 = plot3(truedata(:,3),truedata(:,5),truedata(:,7),'rd');
%set(figure2,'color','r');
%%hold;
%figure3 = plot3(0,0,0,'o','markeredgecolor','k','marker','*','markerSize',10);
%set(figure3,'color','k');

figure = plot3(data1(:,1),data1(:,2),data1(:,3),'.','markerSize',15);
set(figure,'color','b');
hold on;
figure2 = plot3(data2(:,1),data2(:,2),data2(:,3),'.','markerSize',15);
set(figure2,'color','r');
figure3 = plot3(data3(:,1),data3(:,2),data3(:,3),'.','markerSize',15);
set(figure3,'color','k');
figure4 = plot3(data4(:,1),data4(:,2),data4(:,3),'.','markerSize',15);
set(figure4,'color','g');
%hold;
figure0 = plot3(0,0,0,'o','markeredgecolor','k','marker','*','markerSize',10);
set(figure0,'color','k');


axis equal


grid on
xlim ([-500 500]);
ylim ([-500 500]);
zlim ([-800 800]);

%X = [truedata(:,2) truedata(:,4) truedata(:,6)] 
%Y = [truedata(:,3) truedata(:,5) truedata(:,7)] 

%[c1,r1] = sphereFit(X)
%[c2,r2] = sphereFit(Y)




%Creating legend containing equation for lsline (%0.4f = 4 decimals)
%legend('Data', sprintf( 'y = %0.4fx + %0.4f', a, b ), 'Location', 'northwest' )

%Title and axis labels added
title('Plot of magnitude with circle quarters')
xlabel('X [µT]')
ylabel('Y [µT]')
zlabel('Z [µT]')

grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)


%differnet coordinates of 0
%doubleraw2: -114.9936  134.0346   -9.5615
%doubleraw3: -96.1951  150.9983  -46.1978
%doubleraw4: -116.7155  132.9689   -4.0813
%doubleraw5: -110.5859  134.4870  -18.4628
%doubleraw6: -101.1932  129.1799  -31.7741