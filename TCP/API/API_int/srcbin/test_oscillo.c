#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
#include<signal.h>

#include "oscilloRP.h"

#define PORT 7538

float x0=80.0;
float xf=160.0;
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

	double speed=3.0; //1 for dec8 3 for dec1

	//data data_RP;
	float level0=0.3;
	float levelf=1.0;
	init_data(&data_RP, 5, PORT, level0, levelf, full);  //full_16
	data_RP.angle=sector/((double)Nline);
	printf("buffer length = %i\n", (int)data_RP.buffer_length);

	data_RP.buffer_length=16384;
	data_RP.delay=8192;
	//enable_stepper(&(data_RP.stepper));

	while(1)
	{
		external_trigger_acquisition_TCP(&data_RP, i+1);
	}

	printf("close all\n");
	clear_data(&data_RP);
	return 0;
}
