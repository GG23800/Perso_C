#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

#include"rp.h"
#include"stepper.h"
#include"TCP_API.h"
#include"echopenRP.h"

#define PORT 7538

client client_list={.Nmax=0, .NbClient=0, .id_client=NULL, .sock_client=NULL, .sin_client=NULL};
SOCKET sock;

void signal_callback_handler()
{
	close_TCP_server(&sock, &client_list);
	close_RP();
}

int main(int argc, char** argv)
{
	//close server and RedPitaya if CTRL+C
	signal(SIGINT, signal_callback_handler);

	//server TCP initialisation
	unsigned int MaxClient=5;
	sock=0;

	init_TCP_server(&sock, PORT, &client_list, MaxClient);
	launch_server(&sock, &client_list);

	//RedPitaya initialisation
	init_RP(1);
	float *buffer_float=NULL;
	char *buffer_char=NULL;
	uint32_t buffer_length=1024;
	int i=0;
	buffer_float=(float*)malloc(buffer_length*sizeof(float));
	buffer_char=(char*)malloc((buffer_length+1)*sizeof(char));

	for (i=0 ; i<buffer_length ; i++)
	{
		buffer_float[i]=((float)i)/1023.0;
	}

	//stepper initialisation
	stepper_motor stepper;
	init_stepper(&stepper);
	set_mode(&stepper, full_8);

	double angle=0.0, speed=2.0;
	double sector=60.0;
	int Nline=64;
	angle=sector/((double)Nline);
	init_position(&stepper, 120);

	while(1)
	{
		for (i=0 ; i<Nline ; i++)
		{
			move(&stepper, &angle, &speed, sens1);
			pulse();
			send_via_tcp(i+1, buffer_char, buffer_float, buffer_length, &client_list);
			usleep(3000);
		}
		for (i=Nline ; i>0 ; i--)
		{
			move(&stepper, &angle, &speed, sens2);
			pulse();
			send_via_tcp(i, buffer_char, buffer_float, buffer_length, &client_list);
			usleep(3000);
		}
	}

	//close TCP server
	close_TCP_server(&sock, &client_list);
	//close RedPitaya
	close_RP();
	free(buffer_float);
	free(buffer_char);

	return 0;
}
