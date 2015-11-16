close all;
clear all;
clear home;
clc;

Step1 = csvread('steps.csv');
Step2 = csvread('noP2.csv');
PureP1 = csvread('pureP1.csv');
PureP2 = csvread('pureP2.csv');
PwithFF1 = csvread('PwithFF1.csv');
PwithFF2 = csvread('PwithFF2.csv');
% = csvread('noP1.csv');
%data1 = csvread('noP1.csv');

Stepdata = [0.38 1.13 1.84 2.45 3 ; 7.89*0.2 7.75*0.4 7.52*0.6 7.29*0.8 6.97];

scatter(Stepdata(2,:),Stepdata(1,:));
%hold;
%scatter(Step1(:,5),Step1(:,2)/100);
%hold
%scatter(PureP1(:,6),PureP1(:,4));
%hold;
%scatter(PureP2(:,6),PureP2(:,4));
%hold
%scatter(PwithFF1(:,6),PwithFF1(:,4));
%hold;
%scatter(PwithFF2(:,6),PwithFF2(:,4));