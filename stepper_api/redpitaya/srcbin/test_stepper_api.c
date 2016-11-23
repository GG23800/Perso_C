#include<stdio.h>
#include<stdlib.h>

#include"stepper.h"

int main(int argc, char** argv)
{
	stepper_motor stepper;
	init_stepper(&stepper);

	set_mode(&stepper, full);
	init_position(&stepper, 120);
	disable_stepper(&stepper);

	return 0;
}
