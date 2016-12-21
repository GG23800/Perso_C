#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

#include"rp.h"
#include"stepper.h"
#include"TCP_API.h"
#include"echopenRP.h"

#define PORT 9000
#define Nset 8

float x0=0.0;
float xf=0.0;
int dec=1;
int Nline=64;
double sector=60.0;
SOCKET sock;

void signal_callback_handler()
{
	close_TCP_client(&sock);
	close_RP();
}

void convert(char *settings, int *isettings)
{
	int i=0;
	for (i=0 ; i<Nset ; i++)
	{
		isettings[i]=128*((int)settings[2*i])+(int)settings[2*i+1];
	}
}

int main(int argc, char** argv)
{
	//close server and RedPitaya if CTRL+C
	signal(SIGINT, signal_callback_handler);

	//client TCP initialisation
	const char *IP="192.168.1.119";//"92.243.29.92";
	sock=0;
	init_TCP_client(&sock, IP, PORT);

	//RedPitaya and settings initialisation
	init_RP();
	char settings[2*Nset];
	int isettings[Nset];
	uint32_t buffer_length=0;
	float  level0=0.0, levelf=0.0;
	int Nline=0, Nimage=0;
	int delay;

	//stepper initialisation
	stepper_motor stepper;
	init_stepper(&stepper);
	set_mode(&stepper, full_16);
	double angle=0.0, speed=3.0;
	disable_stepper(&stepper);

	int i=0, j=0;

	while(1)
	{
		if (receive_TCP_client(&sock,settings,2*Nset)==1)
		{
			printf("Server disconnected\n");
			break;
		}

		float *buffer_float=NULL;
		char *buffer_char=NULL;

		convert(settings, isettings);
		for (i=0 ; i<Nset ; i++)
		{
			printf("setting %i = %i\n",i,isettings[i]);
		}
		dec=isettings[0];
		x0=(float)isettings[1];
		xf=(float)isettings[2];
		level0=((float)settings[3])/255.0;
		levelf=((float)settings[4])/255.0;
		sector=(double)settings[5];
		Nline=isettings[6];
		Nimage=isettings[7];
		printf("dec = %i\n",dec);
		printf("x0 = %f\n",x0);
		printf("xf = %f\n",xf);
		printf("l0 = %f\n",level0);
		printf("lf = %f\n",levelf);
		printf("sector = %f\n",sector);
		printf("Nline = %i\n",Nline);
		printf("Nimage = %i\n",Nimage);
		//send_TCP_client(&sock, settings, Nset);

		set_acquisition(dec);
		init_ramp(1, level0, x0, levelf, xf);
		init_variable(x0, xf, dec, &buffer_length, &delay);
		//printf("length = %i\n",(int)buffer_length);

		buffer_float=(float *)malloc(((int)buffer_length)*sizeof(float));
		buffer_char=(char *)malloc(((int)buffer_length+1)*sizeof(char));

		enable_stepper(&stepper);
		usleep(1000);

		angle=sector/((double)Nline);
		init_position(&stepper, 160-((int)sector)/2);
		usleep(1000);

		for (i=0 ; i<Nimage ; i++)
		{
			printf("image number %i\n",i);
			for (j=0 ; j<Nline ; j++)
			{
				move(&stepper, &angle, &speed, sens1);
				trigg(delay);
				pulse();
				on_trigger_acquisition(buffer_float, buffer_length);
				send_to_server(i+1, buffer_char, buffer_float, buffer_length, &sock);
				pulse();
			}
			sector=((double)Nline)*angle;
			move(&stepper, &sector, &speed, sens2);
		}

		free(buffer_float);
		free(buffer_char);
		end_ramp();
		disable_stepper(&stepper);
		printf("Process done\n");
	}

	//close TCP client
	close_TCP_client(&sock);
	//close RedPitaya
	close_RP();

	return 0;
}
