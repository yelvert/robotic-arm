#include "SerialInterface.h"

void Arm::SerialInterface::setup () {
  Serial.begin(19200);
  while (!Serial) {}
}

void Arm::SerialInterface::loop (long delta) {
  read();
}

void Arm::SerialInterface::read () {
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();
    if (incomingByte == COMMAND_TERMINATOR) {
      executeCommand();
    } else {
      command += incomingByte;
    }
  }
}

void Arm::SerialInterface::executeCommand (String _command) {
  Serial.println("Executing: "+_command);
  CommandInterface::executeCommandOnAll(_command);
}

void Arm::SerialInterface::executeCommand () {
  executeCommand(command);
  command = "";
}
