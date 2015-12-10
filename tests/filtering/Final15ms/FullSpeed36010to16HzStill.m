close all;
clear all;
clc;

Data1 = csvread('newtestamaliestuff5.csv');
Data1(:,2) = Data1(:,2);

Data1(:,1) = Data1(:,1)/1000;

plot(Data1(:,1),Data1(:,2))

figure;

format long

fs = 66.6;
fm = fs/2;
ns = 20000;
w = linspace(1,2*pi*fm,ns);
f = w/(2*pi);
wd = w/(2*fm);
s = tf('s');
z = tf('z');
H = 1.5340*10^9/(s^4+517.15*s^3+1.337235496*10^5*s^2+2.025521405*10^7*s+1.534053889*10^9);
%bodeplot(H)
%figure;
%% LOWPASS FILTER

  %Hs = (8.5009000*10^7*z^4+3.40036000*10^8*z^3+5.10054000*10^8*z^2+3.40036000*10^8*z+8.5009000*10^7)/(6.409741674*10^8*z^4+2.89405884*10^8*z^3+3.528825092*10^8*z^2+6.2981316*10^7*z+1.389052340*10^7)
  %Hs = (4.0996000*10^7*z^4+1.63984000*10^8*z^3+2.45976000*10^8*z^2+1.63984000*10^8*z+4.0996000*10^7)/(4.360218108*10^8*z^4+2.370653600*10^5*z^3+2.11920835*10^8*z^2+49717.36000*z+7.704136840*10^6)
%   30ms Hs = (4.099576169*10^7*z^4+1.639830468*10^8*z^3+2.459745701*10^8*z^2+1.639830468*10^8*z+4.099576169*10^7)/(3.08565976*10^8*z^4+1.400767645*10^8*z^3+1.700925742*10^8*z^2+3.049578912*10^7*z+6.701083335*10^6)
%   Hs = (3.83500000*10^8*z^4+1.534000000*10^9*z^3+2.301000000*10^9*z^2+1.534000000*10^9*z+3.83500000*10^8)/(2.038443785*10^9*z^4+1.955484495*10^9*z^3+1.586493482*10^9*z^2+4.80579825*10^8*z+7.5213969*10^7)
%   [num,den] = tfdata(Hs);
%   num = num{1}/(2.038e09);
%   den = den{1}/(2.038e09);
%  H = tf(num, den, 0.015, 'variable', 'z^-1')
% den
% 
%  H_freq = freqz(num, den, wd);
%  magdb = 20*log10(abs(H_freq));
% 
% %bodeplot(Hs)
% % 
% semilogx(f, magdb)
% % 
%  grid;
%  figure;

%% Test filter algorithm
% BUF0 = 0;
% BUF1 = 0;
% BUF2 = 0;
% BUF3 = 0;
% BUF4 = 0;
% 
% a1 = 0.9595;
% a2 = 0.7785;
% a3 = 0.2358;
% a4 = 0.03691;
% 
% 
% b0 = 0.1882;
% b1 = 0.7527;
% b2 = 1.129;
% b3 = 0.7527;
% b4 = 0.1882;
% 
% 
% input = Data1(:,2);
% output = zeros(572,1);
% for i=1:572
%    BUF0 = input(i) - (a1*BUF1 + a2*BUF2 + a3*BUF3 + a4*BUF4);
%    output(i) = BUF0*b0 + b1*BUF1 + b2*BUF2 + b3*BUF3 + b4*BUF4;
%    BUF4 = BUF3;
%    BUF3 = BUF2;
%    BUF2 = BUF1;
%    BUF1 = BUF0;
% end
% 
% plot(Data1(:,1),Data1(:,2), 'b',Data1(:,1),output, 'r')
% 
% figure;
%scatter(Data1(:,2),output)

%% FFT without filter
% scatter(Data1(:,2),Data1(:,1));
% figure;
% 
 input = Data1(:,2);
%  
%  %input_fft = mag2db(abs(fft(input)));
  input_fft = mag2db(2/length(input)*abs(fft(input)));
  freq = linspace(0,33.3,length(input_fft));
% plot(freq,input_fft);
%  figure;
% spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)
% % 
%  figure;

%% Make it B-E-Autiful
%plot(Data1(:,1),Data1(:,2)) %Original data
%bodemag(H)
%semilogx(f, magdb)
plot(freq,input_fft)
%xlim([-.2 16.66])
%legend('Measured data', 'Location', 'northwest' )
%semilogx(f, magdb)

ylim([-50 1])

%Title and axis labels added

title('Frequency Response of Filter', 'fontsize', 13)
xlabel('Frequency [Hz]', 'fontsize', 12)
ylabel('Magnitude [dB]','fontsize', 12)

grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

%% FFT with filter
 %inputfilter = output;

% %input_fft = mag2db(abs(fft(input)));
%  input_fft = mag2db(2/length(inputfilter)*abs(fft(inputfilter)));
%  freq = linspace(0,40,length(input_fft));
%  plot(freq,input_fft);
%  figure;
% spectrogram(output,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)
% 
% %figure;

% %plot(Data1(:,2),Data1(:,1),Data1(:,2),output, 'r')
% %figure;

