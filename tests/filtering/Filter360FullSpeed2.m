close all;
clear all;
clc;

%% Convert pisture from - and + degrees to only + degrees
Data1 = csvread('twoturns.3.csv');
Data1(:,2) = Data1(:,2)/1000;

Data1(73:192,1) = Data1(73:192,1)+360;
Data1(116:193,1) = Data1(116:193,1)+360;
Data1(193:231,1) = Data1(193:231,1)+360;

format long

fs = 40;
fm = fs/2;
ns = 20000;
w = linspace(1,2*pi*fm,ns);
f = w/(2*pi);
wd = w/(2*fm);
s = tf('s');
z = tf('z');
%H =  (73.61015518^(3))/((s^(2)-2*-1/2*73.61015518*s+73.61015518^(2))*(s-73.61015518*-1))
%bodeplot(H)
%% LOWPASS FILTER

%H = (0.4347829973e-2+0.2608697984e-1/z+0.6521744960e-1/z^2+0.8695659946e-1/z^3+0.6521744960e-1/z^4+0.2608697984e-1/z^5+0.4347829973e-2/z^6)/(1-1.974486371/z+2.241740971/z^2-1.460131921/z^3+.5920585105/z^4-.1343581056/z^5+0.1344675427e-1/z^6)
Hs = (3.98850*10^5*z^3+1.196550*10^6*z^2+1.196550*10^6*z+3.98850*10^5)/(2.720018353*10^6*z^3-4.146860770*10^5*z^2+9.234047870*10^5*z-37890.78300)
[num,den] = tfdata(Hs);
num = num{1}/(2.72e06);
den = den{1}/(2.72e06);
H = tf(num, den, 0.025, 'variable', 'z^-1')
den
H_freq = freqz(num, den, wd);
magdb = (abs(H_freq));

semilogx(f, magdb)

grid;
%figure;
%% FFT
%scatter(Data1(:,2),Data1(:,1));
%figure;

input = Data1(:,1);

input_fft = mag2db(abs(fft(input)));
%input_fft = abs(fft(input));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)
figure;

%% Test filter algorithm
BUF0 = 0;
BUF1 = 0;
BUF2 = 0;
BUF3 = 0;
BUF4 = 0;
BUF5 = 0;
BUF6 = 0;

a1 = - 0.1525;
a2 = 0.3395;
a3 = - 0.01393;

b0 = 0.1466;
b1 = 0.4399;
b2 = 0.4399;
b3 = 0.1466;


input = Data1(:,1);
output = zeros(369,1);
for i=1:369
   BUF0 = input(i) - (a1*BUF1 + a2*BUF2 + a3*BUF3);
   output(i) = BUF0*b0 + b1*BUF1 + b2*BUF2 + b3*BUF3;
   BUF3 = BUF2;
   BUF2 = BUF1;
   BUF1 = BUF0;
end

plot(Data1(:,2),Data1(:,1), 'b',Data1(:,2),output, 'r')
