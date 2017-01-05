#include<stdio.h>
#include<stdlib.h>

#include"TCP_API.h"

#define PORT 7538

float x0=0.0;
float xf=0.0;
int dec=0;
int Nline=0;
double sector=0.0;
int mode_RP=0;
int step=1;

/*int int_converter(char x)
{
	int y;
	y=(int)x+256;
	y=y%256;
	return y;
}*/

int main(int argc, char ** argv)
{
	const char *IP="192.168.1.74";
	SOCKET client;

	printf("waiting for connection\n");
	init_TCP_client(&client, IP, PORT);

	//usleep(60000000);
	int i=0,Nbuff=12;
	int *buff_int=NULL;
	int16_t *buff=NULL;
	//char set[5];
	buff_int=(int *)malloc(Nbuff*sizeof(int));
	buff=(int16_t *)malloc(Nbuff*sizeof(uint16_t));

	//receive_TCP_client(&client, set, 5);
	get_RP_settings(&client);
	/*for (i=0 ; i<5 ; i++)
	{
		printf("setting[%i] = %i\n",i,int_converter(set[i]));
	}*/
	printf("x0=%f\n",x0);
	printf("xf=%f\n",xf);
	printf("dec=%i\n",dec);
	printf("Nline=%i\n",Nline);
	printf("sector=%f\n",sector);

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

