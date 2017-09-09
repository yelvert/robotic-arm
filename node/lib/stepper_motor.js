const NanoTimer = require('nanotimer');
const inspectInstance = require('./inspect_instance');
const rpio = require('rpio');

const name = Symbol('StepperMotor#name');
const stepPin = Symbol('StepperMotor#stepPin');
const dirPin = Symbol('StepperMotor#dirPin');
const stepsPerRotation = Symbol('StepperMotor#stepPerRotation');
const degreesPerStep = Symbol('StepperMotor#degreesPerStep');
const currentRotation = Symbol('StepperMotor#currentRotation');
const desiredRotation = Symbol('StepperMotor#desiredRotation');
const stepInterval = Symbol('StepperMotor#stepInterval');
const wantsStep = Symbol('StepperMotor#wantsStep');
const rotateTimer = Symbol('StepperMotor#rotateTimer');
const stepFlopTimer = Symbol('StepperMotor#stepFlopTimer');
const startRotating = Symbol('StepperMotor#startRotating()');
const stopRotating = Symbol('StepperMotor#stopRotating()');
const setDir = Symbol('StepperMotor#setDir()');
const tryStep = Symbol('StepperMotor#tryStep()');
const step = Symbol('StepperMotor#step()');
const stepFlip = Symbol('StepperMotor#stepFlip()');
const stepFlop = Symbol('StepperMotor#stepFlop()');

class StepperMotor {

  static get FORWARD () { return rpio.LOW }

  static get BACKWARD () { return rpio.HIGH }

  static get MIN_STEP_INTERVAL () { return 500 }

  static get STEP_FLOP_INTERVAL () { return 200 }

  constructor (_name, _stepPin, _dirPin, _stepsPerRotation) {
    if (!(this instanceof StepperMotor)) return new StepperMotor(...arguments);
    this[name] = _name;
    this[stepPin] = _stepPin;
    this[dirPin] = _dirPin;
    this[stepsPerRotation] = _stepsPerRotation;
    this[degreesPerStep] = 360.0/_stepsPerRotation;
    this[currentRotation] = 0.0;
    this[desiredRotation] = 0.0;
    this.speed = 360.0
    this.setup();
  }

  get name () { return this[name] }

  get stepPin () { return this[stepPin] }

  get dirPin () { return this[dirPin] }

  get stepsPerRotation () { return this[stepsPerRotation] }

  get degreesPerStep () { return this[degreesPerStep] }

  get currentRotation () { return this[currentRotation] }

  get desiredRotation () { return this[desiredRotation] }
  set desiredRotation (angle) {
    this[desiredRotation] = angle;
    this[startRotating]();
  }

  get direction () { return this.constructor[this.desiredRotation > this.currentRotation ? 'FORWARD' : 'BACKWARD'] }

  get stepInterval () { return this[stepInterval] }
  set stepInterval (microseconds) { this[stepInterval] = Math.max(microseconds, this.constructor.MIN_STEP_INTERVAL) }

  get speed () { return this.degreesPerStep/(this.stepInterval/1e6) }
  set speed (degreesPerSecond) { this.stepInterval = 1e6/(degreesPerSecond/this.degreesPerStep) }

  get [wantsStep] () {
    const diff = Math.abs(Math.abs(this.currentRotation) - Math.abs(this.desiredRotation));
    return diff > this.degreesPerStep/2;
  }

  log () { console.log(`StepperMotor "${this.name}":`, this, ...arguments) }

  setup () {
    this.log('Setup');
    this[rotateTimer] = new NanoTimer();
    this[stepFlopTimer] = new NanoTimer();
    rpio.open(this.stepPin, rpio.OUTPUT, rpio.LOW);
    rpio.open(this.dirPin, rpio.OUTPUT, rpio.LOW);
  }

  [startRotating] () {
    this[rotateTimer].setInterval( _ => this[tryStep](), '', `${this.stepInterval}u`)
    this.log('start rotating', this[rotateTimer]);
  }

  [stopRotating] () {
    this[rotateTimer].clearInterval();
    this.log('stop rotating', this[rotateTimer]);
  }

  [setDir] () {
    rpio.write(this.dirPin, this.direction);
  }

  [tryStep] () {
    this[this[wantsStep] ? step : stopRotating]();
  }

  [step] () {
    this[setDir]();
    this[stepFlip]();
  }

  [stepFlip] () {
    this.log('flip');
    rpio.write(this.stepPin, rpio.HIGH);
    this[stepFlopTimer].setTimeout( _ => this[stepFlop](), '', `${this.constructor.STEP_FLOP_TIME}u`);
  }

  [stepFlop] () {
    this.log('flop');
    rpio.write(this.stepPin, rpio.LOW);
    this[currentRotation] += this.degreesPerStep*(this.direction === this.constructor.FORWARD ? 1 : -1);
  }

  inspect () { return `StepperMotor ${JSON.stringify(inspectInstance(this))}` }

}

module.exports = StepperMotor;
