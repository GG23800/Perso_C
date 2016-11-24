#include"stepper.h"

stepper_motor stepper;
  
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  init_stepper(&stepper);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(stepper.pin_step);
  delay(1000);
  set_mode(&stepper, full);
  init_position(&stepper, 120);
  disable_stepper(&stepper);
}
