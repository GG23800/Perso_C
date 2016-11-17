#include"stepper.h"

stepper_motor stepper;
  
void setup() {
  // put your setup code here, to run once:
  pinMode(stepper.pin_en,OUTPUT);
  pinMode(stepper.pin_ms1,OUTPUT);
  pinMode(stepper.pin_ms2,OUTPUT);
  pinMode(stepper.pin_ms3,OUTPUT);
  pinMode(stepper.pin_step,OUTPUT);
  pinMode(stepper.pin_dir,OUTPUT);

  init_stepper(&stepper);
}

void loop() {
  // put your main code here, to run repeatedly:
  init_position(&stepper, 120);
}
