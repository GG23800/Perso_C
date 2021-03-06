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
int Nline=100;
double sector=60.0;
int mode_RP=0;
int step=1;
float level0=0.3;
float levelf=0.9;
int trigger=1;

data data_RP={.buffer_length=0, .delay=0, .sock=0, .client_list=NULL, .stepper=NULL, .stepper_mode=full, .angle=0.0, .buffer_char=NULL, .buffer_float=NULL, .buffer_int16=NULL};
data data_set={.buffer_length=0, .delay=0, .sock=0, .client_list=NULL, .stepper=NULL, .stepper_mode=full, .angle=0.0, .buffer_char=NULL, .buffer_float=NULL, .buffer_int16=NULL};


void signal_callback_handler()
{
	printf("signal callback handler\n");
	clear_data(&data_RP, &data_set);
	exit(0);//must exit whereas it return into main
}

int main (int agrc, char **argv)
{
	//close server and RedPitaya if CTRL+C
	signal(SIGINT, signal_callback_handler);

	double speed=3.0; //1 for dec8 3 for dec1

	//float level0=0.3;
	//float levelf=1.0;
	init_data(&data_RP, &data_set, 5, PORT, level0, levelf, full_16);  //full_16
	data_RP.angle=sector/((double)Nline-1);
	printf("angle = %lf\n",data_RP.angle);
	double sec;
	sec=((double)Nline)*data_RP.angle;
	printf("sector = %lf\n",sec);
	printf("buffer length = %i\n", (int)data_RP.buffer_length);
	//enable_stepper(&(data_RP.stepper));

	int i=1;
	int t=000;
	while(1)
	{
		for (i=0 ; i<Nline ; i++)
		{
			if (i!=0) {move(data_RP.stepper, &(data_RP.angle), &speed, sens1);}
			internal_trigger_acquisition_TCP(&data_RP, i+1);
			usleep(t);
		}
		//usleep(10000);
		for (i=Nline ; i>0 ; i--)
		{
			if (i!=Nline) {move(data_RP.stepper, &(data_RP.angle), &speed, sens2);}
			internal_trigger_acquisition_TCP(&data_RP, i);
			usleep(t);
		}
		//usleep(100000);
		/*if(i>Nline){i=1;}
		internal_trigger_acquisition_TCP(&data_RP, i);
		i++;*/
		//usleep(100000);
	}

	printf("close all\n");
	clear_data(&data_RP, &data_set);
	return 0;
}
