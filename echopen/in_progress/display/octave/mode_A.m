clear all;
close all;

pkg load sockets;

% client initialisation
client = socket(AF_INET, SOCK_STREAM, 0);
server_info = struct("addr", "192.168.128.3", "port", 7538);
rc = connect(client, server_info);

%receive RP parameters
[msg, len] = recv(client,6);

r0=double(msg(1))
rf=double(msg(2))
dec=double(msg(3))
Nline=msg(4)
sector=double(msg(5))
toto=double(mod(msg(6)+256,256))

Npoint=int16(2*(rf-r0)*125/1.48/dec);
if Npoint>16384
  Npoint=16384;
endif
Npoint

Ndonne=2*(Npoint+1);
data=zeros(Nline,Npoint);
tmp=zeros(1,Ndonne);
tmp2=zeros(1,Npoint+1);

l0=12;
l1=23;

while ((l1!=1 && l0!=2))
  [tmp,len]=recv(client,(Npoint+1)*2,MSG_WAITALL);
   tmp2=typecast(tmp,"int16");
   l0=l1;
   l1=tmp2(1);
endwhile

env=data;
tgc=linspace(1,2,Npoint+1);
Nz=1024*2;
fe=125/8;
f0=1;
fm=6;
n0=floor(f0*Nz/fe);
nm=floor(fm*Nz/fe);

for i=1:Nline
  [tmp,len]=recv(client,(Npoint+1)*2,MSG_WAITALL);
   tmp2=typecast(tmp,"int16");
   figure(1)
   plot(tmp2);
   title(['line ',num2str(i)]);
   drawnow;
   %pause(0.1);
   data(tmp2(1),:)=tmp2(2:end);
   tmp2=tmp2.*tgc;
   tmp2=fft(tmp2,Nz);
   tmp2(1:n0)=0;
   tmp2(nm:end)=0;
   tmp2=ifft(tmp2);
   env(i,:)=abs(tmp2(1:Npoint));
endfor

figure(2)
surf(data);
shading interp;
view([0 90]);
colormap gray;
axis off;

figure(3)
surf(env);
shading interp;
view([0 90]);
colormap gray;
axis off;

figure(4)
surf(log(env));
shading interp;
view([0 90]);
colormap gray;
axis off;

env=20*log(env);
env=env/max(max(env));
figure(4)
surf(env);
shading interp;
view([0 90]);
colormap gray;
caxis([0.5 1])
axis off;

disconnect(client);