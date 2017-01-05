#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "TCP_API.h"

#define PORT 7538

float x0=50.0;
float xf=150.0;
int dec=8;
int Nline=128;
double sector=80.0;
int mode_RP=0;
int step=1;

int intpow(int num, int p)
{
	int i=0, res=1;
	for (i=0 ; i<p ; i++){res*=num;}
	return res;
}

int main(int argc, char **argv){

	//initialize server
	client client_list={.Nmax=0, .NbClient=0, .id_client=NULL, .sock_client=NULL, .sin_client=NULL};
	unsigned int MaxClient=5;
	SOCKET  sock=0;

	init_TCP_server(&sock, PORT, &client_list, MaxClient);
	launch_server(&sock, &client_list);
	

	printf("test TCP_API.h\n");
	usleep(10000000);

	int i, Nbuff=12;
	int * buff_int=NULL;
	int16_t * buff=NULL;

	buff_int=(int *)malloc(Nbuff*sizeof(int));
	buff=(int16_t *)malloc(Nbuff*sizeof(int16_t));
	for (i=0 ; i<Nbuff ; i++)
	{
		buff_int[i]=intpow(-1,i)*4*i;
		buff[i]=(int16_t)buff_int[i];
	}

	while(1)
	{
		send_int16_TCP_server(&client_list,buff,Nbuff,-1);
		usleep(500000);
	}
	
	for (i=0 ; i<Nbuff ; i++)
	{
		printf("buff[%i] = %i\n",i,buff[i]);
	}
	//Clean and close server
	close_TCP_server(&sock, &client_list);

	return 0;
}
