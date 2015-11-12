clear all;
clear home;
clc;

data = csvread('SwithP10percentstart2ms.txt');

scatter(data(:,6),data(:,4));