#ifndef SerialInterface_h
#define SerialInterface_h

#include <WString.h>
#include "Singleton.h"

namespace Arm {
  class SerialInterface :
    public Singleton<SerialInterface>
  {
    friend class Singleton<SerialInterface>;
    public:
      String command = "";

      void setup ();
      void loop (long delta);
      void read ();
      void executeCommand ();
      void executeCommand (String _command);

  };
}
#endif
