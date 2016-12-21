#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

#include"rp.h"
#include"stepper.h"
#include"TCP_API.h"
#include"echopenRP.h"

#define PORT 7538

float x0=50.0;
float xf=100.0;
int dec=8;
int Nline=128;
double sector=80.0;
SOCKET sock;
client client_list={.Nmax=0, .NbClient=0, .id_client=NULL, .sock_client=NULL, .sin_client=NULL};
stepper_motor(stepper);

void signal_callback_handler()
{
	disable_stepper(&stepper);
	close_TCP_client(&sock);
	close_RP();
}

int main(int argc, char** argv)
{
	//close server and RedPitaya if CTRL+C
	signal(SIGINT, signal_callback_handler);

	//client TCP initialisation
	unsigned int MaxClient=5;
	sock=0;

	init_TCP_server(&sock, PORT, &client_list, MaxClient);
	launch_server(&sock, &client_list);

	//RedPitaya and settings initialisation
	init_RP();
	uint32_t buffer_length=0;
	float  level0=0.10, levelf=1.0;
	int delay;

	float *buffer_float=NULL;
	char *buffer_char=NULL;

	set_acquisition(dec);
	init_ramp(1, level0, x0, levelf, xf);
	init_variable(x0, xf, dec, &buffer_length, &delay);
	printf("length = %i\n",(int)buffer_length);

	buffer_float=(float *)malloc(((int)buffer_length)*sizeof(float));
	buffer_char=(char *)malloc(((int)buffer_length+1)*sizeof(char));

	//stepper initialisation
	init_stepper(&stepper);
	set_mode(&stepper, full_16);
	double angle=0.0, speed=3.0;
	angle=sector/((double)Nline);
	init_position(&stepper, 160.0-sector/2.0);

	int i=0;

	while(1)
	{
		for (i=0 ; i<Nline ; i++)
		{
			move(&stepper, &angle, &speed, sens1);
			trigg(delay);
			pulse();
			on_trigger_acquisition(buffer_float, buffer_length);
			send_via_tcp(i+1, buffer_char, buffer_float, buffer_length, &client_list);
			pulse();
		}
		for (i=Nline ; i>0 ; i--)
		{
			move(&stepper, &angle, &speed, sens2);
			trigg(delay);
			pulse();
			on_trigger_acquisition(buffer_float, buffer_length);
			send_via_tcp(i, buffer_char, buffer_float, buffer_length, &client_list);
			pulse();
		}
		
	}

	free(buffer_float);
	free(buffer_char);
	end_ramp();
	disable_stepper(&stepper);
	printf("Process done\n");

	//close TCP client
	close_TCP_client(&sock);
	//close RedPitaya
	close_RP();

	return 0;
}
