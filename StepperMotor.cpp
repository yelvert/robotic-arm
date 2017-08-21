#include <Arduino.h>
#include <WString.h>
#include "Vector.h"
#include "StringUtils.h"
#include "CommandInterface.h"
#include "StepperMotor.h"

Arm::StepperMotor::StepperMotor
  (String name, int stepPin, int dirPin, int stepsPerRotation) :
  Arm::CommandInterface(),
  _name(name),
  _stepPin(stepPin),
  _dirPin(dirPin),
  _stepsPerRotation(stepsPerRotation)
{
    delta = micros();
    _stepInterval = 1000;
    stepTimeout = delta + stepInterval();
}

String Arm::StepperMotor::name () const { return _name; }

int Arm::StepperMotor::stepPin () const { return _stepPin; }

int Arm::StepperMotor::dirPin () const { return _dirPin; }

long Arm::StepperMotor::stepInterval () { return max(_stepInterval, MINIMUM_STEP_INTERVAL); }

long Arm::StepperMotor::stepInterval (long newStepInterval) {
  _stepInterval = max(newStepInterval, MINIMUM_STEP_INTERVAL);
  Serial.println(name()+" stepInterval: "+stepInterval());
  return stepInterval();
}

int Arm::StepperMotor::stepsPerRotation () const { return _stepsPerRotation; }

double Arm::StepperMotor::degreesPerStep () const { return 360.0/stepsPerRotation(); }

double Arm::StepperMotor::currentRotation () { return _currentRotation; }

double Arm::StepperMotor::desiredRotation () { return _desiredRotation; }

void Arm::StepperMotor::setup () {
  pinMode(stepPin(), OUTPUT);
  pinMode(dirPin(), OUTPUT);
  Serial.print(name());
  Serial.println(" setup");
}

void Arm::StepperMotor::loop (long _delta) {
  delta = _delta;
  step();
}

void Arm::StepperMotor::executeCommand (String command) {
  Vector<String> parts;
  StringUtils::split(command, parts);
  if (parts[0] == name()) {
    for (int i = 1 ; i < parts.size() ; i++) {
      String part = parts[i];
      switch (part[0]) {
        case 'M':
          if (part.length() > 1) {
            rotateTo(part.substring(1).toFloat());
          } else {
            Serial.println(name()+" M"+currentRotation()+Arm::CommandInterface::COMMAND_TERMINATOR);
          }
          break;
        case 'S':
          if (part.length() > 1) {
            stepInterval(part.substring(1).toInt());
          } else {
            Serial.println(name()+" S"+stepInterval()+Arm::CommandInterface::COMMAND_TERMINATOR);
          }
          break;
        case 'R':
          rotateTo(0.0);
          break;
      }
    }
  }
}

bool Arm::StepperMotor::step () {
  if (canStep()) {
    if (desiredRotation() > currentRotation()) {
      direction = DIRECTION::FORWARD;
      digitalWrite(dirPin(), HIGH);
    } else {
      direction = DIRECTION::BACKWARD;
      digitalWrite(dirPin(), LOW);
    }
    if (wantsStep()) {
      int thisStep = !lastStep;
      digitalWrite(stepPin(), thisStep);
      stepTimeout = delta + stepInterval();
      if (thisStep == LOW) {
        _currentRotation += degreesPerStep() * (int)direction;
      }
      lastStep = !lastStep;
    } else if (lastStep == HIGH) {
      digitalWrite(stepPin(), LOW);
      lastStep = LOW;
    }
  }
}

bool Arm::StepperMotor::canStep () {
  return delta - stepTimeout >= 0;
}

bool Arm::StepperMotor::wantsStep () {
  return fabs(currentRotation() - desiredRotation()) > degreesPerStep()/2;
}

void Arm::StepperMotor::rotateTo (double degrees) {
  _desiredRotation = degrees;
  Serial.println(name()+" rotateTo: "+_desiredRotation);
}
