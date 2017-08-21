#include <Arduino.h>
#include <WString.h>
#include "Vector.h"
#include "StringUtils.h"
#include "Singleton.h"
#include "StepperMotor.h"
#include "Controller.h"

Arm::Controller::Controller () :
  Singleton<Arm::Controller>(),
  Arm::CommandInterface()
{
  delta = micros();
  articulations.push_back( new Arm::StepperMotor ("BaseYaw", 2, 3, 200) );
  articulations.push_back( new Arm::StepperMotor ("BasePitch", 4, 5, 200) );
  articulations.push_back( new Arm::StepperMotor ("Elbow", 6, 7, 200) );
}

void Arm::Controller::setup () {
  const int motorEnabledPin = 8;
  pinMode(motorEnabledPin, OUTPUT);
  digitalWrite(motorEnabledPin, HIGH);
  for (int i = 0 ; i < articulations.size() ; i++) {
    articulations[i]->setup();
  }
  executeCommand("Ctrl A");
  executeCommand("Ctrl ?");
  Serial.println("Controller setup");
}

void Arm::Controller::loop (long _delta) {
  delta = _delta;
  for (int i = 0 ; i < articulations.size() ; i++) {
    articulations[i]->loop(delta);
  }
}

void Arm::Controller::executeCommand (String command) {
  Vector<String> parts;
  StringUtils::split(command, parts);
  if (parts[0] == "Ctrl") {
    for (int i = 1 ; i < parts.size() ; i++) {
      String part = parts[i];
      switch (part[0]) {
        case '?':
          Serial.println("Ok");
          break;
        case 'A':
          for (int i = 0 ; i < articulations.size() ; i++) {
            Serial.println("Articulation: "+articulations[i]->name());
          }
          break;
      }
    }
  }
}
