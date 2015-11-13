clear all;
clear home;
clc;

data = csvread('Ptest.csv');

scatter(data(:,6),data(:,4));
hold;
scatter(data(:,6),data(:,5));
