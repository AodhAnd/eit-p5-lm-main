close all;
clear all;
clc;

Data1 = csvread('StillAngle.csv');
Data1(:,2) = Data1(:,2)/1000;

Data1(:,1) = Data1(:,1)-147.8;

scatter(Data1(:,2),Data1(:,1))

format long

fs = 40;
fm = fs/2;
ns = 20000;
w = linspace(1,2*pi*fm,ns);
f = w/(2*pi);
wd = w/(2*fm);
s = tf('s');
z = tf('z');
%H = 8.500881141*10^7/(s^4+192.0418945*s^3*cos((1/8)*pi)+18440.04462*s^2+192.0418945*cos((3/8)*pi)*s^3+36880.08924*cos((3/8)*pi)*s^2*cos((1/8)*pi)+1.770630552*10^6*cos((3/8)*pi)*s+1.770630552*10^6*cos((1/8)*pi)*s+8.500881142*10^7)
%bodeplot(H)
%% LOWPASS FILTER

%H = (0.4347829973e-2+0.2608697984e-1/z+0.6521744960e-1/z^2+0.8695659946e-1/z^3+0.6521744960e-1/z^4+0.2608697984e-1/z^5+0.4347829973e-2/z^6)/(1-1.974486371/z+2.241740971/z^2-1.460131921/z^3+.5920585105/z^4-.1343581056/z^5+0.1344675427e-1/z^6)
Hs = (8.5009000*10^7*z^4+3.40036000*10^8*z^3+5.10054000*10^8*z^2+3.40036000*10^8*z+8.5009000*10^7)/(6.409741674*10^8*z^4+2.89405884*10^8*z^3+3.528825092*10^8*z^2+6.2981316*10^7*z+1.389052340*10^7)
[num,den] = tfdata(Hs);
num = num{1}/(6.41e08);
den = den{1}/(6.41e08);
H = tf(num, den, 0.025, 'variable', 'z^-1')
den
H_freq = freqz(num, den, wd);
magdb = 20*log10(abs(H_freq));

%bodeplot(Hs)

semilogx(f, magdb)

grid;
figure;

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


input = Data1(:,1);
output = zeros(183,1);
for i=1:183
   BUF0 = input(i) - (a1*BUF1 + a2*BUF2 + a3*BUF3 + a4*BUF4);
   output(i) = BUF0*b0 + b1*BUF1 + b2*BUF2 + b3*BUF3 + b4*BUF4;
   BUF4 = BUF3;
   BUF3 = BUF2;
   BUF2 = BUF1;
   BUF1 = BUF0;
end

plot(Data1(:,2),Data1(:,1), 'b',Data1(:,2),output, 'r')

%scatter(Data1(:,2),output)

%% FFT
%scatter(Data1(:,2),Data1(:,1));
%figure;

input = Data1(:,1);

%input_fft = mag2db(abs(fft(input)));
input_fft = mag2db(2/length(input)*abs(fft(input)));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)

figure;

inputfilter = output;

%input_fft = mag2db(abs(fft(input)));
input_fft = mag2db(2/length(inputfilter)*abs(fft(inputfilter)));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(output,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)

figure;

plot(Data1(:,2),Data1(:,1),Data1(:,2),output, 'r')
figure;