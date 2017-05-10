clear all;
close all;

y=load('mode0.txt');

s0=y(1,:);
s0=s0/max(s0);

y=load('mode1.txt');

s1=y(1,:);
s1=s1/max(s1);

x=0:1688;

figure(1)
plot(x,s0,x,s1);

figure(2)
plot(x,s0,x,s1);
xlim([1300 1500]);

mean0=mean(s0(1:845));
mean1=mean(s1(1:845));

db0=20*log10(1/mean0)
db1=20*log10(1/mean1)