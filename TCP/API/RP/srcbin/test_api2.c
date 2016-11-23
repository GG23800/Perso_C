#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "rp.h"
#include "TCP_API.h"

#define PORT 7538
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

	int i, Nbuff=5;
	int * buff_int=NULL;
	char * buff=NULL;
	buff_int=(int*)malloc((Nbuff+1)*sizeof(int));
	buff=(char*)malloc((Nbuff+1)*sizeof(char));
	for (i=1 ; i<Nbuff+1 ; i++)
	{
		buff_int[i]=i;
		buff[i]=(char)buff_int[i];
	}

	while (1)
	{
		for (i=0 ; i<(int)client_list.NbClient ; i++)
		{
			buff_int[0]=(i+256)%256;
			buff[0]=(char)buff_int[0];
			printf("sending to client number %i\n",i);
			send_TCP_server(&client_list,buff,Nbuff+1,i);
			usleep(1);
		}
		usleep(1000000);
		//printf("number of client: %i\n",client_list.NbClient);
	}

	//Clean and close server
	close_TCP_server(&sock, &client_list);

	//Close RedPitaya
	end();             //min with 1.2 ms with 2048 points

	return 0;
}
