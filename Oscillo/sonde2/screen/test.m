clear all;
close all;

y=load('raw.txt');

s=y(64,:);

figure(1)
plot(s);

R=220;
C=1.45*10^(-9);
ra=10;
rb=1;

K=1+ra/rb;
f0=1/(2*pi*R*C);
Q=R*C/((1-K)*R*C+2*R*C);

f=linspace(0,10000000,16384);

H=K*1./(-f.*f/f0/f0+i*f/f0/Q+1);


figure(2)
loglog(f,abs(H));
ylim([0.5 10]);