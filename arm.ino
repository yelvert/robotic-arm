#include "SerialInterface.h"
#include "Controller.h"
#include "StepperMotor.h"

Arm::StepperMotor baseRotation("BaseRotation", 2, 3, 200);
Arm::StepperMotor basePitch("BasePitch", 4, 5, 200);
Arm::StepperMotor elbow("Elbow", 6, 7, 200);

void setup () {
  Arm::Controller::Get().addArticulation(&baseRotation);
  Arm::Controller::Get().addArticulation(&basePitch);
  Arm::Controller::Get().addArticulation(&elbow);

  Arm::SerialInterface::Get().setup();
  Arm::Controller::Get().setup();
}

void loop () {
  unsigned long delta = micros();
  Arm::SerialInterface::Get().loop(delta);
  Arm::Controller::Get().loop(delta);
}