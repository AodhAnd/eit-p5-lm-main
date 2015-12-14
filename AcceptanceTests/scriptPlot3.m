clear all;
close all;
clc;

% Read the data from the test
data = csvread('test3.csv');


%put the data according to their position
time1 = data(:,1);
time2 = data(:,1);

speed3 = data(:,2)

for x = 1:58
        if data(x,2) < 3
            speed1(x) = data(x,2);
            time2(x) = -10;
        end
        if data(x,2) > 3
            speed2(x) = data(x,2);
            time1(x) = -10;
        end
end
     speed2(x) = data(x,2);
        
% Plots
hold on
P1 = scatter(time1,speed1,'green');
P2 = scatter(time2,speed2,'red');
%P3 = scatter(time,speed3);
xlim([0 58]);

% Make the plots beautiful
% set( P1, 'color', '[0 0 1]', 'LineWidth', 2 );
title('Time vs Speed')
xlabel('Number of period')
ylabel('Speed [m \cdot s^{-1}]')

%ylim([0 10]);
legend('Speed above 3m \cdot s^{-1}','Speed below 3m \cdot s^{-1}')
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
