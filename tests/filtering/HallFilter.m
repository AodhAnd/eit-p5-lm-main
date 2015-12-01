clc;
clear home;
clear all;
close all;

Data1 = csvread('data3.2.csv');

scatter(Data1(:,4),Data1(:,3));

%scatter(Data1(:,3),Data1(:,4));

figure;

input = Data1(:,3);

%input_fft = mag2db(abs(fft(input)));
input_fft = abs(fft(input));
freq = linspace(0,40,length(input_fft));
plot(freq,input_fft);
figure;
spectrogram(input,hamming(20),19,100,40,'yaxis') %fft for hvert sekund (40)