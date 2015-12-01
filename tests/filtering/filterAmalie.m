close all;
clear all;
clc;

Data1 = csvread('twoturns.3.csv');
Data1(:,2) = Data1(:,2)/1000;

Data1 = Data1;
format long

fs = 40;
fm = fs/2;
ns = 20000;
w = linspace(1,2*pi*fm,ns);
f = w/(2*pi);
wd = w/(2*fm);
%s = tf('s');
z = tf('z');
%H = 9.8358*10^9/((s^2+23.961*s+2142.6)*(s^2+65.460*s+2142.6)*(s^2+89.422*s+2142.6))
%bodeplot(H)
%% LOWPASS FILTER

%H = (0.4347829973e-2+0.2608697984e-1/z+0.6521744960e-1/z^2+0.8695659946e-1/z^3+0.6521744960e-1/z^4+0.2608697984e-1/z^5+0.4347829973e-2/z^6)/(1-1.974486371/z+2.241740971/z^2-1.460131921/z^3+.5920585105/z^4-.1343581056/z^5+0.1344675427e-1/z^6)
Hs = (4.91800000*10^8*z^6+2.950800000*10^9*z^5+7.377000000*10^9*z^4+9.836000000*10^9*z^3+7.377000000*10^9*z^2+2.950800000*10^9*z+4.91800000*10^8)/(1.131121758*10^11*z^6-2.233379015*10^11*z^5+2.535665062*10^11*z^4-1.651572558*10^11*z^3+6.696848195*10^10*z^2-1.519746938*10^10*z+1.521009318*10^9)
[num,den] = tfdata(Hs);
num = num{1}/(1.131121758*10^(11));
den = den{1}/(1.131121758*10^(11));
H = tf(num, den, 0.025, 'variable', 'z^-1')
den
H_freq = freqz(num, den, wd);
magdb = 20*log10(abs(H_freq));

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


%% Test filter algorithm
BUF0 = 0;
BUF1 = 0;
BUF2 = 0;
BUF3 = 0;
BUF4 = 0;
BUF5 = 0;
BUF6 = 0;

a1 = -1.974;
a2 = 2.242;
a3 = -1.46;
a4 = 0.5921;
a5 = -0.1344;
a6 = 0.01345;

b0 = 0.004348;
b1 = 0.02609;
b2 = 0.06522;
b3 = 0.08696;
b4 = 0.06522;
b5 = 0.02609;
b6 = 0.004348;

input = Data1(:,1);
output = zeros(369,1);
for i=1:369
   BUF0 = input(i) - (a1*BUF1 + a2*BUF2 + a3*BUF3 + a4*BUF4 + a5*BUF5 + a6*BUF6);
   output(i) = BUF0*b0 + b1*BUF1 + b2*BUF2 + b3*BUF3 + b4*BUF4 + b5*BUF5 + b6*BUF6;
   BUF6 = BUF5;
   BUF5 = BUF4;
   BUF4 = BUF3;
   BUF3 = BUF2;
   BUF2 = BUF1;
   BUF1 = BUF0;
end

plot(Data1(:,2),Data1(:,1), 'b',Data1(:,2),output, 'r')
%scatter(Data1(:,2),output)

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
%grid on
%set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)