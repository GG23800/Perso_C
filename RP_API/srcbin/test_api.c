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

void writefile (uint32_t length, float *buffer)
{
	FILE *f=NULL;
	f=fopen("test.txt","w+");
	int i=0;
	for (i=0 ; i<(int)length ; i++){fprintf(f,"%f\n",buffer[i]);}
	fclose(f);
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
	int dec=8;
	init_RP(dec);
	float x0=0.0, xf=200.0;
	float level0=0.6, levelf=0.8;
	int delay=0;
	uint32_t buffer_length=0;
	init_ramp(1, level0, x0+5, levelf, xf-5); 
	float *buffer_float=NULL;
	char *buffer_char=NULL;
	int i=0, j=0;

	init_variable(x0, xf, dec, &buffer_length, &delay);
	buffer_float=(float *)malloc(((int)buffer_length)*sizeof(float));
	buffer_char=(char *)malloc(((int)buffer_length+1)*sizeof(char));
	printf("buffer length = %i\n",(int)buffer_length);
	printf("delay = %i\n",delay);

	int Nline=64;

	while(j<1)
	{
		for (i=0 ; i<Nline ; i++)
		{
			trigg(delay);
			pulse();
			on_trigger_acquisition(buffer_float, buffer_length);
			send_via_tcp(i+1, buffer_char, buffer_float, buffer_length, &client_list);
			pulse();
			usleep(3000);
		}
		for (i=Nline ; i>0 ; i--)
		{
			trigg(delay);
			pulse();
			on_trigger_acquisition(buffer_float, buffer_length);
			send_via_tcp(i, buffer_char, buffer_float, buffer_length, &client_list);
			pulse();
			usleep(3000);
		}
		j++;
	}
	writefile(buffer_length, buffer_float);

	//close TCP server
	close_TCP_server(&sock, &client_list);
	//close RedPitaya
	end_ramp();
	close_RP();
	free(buffer_float);
	free(buffer_char);

	return 0;
}
