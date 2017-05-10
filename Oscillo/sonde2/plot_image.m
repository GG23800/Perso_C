clear all;
close all;

z=load("int380.txt");
z2=z;
% 50 80
[l,c]=size(z);
N=c;

x=zeros(l,c);
y=x;

x0=80;
xf=150;
sector=80;

r=linspace(x0,xf,N);
th=linspace(-sector/2*pi/180,sector/2*pi/180,l);

for j=1:N
  for k=1:l
    x(k,j)=r(j)*cos(th(k));
    y(k,j)=r(j)*sin(th(k));
  endfor
endfor

maxi=max(max(z))
figure(1)
surf(x,y,z);
shading interp;
view ([0 90]);
colormap gray;
caxis([0 maxi/1]);
axis square;
axis equal;
axis off;

fe=125/8;
f0=2;
fm=5;
df=fe/N;
n0=floor(f0/df)
nf=floor(fm/df)

for i=1:l
  tmp=fft(z(i,:));
  tmp(1:n0)=0;
  tmp(nf:N)=0;
  %tmp(nf+1:N-nf)=0;
  %tmp(N-n0:end)=0;
  tmp=abs(ifft(tmp));
  z(i,:)=tmp;
  z2(i,:)=20*log(tmp);
endfor

maxi=max(max(z))

figure(2)
surf(x,y,z);
shading interp;
view ([0 90]);
colormap gray;
caxis([0 maxi/2]);
%axis square;
%axis equal;
axis off;

maxi=max(max(z2))
figure(3)
surf(x,y,z2);
shading interp;
view ([0 90]);
colormap gray;
caxis([maxi-60 maxi]);
%axis square;
%axis equal;
axis off;

figure(4)
surf(z2);
shading interp;
view ([0 90]);
colormap gray;
caxis([maxi-60 maxi]);
%axis square;
%axis equal;
axis off;
