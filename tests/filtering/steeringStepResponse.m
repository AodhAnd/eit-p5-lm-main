close all;
clear all;
clc;

Data1 = csvread('twoturns.3.csv');
Data1(:,2) = Data1(:,2)/1000;
%Data2 = csvread('zigzag1600and1070.3.csv');
%Data3 = csvread('test1650.csv');

%Step1(:,2) = Data1(:,1)+180;    %angle
%for(
%if(Step1(:,2)>360) {Step1(:,2) = Step1(:,2) - 180;}
%Step1(:,1) = Data1(:,2);        %time
%Step2(:,2) = Data2(:,1);
%Step2(:,1) = Data2(:,4);
%Step3(:,2) = Data3(:,1);
%Step3(:,1) = Data3(:,4);
format long

fs = 40;
fm = fs/2;
w = linspace(1,2*pi*fm,20000);
f = w/(2*pi);
wd = w/(2*fm);
s = tf('s');
z = tf('z');
H = 9.8358*10^9/((s^2+23.961*s+2142.6)*(s^2+65.460*s+2142.6)*(s^2+89.422*s+2142.6))
bodeplot(H)
%%


%H = (0.4347829973e-2+0.2608697984e-1/z+0.6521744960e-1/z^2+0.8695659946e-1/z^3+0.6521744960e-1/z^4+0.2608697984e-1/z^5+0.4347829973e-2/z^6)/(1-1.974486371/z+2.241740971/z^2-1.460131921/z^3+.5920585105/z^4-.1343581056/z^5+0.1344675427e-1/z^6)
H = 9.8358*10^9*(z+1.)^6/((10459.5*z^2-8514.8*z+6625.7)*(13779.4*z^2-8514.8*z+3305.8)*(15696.4*z^2-8514.8*z+1388.8))
[num,den] = tfdata(H);
num = num{1};
den = den{1};
H = tf(num, den, 0.025, 'variable', 'z^-1')

H_freq = freqz(num, den, wd);
magdb = 20*log(abs(H_freq));

semilogx(f, magdb)

grid;
figure;
%% FFT
scatter(Data1(:,2),Data1(:,1));
figure;

input = Data1(:,1);

%input_fft = mag2db(abs(fft(input)));
input_fft = abs(fft(input));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)

%% Noise
%hold;
%P1 = plot(Step1(:,1),Step1(:,2));
%P2 = plot(Step2(:,1),Step2(:,2));
%P3 = plot(Step3(:,1),Step3(:,2));

%set( P1, 'color', '[1 0 0]', 'LineWidth', 2 );
%set( P2, 'color', '[0 .5 0]', 'LineWidth', 2 );
%set( P3, 'color', '[0 0 1]', 'LineWidth', 2 );

%title('Step response with and without control')
%xlabel('Time [s]')
%ylabel('Velocity [m \cdot s^{-1}]')
% xlim([3 7]);
%legend('Voltage step', 'P control','P control with Feed forward','Location', 'southeast' )
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)