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

	init_data(&data_RP, 5, PORT, level0, levelf, full_16);  //full_16
	data_RP.angle=sector/((double)Nline);
	//enable_stepper(&(data_RP.stepper));

	double speed=3.0, ang=0.9;
	int i=0;

	while(1)
	{
		for (i=0 ; i<64 ; i++)
                {
                    move(data_RP.stepper, &ang, &speed, sens1);
                }
                for (i=0 ; i<64 ; i++)
                {
                    move(data_RP.stepper, &ang, &speed, sens2);
                }
	}

	printf("close all\n");
	clear_data(&data_RP);
	return 0;
}
