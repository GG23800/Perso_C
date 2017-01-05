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
	int i=0,Nbuff=12;
	int *buff_int=NULL;
	int16_t *buff=NULL;
	buff_int=(int *)malloc(Nbuff*sizeof(int));
	buff=(int16_t *)malloc(Nbuff*sizeof(uint16_t));

	while(1)
	{
		receive_int16_TCP_client(&client,buff,Nbuff);
		for (i=0 ; i<Nbuff ; i++)
		{
			printf("buff[%i] = %i\n",i,buff[i]);
		}
	}

	close_TCP_client(&client);

	return 0;
}

