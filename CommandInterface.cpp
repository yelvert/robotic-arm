#include "lib/vector.h"
#include "CommandInterface.h"

Arm::CommandInterface::CommandInterface () {
  commandReceivers().push_back(this);
}

static Vector<Arm::CommandInterface*>& Arm::CommandInterface::commandReceivers () {
  static Vector<Arm::CommandInterface*> _commandReceivers;
  return _commandReceivers;
}
static void Arm::CommandInterface::executeCommandOnAll (String command) {
  for ( int i = 0 ; i < commandReceivers().size() ; i++) {
    commandReceivers()[i]->executeCommand(command);
  }
}
