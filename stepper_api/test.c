#include<stdio.h>
#include<stdlib.h>

#include"stepper.h"

int main (int argc, char *argv[])
{
	stepper_motor stepper;
	double time, speed=3.0;
	double angle=14.5742;
	int Nstep;
	mode step_size=full_16;

	init_stepper(&stepper);

	set_mode(&stepper, step_size);

	time=half_step_time(& stepper, &speed);
	printf("speed = %f\n",speed);
	printf("time = %f\n",time);

	Nstep=step_number(&stepper, &angle);
	printf("angle = %f\n",angle);
	printf("number of step = %i\n",Nstep);	
}
