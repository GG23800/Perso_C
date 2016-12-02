#ifndef ECHOPENRP_H
#define ECHOPENRP_H

/*#include<signal.h>

#include"rp.h"
#include"stepper.h"
#include"TCP_API.h"*/

void init_ramp(int trigger); //if trigger==1 ramp is made on trigger else ramp is made with function ramp()
void ramp();
void end_ramp();
void set_acquisition();
void trigg();
void triggnow();
void on_trigger_acquisition(float *buffer_float, uint32_t buffer_length);
void acquisition(float *buffer_float, uint32_t buffer_length);
void init_RP();
void close_RP();
void send_via_tcp(int line, char *buffer_char, float *buffer_float, uint32_t buffer_length, client *client_list);
void init_pulse();
void pulse();

void init_ramp(int trigger) 
{
	rp_GenWaveform(RP_CH_1, RP_WAVEFORM_RAMP_UP);
	rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
	rp_GenBurstCount(RP_CH_1, 1);
	rp_GenAmp(RP_CH_1, 1.0);
	rp_GenFreq(RP_CH_1, 7633.59);

	if (trigger==1)
	{	
		rp_GenTriggerSource(RP_CH_1,RP_TRIG_SRC_CHA_PE); //to trigger on external trigger must put RP_TRIG_SRC_CHA_PE not RP_TRIG_SRC_EXT_PE...
		rp_GenOutEnable(RP_CH_1);
	}
}

void ramp()
{
	rp_GenOutEnable(RP_CH_1);
}

void end_ramp() {rp_GenOutDisable(RP_CH_1);}

void set_acquisition() 
{
	rp_AcqSetDecimation(RP_DEC_8);
	rp_AcqSetAveraging(1);
	rp_AcqSetGain(RP_CH_1,RP_HIGH); 	
}

void trigg() 
{
	rp_AcqStart();
	rp_AcqSetTriggerSrc(RP_TRIG_SRC_EXT_PE);
	rp_AcqSetTriggerDelay(-6144); //if there is noise at the end can use -6550
}

void triggnow() 
{
	rp_AcqStart();
	rp_AcqSetTriggerSrc(RP_TRIG_SRC_NOW);
	rp_AcqSetTriggerDelay(-6144); //if there is noise at the end can use -6550
	rp_acq_trig_state_t state = RP_TRIG_STATE_TRIGGERED;
	while(1){
		rp_AcqGetTriggerState(&state);
		if(state == RP_TRIG_STATE_TRIGGERED){
			break;
		}
	}
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

void acquisition(float *buffer_float, uint32_t buffer_length)
{
	triggnow();
	rp_AcqGetLatestDataV(RP_CH_1, &buffer_length, buffer_float);
}

void init_RP(int trigger)
{
	if(rp_Init() != RP_OK)
	{
	printf("Rp api init failed!\n");
	}
	init_ramp(trigger);
	init_pulse();
	set_acquisition();
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
