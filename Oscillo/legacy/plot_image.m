clear all;
close all;

tmp=load("00fouet1.txt");

Npoint=1024;
Nline=64;
x=zeros(Npoint,Nline);
y=x;
z=x;

for i=1:Npoint
  for j=1:Nline
    x(i,j)=tmp(Npoint*(j-1)+i,1);
    y(i,j)=tmp(Npoint*(j-1)+i,2);
    z(i,j)=tmp(Npoint*(j-1)+i,3);
  endfor
endfor


clear tmp;

h=figure(1);
surf(x,y,z);
view(0,90);
xlim([100 225]);
ylim([-110 110]);
shading interp;
colormap bone;
axis equal;
set(h,"visible","off");
print(h,"-mono","test.fig");
set(h,'visible','on');