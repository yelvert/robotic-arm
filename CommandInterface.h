#ifndef CommandInterface_h
#define CommandInterface_h

#include <WString.h>
#include "Vector.h"

namespace Arm {
  class CommandInterface {
    public:
      static const char COMMAND_TERMINATOR = ';';
      CommandInterface ();
      static void executeCommandOnAll (String command);
      static Vector<Arm::CommandInterface*>& commandReceivers ();
      virtual void executeCommand (String command) = 0;
  };
}

#endif
