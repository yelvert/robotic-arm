#include "SerialInterface.h"
#include "Controller.h"
#include "StepperMotor.h"

void setup () {
  Arm::SerialInterface::Get().setup();
  Arm::Controller::Get().setup();
}

void loop () {
  unsigned long delta = micros();
  Arm::SerialInterface::Get().loop(delta);
  Arm::Controller::Get().loop(delta);
}