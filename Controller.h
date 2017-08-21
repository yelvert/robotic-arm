#ifndef Controller_h
#define Controller_h

#include <WString.h>
#include "Vector.h"
#include "Singleton.h"
#include "CommandInterface.h"
#include "StepperMotor.h"

namespace Arm {
  class Controller :
    public Singleton<Controller>,
    public CommandInterface
  {
    friend class Singleton<Controller>;
    public:
      long delta;
      Vector<Arm::StepperMotor*> articulations;

      Controller ();
      void setup ();
      void loop (long _delta);
      void read ();
      void executeCommand ();
      void executeCommand (String _command);

  };
}
#endif
