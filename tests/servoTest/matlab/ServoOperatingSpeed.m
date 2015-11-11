%%%%%% Servo operating speed %%%%%%

clc;
clear home;
clear all;

%%%% degrees to radians %%%%

rad = pi * 60/180

%%%%

Voltagevector = [4.8 6]; %obtained from the datasheet
Timevector = [rad/0.23 rad/0.19]; %obtained from the datasheet

scatter(Voltagevector, Timevector)

yL = get(gca,'YLim');
line([5 5],yL,'Color','b');

xlabel('Voltage', 'Fontsize', 20);
ylabel('Rad/s', 'Fontsize', 20);