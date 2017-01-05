#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<signal.h>

#include "echopenRP.h"

#define PORT 7538

float x0=50.0;
float xf=150.0;
int dec=8;
int Nline=128;
double sector=80.0;
int mode_RP=1;
int step=1;

data data_RP={.buffer_length=0, .delay=0, .client_list=NULL, .stepper_mode=full, .angle=0.0, .buffer_char=NULL, .buffer_float=NULL, .buffer_int16=NULL};

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

	//data data_RP;
	float level0=0.0;
	float levelf=1.0;
	init_data(&data_RP, 5, PORT, level0, levelf, full_16);
	printf("buffer length = %i\n", (int)data_RP.buffer_length);

	int i=1;
	while(1)
	{
		if(i>Nline){i=1;}
		internal_trigger_acquisition_TCP(&data_RP, i);
		i++;
		//usleep(100000);
	}

	printf("close all\n");
	clear_data(&data_RP);
	return 0;
}
