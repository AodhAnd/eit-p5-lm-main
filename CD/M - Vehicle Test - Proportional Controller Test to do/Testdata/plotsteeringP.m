close all;
clear all;
clear home;
clc;

Step1 = csvread('Ptest - working.csv');
Step2 = csvread('noP2.csv');
PureP1 = csvread('pureP1.csv');
PureP2 = csvread('pureP2.csv');
PwithFF1 = csvread('PwithFF1.csv');
PwithFF2 = csvread('PwithFF2.csv');
%Ptest = csvread('Ptest.csv'); Yesterday = to fast
% = csvread('noP1.csv');
%data1 = csvread('noP1.csv');

scatter(Step1(:,6),(Step1(:,5)+Step1(:,4))/2);
%hold;
%scatter(Step1(:,6),Step1(:,4));
%scatter(Step2(:,6),Step2(:,4));
%hold
%scatter(PureP1(:,6),PureP1(:,4));
%hold;
%scatter(PureP2(:,6),PureP2(:,4));
%hold
%scatter(PwithFF1(:,6),PwithFF1(:,4));
%hold;
%scatter(PwithFF2(:,6),PwithFF2(:,4));