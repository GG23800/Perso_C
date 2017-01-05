#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "rp.h"
#include "echopenRP.h"
#include "TCP_API.h"

#define PORT 7538

float x0=50.0;
float xf=150.0;
int dec=8;
int Nline=128;
double sector=80.0;
int mode_RP=0;
int step=1;

void end_acq() {rp_Release();};

void init(){
	if(rp_Init() != RP_OK){
		fprintf(stderr, "Rp api init failed!\n");
	}
}

void end() {
	end_acq();
}

// Define the function to be called when ctrl-c (SIGINT) signal is sent to process
void signal_callback_handler(){
	printf("Close TCP\n");
	end();
	exit(0);
}

int intpow(int x, int p)
{
	int i=0, y=1;
	for (i=0 ; i<=p ; i++){y*=x;}
	return y;
}

int main(int argc, char **argv){

	//initialize RedPitaya
	init();
	signal(SIGINT, signal_callback_handler);

	//initialize server
	client client_list={.Nmax=0, .NbClient=0, .id_client=NULL, .sock_client=NULL, .sin_client=NULL};
	unsigned int MaxClient=5;
	SOCKET  sock=0;

	init_TCP_server(&sock, PORT, &client_list, MaxClient);
	launch_server(&sock, &client_list);
	

	printf("test include TCP_PAI.h\n");

	int i, Nbuff=12;
	int * buff_int=NULL;
	int16_t * buff=NULL;
	buff_int=(int*)malloc((Nbuff+1)*sizeof(int));
	buff=(int16_t *)malloc((Nbuff+1)*sizeof(int16_t));
	for (i=1 ; i<Nbuff+1 ; i++)
	{
		buff_int[i]=intpow(-1,i)*4*i;
		buff[i]=(int16_t)buff_int[i];
		printf("buff[%i] = %i\n",i,buff[i]);
	}

	int loop=1;
	while (1)
	{
		buff_int[0]=loop;
		buff[0]=(int16_t)loop;
		printf("message number %i\n",loop);
		send_int16_TCP_server(&client_list,buff,Nbuff+1,-1);
		loop++;
		usleep(1000000);
	}

	//Clean and close server
	close_TCP_server(&sock, &client_list);

	//Close RedPitaya
	end();             //min with 1.2 ms with 2048 points

	return 0;
}

