clc;
clear all;


//input values
m1 = 3
m2 = 4
m3 = 5

//Coordinates of the middle point taking the two others as a system of coordinates
a = (m3^2 - (m2)^2 + (m1)^2)/(2*m3)
h = sqrt((m1^2) - (((m1^2) - (m2^2) + (m3^2))/(2*m3))^2)

//coordinates of the center of the circle
x = m3 / 2
y = (c^2 - c*a + d^2)/(2*a)

//Radius of circle
r = sqrt(x^2 + y^2
