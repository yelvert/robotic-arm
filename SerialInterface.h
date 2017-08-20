#ifndef SerialInterface_h
#define SerialInterface_h

#include "Arduino.h"
#include "WString.h"
#include "CommandInterface.h"

namespace Arm {
  class SerialInterface {
    public:
      static const char COMMAND_TERMINATOR = ';';

      String command = "";

      void setup ();
      void loop (long delta);
      void read ();
      void executeCommand ();
      void executeCommand (String _command);

    public:
      static SerialInterface& getInstance() {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        static SerialInterface instance;
        return instance;
      }
    private:
      SerialInterface () {} // Constructor? (the {} brackets) are needed here.
      SerialInterface (SerialInterface const&); // Don't Implement
      void operator= (SerialInterface const&); // Don't implement
  };
}
#endif
