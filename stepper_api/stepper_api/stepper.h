#ifndef STEPPER_H
#define STEPPER_H

#define EN 10
#define MS1 9
#define MS2 8
#define MS3 7
#define STEP 6
#define DIR 5

typedef struct stepper_motor stepper_motor; //so we can call stepper_motor and not struct stepper_motor
//typedef enum mode mode;
//typedef enum sens sens;

enum mode
{
  full,full_2,full_4,full_8,full_16
};

enum sens
{
  sens1,sens2
};

void init_stepper(stepper_motor* stepper); //initialyse the structure stepper_motor
void enable_stepper(stepper_motor* stepper);
void desable_stepper(stepper_motor* stepper);
void set_mode(stepper_motor* stepper, mode step_size); //set mode of the stepper : full, 1/2, 1/4, 1/8, 1/16 step
int half_step_time(stepper_motor* stepper, double* speed); //give time of a half step depending on the mode and speed in tour per second, note that this time is in microseconds and must be greater than 1 us. It change the speed to its real value
int step_number(stepper_motor* stepper, double* angle); //give the number of step to do in order to move to a given angle, if angle is not a multiple of the angle of a step, angle is change to its correct value
void move(stepper_motor* stepper, double* angle, double* speed, sens dir); //move the stepper of a given angle with a given speed on sens dir. It returns the real mooved angle and speed
void init_position(stepper_motor* stepper, double angle); //initialize the stepper position by going to the mecanic stop (sens2) and then move to the given angle (sens1)

struct stepper_motor
{
	int pin_en;
	int pin_ms1;
	int pin_ms2;
	int pin_ms3;
	int pin_step;
	int pin_dir;
	mode step_size;
	
};

void init_stepper(stepper_motor* stepper)
{
	stepper->pin_en=EN;
	stepper->pin_ms1=MS1;
	stepper->pin_ms2=MS2;
	stepper->pin_ms3=MS3;
	stepper->pin_step=STEP;
	stepper->pin_dir=DIR;
	stepper->step_size=full;

	digitalWrite(stepper->pin_en,HIGH);
	digitalWrite(stepper->pin_ms1,LOW);
	digitalWrite(stepper->pin_ms2,LOW);
	digitalWrite(stepper->pin_ms3,LOW);
	digitalWrite(stepper->pin_step,LOW);
	digitalWrite(stepper->pin_dir,LOW);
}

void enable_stepper(stepper_motor* stepper)
{
	digitalWrite(stepper->pin_en,LOW);
}

void desable_stepper(stepper_motor* stepper)
{
	digitalWrite(stepper->pin_en,HIGH);
}

void set_mode(stepper_motor* stepper, mode step_size)
{
	if (step_size!=stepper->step_size)
	{
		stepper->step_size=step_size;

		if (step_size==full)
		{
			digitalWrite(stepper->pin_ms1,LOW);
			digitalWrite(stepper->pin_ms2,LOW);
			digitalWrite(stepper->pin_ms2,LOW);
		}
		if (step_size==full_2)
		{
			digitalWrite(stepper->pin_ms1,HIGH);
			digitalWrite(stepper->pin_ms2,LOW);
			digitalWrite(stepper->pin_ms2,LOW);
		}
		if (step_size==full_4)
		{
			digitalWrite(stepper->pin_ms1,LOW);
			digitalWrite(stepper->pin_ms2,HIGH);
			digitalWrite(stepper->pin_ms2,LOW);
		}
		if (step_size==full_8)
		{
			digitalWrite(stepper->pin_ms1,HIGH);
			digitalWrite(stepper->pin_ms2,HIGH);
			digitalWrite(stepper->pin_ms2,LOW);
		}
		if (step_size==full_16)
		{
			digitalWrite(stepper->pin_ms1,HIGH);
			digitalWrite(stepper->pin_ms2,HIGH);
			digitalWrite(stepper->pin_ms2,HIGH);
		}
	}
}

int half_step_time(stepper_motor* stepper, double* speed)
{
	int Nstep;
	double time;

	switch (stepper->step_size)
	{
		case full :
			Nstep=400;
		case full_2 :
			Nstep=400*2;
		case full_4 :
			Nstep=400*4;
		case full_8 :
			Nstep=400*8;
		case full_16 :
			Nstep=400*16;
	}

	time=(double)(1000000/Nstep)/(*speed)/2.0; //time in us 
	if (time<1.0){time=1.0;}
	(*speed)=(double)(500000/Nstep)/time;
	return (int)time;
}

int step_number(stepper_motor* stepper, double* angle)
{
	double minimum_angle;
	int  Nstep;

	switch (stepper->step_size)
	{
		case full :
			minimum_angle=360.0/400.0;
		case full_2 :
			minimum_angle=360.0/(400.0*2.0);
		case full_4 :
			minimum_angle=360.0/(400.0*4.0);
		case full_8 :
			minimum_angle=360.0/(400.0*8.0);
		case full_16 :
			minimum_angle=360.0/(400.0*16.0);
	}

	if ((*angle)<minimum_angle){(*angle)=minimum_angle;}	
	Nstep=(int)((*angle)/minimum_angle);
	(*angle)=(double)(Nstep)*minimum_angle;

	return Nstep;
}

void move(stepper_motor* stepper, double* angle, double* speed, sens dir)
{
	int Nstep, half_time;
	int i;

	digitalWrite(stepper->pin_dir,dir);
	half_time=half_step_time(stepper, speed);
	Nstep=step_number(stepper, angle);

	for (i=0 ; i<Nstep ; i++)
	{
		digitalWrite(stepper->pin_step,HIGH);
		delayMicroseconds(half_time);
		digitalWrite(stepper->pin_step,LOW);
		delayMicroseconds(half_time);
	}
}

void init_position(stepper_motor* stepper, double angle)
{
	double tour=360.0, speed=3.0;

	enable_stepper(stepper);
	delay(100);
	move(stepper, &tour, &speed, sens2);
	delay(50);
	move(stepper, &angle, &speed, sens1);

}

#endif
