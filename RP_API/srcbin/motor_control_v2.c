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

	//RedPitaya initialisation
	init_RP(1);
	float *buffer_float=NULL;
	char *buffer_char=NULL;
	uint32_t buffer_length=1024;
	int i=0, Nline=64;
	buffer_float=(float*)malloc(buffer_length*sizeof(float));
	buffer_char=(char*)malloc((buffer_length+1)*sizeof(char));

	while(1)
	{
		for (i=0 ; i<Nline ; i++)
		{
			trigg();
			on_trigger_acquisition(buffer_float, buffer_length);
			send_via_tcp(i+1, buffer_char, buffer_float, buffer_length, &client_list);
		}
		for (i=Nline ; i>0 ; i--)
		{
			trigg();
			on_trigger_acquisition(buffer_float, buffer_length);
			send_via_tcp(i, buffer_char, buffer_float, buffer_length, &client_list);
		}
	}

	//close RedPitaya
	end_ramp();
	close_RP();
	free(buffer_float);
	free(buffer_char);

	return 0;
}
