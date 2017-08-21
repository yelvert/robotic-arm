#ifndef StepperMotor_h
#define StepperMotor_h

#include <WString.h>
#include "Vector.h"
#include "CommandInterface.h"

namespace Arm {
  class StepperMotor :
    public CommandInterface
  {
    public:
      enum class DIRECTION { FORWARD = 1, BACKWARD = -1 };

      static const long MINIMUM_STEP_INTERVAL = 350;

      StepperMotor (String name, int stepPin, int dirPin, int stepsPerRotation);

      StepperMotor::DIRECTION direction = StepperMotor::DIRECTION::FORWARD;

      void executeCommand (String command);

      void setup ();

      void loop (long _delta);

      String name () const;

      int stepPin () const;

      int dirPin () const;

      long stepInterval ();

      long stepInterval (long newStepInterval);

      int stepsPerRotation () const;

      double degreesPerStep () const;

      bool step ();

      bool canStep ();

      bool wantsStep ();

      double currentRotation ();

      double desiredRotation ();

      void rotateTo (double degrees);

    private:
      String _name;

      int _stepPin;

      int _dirPin;

      int _stepsPerRotation;

      long _stepInterval;

      long delta;

      int lastStep;

      long stepTimeout;

      double _currentRotation;

      double _desiredRotation;

  };
}

#endif
