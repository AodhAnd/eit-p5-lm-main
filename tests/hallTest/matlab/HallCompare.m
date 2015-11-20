clear all
close all;
clear home;
clc;

rt = 0.166/(2*pi)
N = 4773/187

data1 = csvread('data2.csv'); %unfiltered hall data

left1  = data1(:,1)-1.2;
right1 = data1(:,2)-1.2;
time1  = (data1(:,3)-3390)/1000; % [s]

%figure
%subplot(2,1,1);
sLeft1 = scatter( time1, left1, 12, [0 .5 1], '*' );
hold
sRight1 = scatter( time1, right1, 12, [0 .5 0], '*' );

xlim([1 3.7])
ylim([2 3])

%Title and axis labels added
title('Hall Data Without Filtering')
xlabel('Time (s)')
ylabel('Angular Velocity (rad\cdot s^{-1})')

%adding legend
legend('Left Belt', 'Right Belt', 'Location', 'northeast' )

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%%
clear all
close all;
clear home;
clc;

rt = 0.166/(2*pi)
N = 4773/187

data2 = csvread('data3.2.csv'); %filtered hall data

left2  = data2(:,2);
right2 = data2(:,3);
time2  = (data2(:,4)-1220)/1000; % [s]

%subplot(2,1,2);
sLeft2 = scatter( time2, left2, 12, 'b', '*' );
hold
sRight2 = scatter( time2, right2, 12, 'r', '*' );

xlim([1 3.7])
ylim([2 3])

%Title and axis labels added
title('Hall Data With Filtering')
xlabel('Time (s)')
ylabel('Angular Velocity (rad\cdot s^{-1})')

%adding legend
legend('Left Belt', 'Right Belt', 'Location', 'northeast' )

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)