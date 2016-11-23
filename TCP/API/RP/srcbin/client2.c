#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

#include"TCP_API.h"

#define PORT 7538

SOCKET sock_client;

void ctrlc(int signum)
{
	close_TCP_client(&sock_client);
	exit(signum);
}

int main(int argc, char ** argv)
{
	signal(SIGINT,ctrlc);

	const char *IP="192.168.128.3";
	//SOCKET client;

	printf("waiting for connection\n");
	init_TCP_client(&sock_client, IP, PORT);

	int i, Nbuff=5;
	int *buff_int=NULL;
	char *buff=NULL;
	buff_int=(int *)malloc((Nbuff+1)*sizeof(int));
	buff=(char *)malloc((Nbuff+1)*sizeof(char));

	while (1)
	{
		if (receive_TCP_client(&sock_client,buff,Nbuff+1)==1){break;}
		printf("message: ");
		for (i=0 ; i<Nbuff ; i++)
		{
			buff_int[i]=(int)(buff[i]);
			buff_int[i]=(buff_int[i]+256)%256;
			printf("%i ",buff_int[i]);
		}
		printf("\n");
	}

	//close_TCP_client(&client);

	return 0;
}
