#include"stepper.h"
#define NOP __asm__ __volatile__ ("nop\n\t");

stepper_motor stepper;

void pulse()
{
	PORTB=B00010000;
	NOP;
	PORTB=B00001000;
}
  
void setup() {
  // put your setup code here, to run once:
	DDRB=B00011000;
	init_stepper(&stepper);
}

void loop() {
  // put your main code here, to run repeatedly:
	double angle=0.0, speed=2.0, sector=60.0;
	int Nline=64, i=0;
	angle=sector/(double)Nline;
	set_mode(&stepper, full_16);
	init_position(&stepper, 130);

	while(1)
	{
		for(i=0 ; i<Nline ; i++)
		{
			move(&stepper, &angle, &speed, sens1);
			pulse();
			delayMicroseconds(3000);
		}
		for(i=Nline ; i>0 ; i++)
		{
			move(&stepper, &angle, &speed, sens2);
			pulse();
			delayMicroseconds(3000);
		}
	}	
}
