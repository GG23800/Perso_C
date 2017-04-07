clear all;
close all;

z=load("int360.txt");
z2=z;
% 50 80
[l,N]=size(z);

x=zeros(l,N);
y=x;

x0=80;
xf=160;
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
%axis square;
%axis equal;
axis off;

zi=20*log10(z);
maxi=max(max(zi));
figure(2)
surf(x,y,z);
shading interp;
view([0 90]);
colormap gray;
caxis([maxi-45 maxi]);
axis off;