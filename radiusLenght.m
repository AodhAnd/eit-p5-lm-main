clc;
clear all;



m1 = 3
m2 = 4
m3 = 5
%p = m1 + m2 + m3

a = m3
c = (a^2 - (m2)^2 + (m1)^2)/(2*a)
d = sqrt((m1^2) - (((m1^2) - (m2^2) + (m3^2))/(2*m3))^2)
%d = 2 * sqrt(p * (p -m1)*(p - m2)*(p-m3)/m1)



y = (c^2 - c*a + d^2)/(2*a)

r = sqrt((a/2)^2 + y^2)
