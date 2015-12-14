clear all;
clc;
clear home;

truedata = csvread('doubleraw7.csv');

figure = plot3(truedata(:,2),truedata(:,4),truedata(:,6),'bd');
set(figure,'color','b','marker','o','markerSize',5);
hold;
figure2 = plot3(truedata(:,3),truedata(:,5),truedata(:,7),'rd');
set(figure2,'color','r','marker','o','markerSize',5);
figure3 = plot3(0,0,0,'markeredgecolor','k','marker','+','markerSize',6);
set(figure3,'color','k');



axis equal



xlim ([-500 500]);
ylim ([-500 500]);
zlim ([-500 500]);

X = [truedata(:,2) truedata(:,4) truedata(:,6)] 
Y = [truedata(:,3) truedata(:,5) truedata(:,7)] 

[c1,r1] = sphereFit(X)
[c2,r2] = sphereFit(Y)




%Creating legend containing equation for lsline (%0.4f = 4 decimals)
legend('Non-calibrated magnitude sphere', 'Calibrated magnitude sphere', 'Origin of the coordinate system', 'Location', 'southeast' )

%Title and axis labels added
title('Magnitude spheres')
xlabel('X [G]')
ylabel('Y [G]')
zlabel('Z [G]')

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)


%differnet coordinates of 0
%doubleraw2: -114.9936  134.0346   -9.5615
%doubleraw3: -96.1951  150.9983  -46.1978
%doubleraw4: -116.7155  132.9689   -4.0813
%doubleraw5: -110.5859  134.4870  -18.4628
%doubleraw6: -101.1932  129.1799  -31.7741