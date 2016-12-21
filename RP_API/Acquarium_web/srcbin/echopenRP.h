#ifndef ECHOPENRP_H
#define ECHOPENRP_H

/*#include<signal.h>

#include"rp.h"
#include"stepper.h"
#include"TCP_API.h"*/

void init_ramp(int trigger, float level0, float x0, float levelf, float xf); //if trigger==1 ramp is made on trigger else ramp is made with function ramp(), ramp is level0 high at x0 and levelf high at xf
void ramp();
void end_ramp();
void init_variable(float x0, float xf, int dec, uint32_t *bufferlength, int *delay);
void set_acquisition(int dec);
void trigg();
void on_trigger_acquisition(float *buffer_float, uint32_t buffer_length);
void init_RP();
void close_RP();
void send_via_tcp(int line, char *buffer_char, float *buffer_float, uint32_t buffer_length, client *client_list);
void send_to_server(int line, char *buffer_char, float *buffer_float, uint32_t buffer_length, SOCKET *sock);
void init_pulse();
void pulse();

void init_ramp(int trigger, float level0, float x0, float levelf, float xf) 
{
	int i=0;
	uint32_t length=16384;
	float tmp=0.0, xmax=0.2;
	float *homeramp;
	homeramp=(float *)malloc(length*sizeof(float));
	x0=x0/1000;
	xf=xf/1000;

	if(level0<0.0){level0=0.0;}
	if(levelf>1.0){levelf=1.0;}
	if(x0<0.0){x0=0.0;}
	if(xf>xmax){xf=xmax;}

	float frequency=1480.0/xmax/2.0; //factor 2 for back and forth
	float lsamp=xmax/((double)length); //"length" sampling
	int N0=(int)(x0/lsamp); //x0 position
	int Nf=(int)(xf/lsamp); //xf position
	float slope=(levelf-level0)/((double)Nf-(double)N0); //slope of the ramp
	float initlevel=level0-slope*((double)N0); //level at first point

	//definition of the ramp
	for (i=0 ; i<length ; i++)
	{
		if (i<Nf)
		{
			tmp=slope*((double)i)+initlevel;
			if (tmp<0.0){tmp=0.0;}
			homeramp[i]=tmp;
		}
		else {homeramp[i]=levelf;}
	}

	rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
	rp_GenArbWaveform(RP_CH_1, homeramp, length);
	rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
	rp_GenBurstCount(RP_CH_1, 1);
	rp_GenAmp(RP_CH_1, 1.0);
	rp_GenFreq(RP_CH_1, frequency);

	if (trigger==1)
	{	
		rp_GenTriggerSource(RP_CH_1,RP_TRIG_SRC_CHA_PE); //to trigger on external trigger must put RP_TRIG_SRC_CHA_PE not RP_TRIG_SRC_EXT_PE...
		rp_GenOutEnable(RP_CH_1);
	}

	free(homeramp);
}

void ramp()
{
	rp_GenOutEnable(RP_CH_1);
}

void end_ramp() {rp_GenOutDisable(RP_CH_1);}

void init_variable(float x0, float xf, int dec, uint32_t *bufferlength, int *delay)
{
	float scale=2.0*125.0/1.48/((float)dec); //factor 2.0 for back and forth
	*bufferlength=(uint32_t)(scale*(xf-x0));
	if (*bufferlength>16384){*bufferlength=16384;}
	int Nf=0;
	Nf=(int)(scale*xf);
	*delay=Nf-8192;
}

void set_acquisition(int dec) 
{
	if (dec==1)
	{
		rp_AcqSetDecimation(RP_DEC_1);
	}
	else
	{
		rp_AcqSetDecimation(RP_DEC_8);
		rp_AcqSetAveraging(1);
	}
	rp_AcqSetGain(RP_CH_1,RP_HIGH); 	
}

void trigg(int delay) 
{
	rp_AcqStart();
	rp_AcqSetTriggerSrc(RP_TRIG_SRC_EXT_PE);
	rp_AcqSetTriggerDelay(delay); //if there is noise at the end can use -6550
}

void on_trigger_acquisition(float *buffer_float, uint32_t buffer_length)
{
	rp_acq_trig_state_t state = RP_TRIG_STATE_WAITING;
	while(1){
		rp_AcqGetTriggerState(&state);
		if(state == RP_TRIG_STATE_TRIGGERED){
			break;
		}
	}
	rp_AcqGetLatestDataV(RP_CH_1, &buffer_length, buffer_float);
}

void init_RP()
{
	if(rp_Init() != RP_OK)
	{
	printf("Rp api init failed!\n");
	}
	init_pulse();
}

void close_RP()
{
	end_ramp();
	rp_Release();
}

void send_via_tcp(int line, char *buffer_char, float *buffer_float, uint32_t buffer_length, client *client_list)
{
	int i=0;
	float tmpf, scale=0.9; //depend on maximum value of input, for test scale=1
	int tmp;
	buffer_char[0]=(char)line;
	for (i=0 ; i<buffer_length ; i++) 
	{
		tmpf=255.0/scale*buffer_float[i]+75.0;
		tmp=(int)tmpf;
		if (tmp<0) {tmp=-tmp;}
		if (tmp==0) {tmp=1;}
		if (tmp>255) {tmp=255;}
		buffer_char[i+1]=(char)tmp;
	}
	send_TCP_server(client_list, buffer_char, (int)buffer_length+1, -1);
}

void send_to_server(int line, char *buffer_char, float *buffer_float, uint32_t buffer_length, SOCKET *sock)
{
	int i=0;
	float tmpf, scale=0.9; //depend on maximum value of input, for test scale=1
	int tmp;
	buffer_char[0]=(char)line;
	char tmp_buffer[(int)buffer_length];
	for (i=0 ; i<buffer_length ; i++) 
	{
		tmpf=255.0/scale*buffer_float[i]+75.0;
		tmp=(int)tmpf;
		if (tmp<0) {tmp=-tmp;}
		if (tmp==0) {tmp=1;}
		if (tmp>255) {tmp=255;}
		buffer_char[i+1]=(char)tmp;
		tmp_buffer[i]=(char)tmp;
	}
	//send_TCP_client(sock, buffer_char, (int)buffer_length+1);
	send_TCP_client(sock, tmp_buffer, (int)buffer_length);
}

void init_pulse()
{
	rp_DpinSetDirection(RP_DIO7_N,1);
	rp_DpinSetState(RP_DIO7_N,0);
}

void pulse()
{
	rp_pinState_t state=0;
	rp_DpinGetState(RP_DIO7_N, &state);
	rp_DpinSetState(RP_DIO7_N, !state);
}

#endif
