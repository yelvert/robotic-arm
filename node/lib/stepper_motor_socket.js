const io = Symbol('StepperMotorSocket.io');
const stepperMotors = Symbol('StepperMotorSocket.stepperMotors');
const stepperMotor = Symbol('StepperMotorSocket#stepperMotor');
const socket = Symbol('StepperMotorSocket#socket');

class StepperMotorSocket {

  static get io () { return this[io] }

  static get stepperMotors () { return this[stepperMotors] }

  static initialize (_io, ..._stepperMotors) {
    if (this.io) throw 'StepperMotorSocket has already been connected!'
    this[io] = _io;
    this[stepperMotors] = _stepperMotors
    this.io.on('connection', _socket => StepperMotorSocket.connect(_socket) )
  }

  static connect (_socket) {
    return this.stepperMotors.map( _stepperMotor => new this(_socket, _stepperMotor) );
  }

  constructor (_socket, _stepperMotor) {
    this[socket] = _socket;
    this[stepperMotor] = _stepperMotor;
    this.socket.emit('stepper', this.stepperMotor.inspect());
    this.socket.on('message', msg => this.handleMessage(msg) );
  }

  get socket () { return this[socket] }

  get stepperMotor () { return this [stepperMotor] }

  handleMessage (message) {
    console.log(message);
  }

}

module.exports = StepperMotorSocket;
