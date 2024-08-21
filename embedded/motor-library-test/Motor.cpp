#include "Motor.h"

// Constructor
Motor::Motor(int in1Pin, int in2Pin, int encoderAPin, int encoderBPin, int resolution, bool invertPolarity)
  : _in1Pin(in1Pin), _in2Pin(in2Pin), _encoderAPin(encoderAPin), _encoderBPin(encoderBPin), _resolution(resolution), _invertPolarity(invertPolarity), _encoderCount(0) {
  
  // Set motor control pins as outputs
  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);

  // Set encoder pins as inputs
  pinMode(_encoderAPin, INPUT);
  pinMode(_encoderBPin, INPUT);

  // Attach interrupts to encoder pins
  attachInterrupt(digitalPinToInterrupt(_encoderAPin), [this]() { this->updateEncoder(); }, RISING);
}

// Get functions
long Motor::getEncoderCount() {
  return _encoderCount;
}

float Motor::getPositionDegrees() {
  return (360.0 * _encoderCount) / _resolution;
}

// Move functions
void Motor::moveDegrees(float degrees) {
  long targetTicks = (degrees * _resolution) / 360.0;
  _moveMotor(degrees > 0 ? 1 : -1, abs(targetTicks));
}

void Motor::moveTicks(long ticks) {
  _moveMotor(ticks > 0 ? 1 : -1, abs(ticks));
}

// Internal move function
void Motor::_moveMotor(int direction, long ticks) {
  if (_invertPolarity) {
    direction = -direction;
  }

  // Set motor direction
  if (direction == 1) {  // Forward
    digitalWrite(_in1Pin, HIGH);
    digitalWrite(_in2Pin, LOW);
  } else {  // Backward
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, HIGH);
  }

  // Reset encoder count
  long startCount = _encoderCount;

  // Move motor until the target ticks are reached
  while (abs(_encoderCount - startCount) < ticks) {
    // Busy-wait until target is reached
  }

  // Stop the motor
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
}

// Update function for encoder
void Motor::updateEncoder() {
  // Read the state of the encoder B pin to determine direction
  if (digitalRead(_encoderBPin) == LOW) {
    _encoderCount++;
  } else {
    _encoderCount--;
  }
}
