clear all;
close all;

c1=4222;

x1=zeros(1,18);
x2=zeros(1,18);

for i=0:10:330

  name=['int',num2str(i),'.txt'];
  %printf("name: %s\n",name);
  
  y=load(name);
  y2=y;
  [l,N]=size(y);
  
  sec=56.7;
  r0=0;
  rf=200;
  r=linspace(r0,rf,N);
  %th=linspace(-sec/2*pi/180,sec/2*pi/180,l);
  %amp0=linspace(1,500,N/2);
  %amp1=linspace(500,500,N/2+1);
  %amp=[amp0,amp1];
  amp=linspace(1,1,N);
  
  fe=125/8;
  f0=0.5;
  fm=7;
  df=fe/N;
  n0=floor(f0/df);
  nf=floor(fm/df);
  
  for j=1:l
    tmp=fft(y(j,:));
    tmp(1:n0)=0;
    tmp(nf:N)=0;
    tmp=abs(ifft(tmp));
    y2(j,:)=tmp.*amp;
  endfor
  
  y2=abs(y2/max(max(abs(y2))));
  %y2=20*log10(y2);
  
  figure(1)
  surf(y2);
  shading interp;
  view([0 90]);
  colormap gray;
  axis off;
  drawnow;
  title(["image ",num2str(i),"/100"]);
  caxis([10^(-9) 0.5]);
  pause(0.1);
  
  [l,c2]=max(max(y2(:,1:N)));
  %x1(i)=1480*c2/fe/2000;
  %x2(i)=l;
  c1=c2;
  
endfor

[l,c2]=max(y2);
figure(3)
plot(l);

x2=x2/max(x2);

figure(2)
plot(y(32,:));