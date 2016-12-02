#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"rp.h"
#include"stepper.h"

int main(int argc, char** argv)
{
	printf("declare stepper\n");
	stepper_motor stepper;
	rp_Init();
	printf("init stepper\n");
	init_stepper(&stepper);
	printf("init done\n");

	while(1)
	{
		printf("set mode\n");
		set_mode(&stepper, full);
		printf("init position\n");
		init_position(&stepper, 120);
		disable_stepper(&stepper);
		usleep(1000000);
	}

	return 0;
}
