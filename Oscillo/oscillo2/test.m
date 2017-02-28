clear all;
close all;

y=load("int7.txt");

figure(1)
plot(y);
%xlim([1100 1300]);

l=length(y);

fe=125;
f0=1;
fm=5;
df=fe/l;
n0=floor(f0/df)
nf=floor(fm/df)

%for i=1:l
  tmp=fft(y);
  tmp(1:n0)=0;
  tmp(nf:l)=0;
  %tmp(nf+1:N-nf)=0;
  %tmp(N-n0:end)=0;
  tmp=2*abs(ifft(tmp));
  z=tmp;
  %z2(i,:)=20*log(tmp);
%endfor

figure(2)
plot(z);
%xlim([10000 l]);