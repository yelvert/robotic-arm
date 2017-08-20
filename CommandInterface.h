#ifndef CommandInterface_h
#define CommandInterface_h

#include "lib/vector.h"
#include "WString.h"

namespace Arm {
  class CommandInterface {
    public:
      CommandInterface ();
      static void executeCommandOnAll (String command);
      static Vector<Arm::CommandInterface*>& commandReceivers ();
      virtual void executeCommand (String command) = 0;
  };
}

#endif
