close all;
clear all;
clc;

Data1 = csvread('stilltest.csv');
Data1(:,2) = Data1(:,2);

Data1(:,1) = Data1(:,1)/1000;

%plot(Data1(:,1),Data1(:,2))

figure;

format long

fs = 66.667;
fm = fs/2;
ns = 20000;
w = linspace(1,2*pi*fm,ns);
f = w/(2*pi);
wd = w/(2*fm);
s = tf('s');
z = tf('z');
H = 3.8818*10^7/(s^4+206.264*s^3+21272.18190*s^2+1.285107226*10^6*s+3.881788416*10^7)
%bodeplot(H)
%figure;
%% LOWPASS FILTER

  %Hs = (8.5009000*10^7*z^4+3.40036000*10^8*z^3+5.10054000*10^8*z^2+3.40036000*10^8*z+8.5009000*10^7)/(6.409741674*10^8*z^4+2.89405884*10^8*z^3+3.528825092*10^8*z^2+6.2981316*10^7*z+1.389052340*10^7)
  %Hs = (4.0996000*10^7*z^4+1.63984000*10^8*z^3+2.45976000*10^8*z^2+1.63984000*10^8*z+4.0996000*10^7)/(4.360218108*10^8*z^4+2.370653600*10^5*z^3+2.11920835*10^8*z^2+49717.36000*z+7.704136840*10^6)
  % 30ms Hs = (4.099576169*10^7*z^4+1.639830468*10^8*z^3+2.459745701*10^8*z^2+1.639830468*10^8*z+4.099576169*10^7)/(3.08565976*10^8*z^4+1.400767645*10^8*z^3+1.700925742*10^8*z^2+3.049578912*10^7*z+6.701083335*10^6)
  Hs = (9.591487662*10^7*z^4+3.836595065*10^8*z^3+5.754892597*10^8*z^2+3.836595065*10^8*z+9.591487662*10^7)/(1.956614438*10^9*z^4-1.430324333*10^9*z^3+1.282376384*10^9*z^2-3.297405086*10^8*z+5.571204633*10^7)
  [num,den] = tfdata(Hs);
  num = num{1}/(1.957e09);
  den = den{1}/(1.957e09);
 H = tf(num, den, 0.015, 'variable', 'z^-1')
% den

 H_freq = freqz(num, den, wd);
 magdb = 20*log10(abs(H_freq));
% 
% %bodeplot(Hs)
% 
 %semilogx(f, magdb)
% 
 %grid;
 %figure;

%% Test filter algorithm
BUF0 = 0;
BUF1 = 0;
BUF2 = 0;
BUF3 = 0;
BUF4 = 0;

a1 = - 0.7309;
a2 = 0.6553;
a3 = - 0.1685;
a4 = 0.02847;


b0 = 0.04901;
b1 = 0.196;
b2 = 0.2941;
b3 = 0.196;
b4 = 0.04901;


input = Data1(:,2);
output = zeros(707,1);
for i=1:707
   BUF0 = input(i) - (a1*BUF1 + a2*BUF2 + a3*BUF3 + a4*BUF4);
   output(i) = BUF0*b0 + b1*BUF1 + b2*BUF2 + b3*BUF3 + b4*BUF4;
   BUF4 = BUF3;
   BUF3 = BUF2;
   BUF2 = BUF1;
   BUF1 = BUF0;
end

plot(Data1(:,1),Data1(:,2), 'b',Data1(:,1),output, 'r')

figure;
%scatter(Data1(:,2),output)

%% FFT without filter
% scatter(Data1(:,2),Data1(:,1));
% figure;
% 
% input = Data1(:,2);
% 
% %input_fft = mag2db(abs(fft(input)));
% input_fft = mag2db(2/length(input)*abs(fft(input)));
% freq = linspace(0,33.3,length(input_fft));
% %plot(freq,input_fft);
% figure;
% %spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)
% 
% figure;

%% Make it B-E-Autiful
%plot(Data1(:,1),Data1(:,2)) //Original data
%bodemag(Hs)
%semilogx(f, magdb)
%xlim([-.2 16.666665])
%legend('Measured data', 'Location', 'northwest' )
semilogx(f, magdb)

ylim([-50 1])

%Title and axis labels added

title('Frequency Response of Discrete-time Filter', 'fontsize', 13)
xlabel('Frequency [Hz]', 'fontsize', 12)
ylabel('Magnitude [dB]','fontsize', 12)

grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%% FFT with filter
% inputfilter = output;
% 
% %input_fft = mag2db(abs(fft(input)));
% input_fft = mag2db(2/length(inputfilter)*abs(fft(inputfilter)));
% freq = linspace(0,40,length(input_fft));
% plot(freq,input_fft);
% figure;
% spectrogram(output,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)
% 
% %figure;
% 
% %plot(Data1(:,2),Data1(:,1),Data1(:,2),output, 'r')
% %figure;

