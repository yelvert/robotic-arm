#include "SerialInterface.h"
#include "StepperMotor.h"

const Arm::SerialInterface& serialInterface = Arm::SerialInterface::getInstance();
const Arm::StepperMotor art1("art1", 2, 3, 200);
const Arm::StepperMotor art2("art2", 4, 5, 200);
const Arm::StepperMotor art3("art3", 6, 7, 200);

const int motorEnabledPin = 8;

void setup () {
  serialInterface.setup();
  pinMode(motorEnabledPin, OUTPUT);
  digitalWrite(motorEnabledPin, HIGH);
  art1.setup();
  art2.setup();
  art3.setup();
}

void loop () {
  unsigned long delta = micros();
  serialInterface.loop(delta);
  art1.loop(delta);
  art2.loop(delta);
  art3.loop(delta);
}