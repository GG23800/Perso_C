#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<signal.h>

#include "echopenRP.h"

#define PORT 7538

float r0=80.0;
float rf=160.0;
int dec=8;
int Nline=64;
double sector=80.0;
int mode_RP=0;
int step=1;

data data_RP={.buffer_length=0, .delay=0, .sock=0, .client_list=NULL, .stepper=NULL, .stepper_mode=full, .angle=0.0, .buffer_char=NULL, .buffer_float=NULL, .buffer_int16=NULL};

void signal_callback_handler()
{
	printf("signal callback handler\n");
	clear_data(&data_RP);
	exit(0);//must exit whereas it return into main
}

int main (int agrc, char **argv)
{
	//close server and RedPitaya if CTRL+C
	signal(SIGINT, signal_callback_handler);


	data data_RP;
	float level0=0.3;
	float levelf=1.0;

	init_data(&data_RP, 5, PORT, level0, levelf, full);  //full_16
	data_RP.angle=sector/((double)Nline);
	//enable_stepper(&(data_RP.stepper));

	int16_t *x1=(int16_t *)malloc(((int)data_RP.buffer_length+1)*sizeof(int16_t));
	int16_t *x2=(int16_t *)malloc(((int)data_RP.buffer_length+1)*sizeof(int16_t));

	int i=1;

	x1[0]=1.0;
	x2[0]=2.0;

	for (i=1 ; i<data_RP.buffer_length+1 ; i++)
	{
		x1[i]=(int16_t)i;
		x2[i]=x1[i]*2;
	}

	printf("buffer done\n");

	while(1)
	{
		for (i=0 ; i<1 ; i++)
		{
			send_int16_TCP_server((data_RP.client_list), x1, (int)data_RP.buffer_length+1, -1);
		}

		for (i=1 ; i>0 ; i--)
		{
			send_int16_TCP_server((data_RP.client_list), x2, (int)data_RP.buffer_length+1, -1);
		}
	}

	printf("close all\n");
	free(x1);
	free(x2);
	clear_data(&data_RP);
	return 0;
}
