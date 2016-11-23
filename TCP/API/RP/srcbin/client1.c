#include<stdio.h>
#include<stdlib.h>

#include"TCP_API.h"

#define PORT 7538

int main(int argc, char ** argv)
{
	const char *IP="192.168.128.3";
	SOCKET client;

	printf("waiting for connection\n");
	init_TCP_client(&client, IP, PORT);

	//usleep(60000000);
	int i,Nbuff=5;
	int *buff_int;
	char *buff;
	buff_int=(int *)malloc(Nbuff*sizeof(int));
	buff=(char *)malloc(Nbuff*sizeof(char));

	receive_TCP_client(&client,buff,Nbuff);
	printf("message: ");
	for (i=0 ; i<Nbuff ; i++)
	{
		buff_int[i]=(int)(buff[i]);
		buff_int[i]=(buff_int[i]+256)%256;
		printf("%i ",buff_int[i]);
	}
	printf("\n");

	printf("preparing buffer :");
	for (i=0 ; i<Nbuff ; i++)
	{
		buff_int[i]=(buff_int[i]+1)*3;
		printf(" %i",buff_int[i]);
		buff[i]=(char)buff_int[i];
	}
	printf("\nbuffer done\n");
	send_TCP_client(&client,buff,Nbuff);
	printf("sent\n");

	close_TCP_client(&client);

	return 0;
}
