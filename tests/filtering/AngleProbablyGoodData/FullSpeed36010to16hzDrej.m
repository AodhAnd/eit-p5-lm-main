close all;
clear all;
clc;

Data1 = csvread('Drej2.csv');
Data1(:,1) = Data1(:,1)/1000;

Data1(57:255,2) = Data1(57:255,2)+360;
Data1(153:255,2) = Data1(153:255,2)-360;

%Data1(60:121,2) = Data1(60:121,2)+360;
%Data1(121:121,2) = Data1(121:121,2)-360;

format long

plot(Data1(:,1),Data1(:,2))

%figure;

fs = 40;
fm = fs/2;
ns = 20000;
w = linspace(1,2*pi*fm,ns);
f = w/(2*pi);
wd = w/(2*fm);
Space = 0:1:1000;
s = tf('s');
z = tf('z');
H = 8.500881141*10^7/(s^4+192.0418945*s^3*cos((1/8)*pi)+18440.04462*s^2+192.0418945*cos((3/8)*pi)*s^3+36880.08924*cos((3/8)*pi)*s^2*cos((1/8)*pi)+1.770630552*10^6*cos((3/8)*pi)*s+1.770630552*10^6*cos((1/8)*pi)*s+8.500881142*10^7)
%bodeplot(H, Space)
%figure;
%% LOWPASS FILTER

%H = (0.4347829973e-2+0.2608697984e-1/z+0.6521744960e-1/z^2+0.8695659946e-1/z^3+0.6521744960e-1/z^4+0.2608697984e-1/z^5+0.4347829973e-2/z^6)/(1-1.974486371/z+2.241740971/z^2-1.460131921/z^3+.5920585105/z^4-.1343581056/z^5+0.1344675427e-1/z^6)
Hs = (8.500881141*10^7*z^4+3.400352456*10^8*z^3+5.100528685*10^8*z^2+3.400352456*10^8*z+8.500881141*10^7)/(6.409788286*10^8*z^4+2.894089112*10^8*z^3+3.528800656*10^8*z^2+6.298157993*10^7*z+1.389159704*10^7)
[num,den] = tfdata(Hs);
num = num{1}/(6.41e08);
den = den{1}/(6.41e08);
% H = tf(num, den, 0.025, 'variable', 'z^-1')
% den
H_freq = freqz(num, den, wd);
magdb = 20*log10(abs(H_freq));
 
%bodeplot(Hs)

%semilogx(f, magdb)

grid;
figure;
%% FFT
%scatter(Data1(:,2),Data1(:,1));
%figure;

% input = Data1(:,1);
% 
% input_fft = mag2db(abs(fft(input)));
% freq = linspace(0,40,length(input_fft));
% plot(freq,input_fft);
% figure;
% spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)
% 
% figure;

%% Test filter algorithm
BUF0 = 0;
BUF1 = 0;
BUF2 = 0;
BUF3 = 0;
BUF4 = 0;
BUF5 = 0;
BUF6 = 0;

a1 = 0.4515;
a2 = 0.5505;
a3 = 0.09825;
a4 = 0.02167;


b0 = 0.1326;
b1 = 0.5305;
b2 = 0.7957;
b3 = 0.5305;
b4 = 0.1326;


input = Data1(:,2);
output = zeros(255,1);
for i=1:255
   BUF0 = input(i) - (a1*BUF1 + a2*BUF2 + a3*BUF3 + a4*BUF4);
   output(i) = BUF0*b0 + b1*BUF1 + b2*BUF2 + b3*BUF3 + b4*BUF4;
   BUF4 = BUF3;
   BUF3 = BUF2;
   BUF2 = BUF1;
   BUF1 = BUF0;
end

plot(Data1(:,1),Data1(:,2), 'b',Data1(:,1),output, 'r')

figure;
%% FFT filter
input = Data1(:,2);

%input_fft = mag2db(abs(fft(input)));
input_fft = mag2db(2/length(input)*abs(fft(input)));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)

figure;

%% Make it B-E-Autiful
plot(Data1(:,1),Data1(:,2))

h_legend = legend('Measured Data', 'Location', 'southeast')

set(h_legend, 'fontsize', 12);
%limmiting the axes to remove zero results

%Title and axis labels added
title('Turning with Full Velocity')
xlabel('Time [s]', 'fontsize', 15)
ylabel('Angle [\circ]', 'fontsize', 15)

grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
 figure;
%% FFT with filter
inputfilter = output;

%input_fft = mag2db(abs(fft(input)));
input_fft = mag2db(2/length(inputfilter)*abs(fft(inputfilter)));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(output,hamming(20),19,100,40,'yaxis')


