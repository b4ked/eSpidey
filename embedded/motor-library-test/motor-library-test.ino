#include "Motor.h"

// Define motor control pins
#define MOTOR1_IN1 2
#define MOTOR1_IN2 3
#define MOTOR1_ENCODER_A 12
#define MOTOR1_ENCODER_B 1

// Instantiate a motor object
Motor motor1(MOTOR1_IN1, MOTOR1_IN2, MOTOR1_ENCODER_A, MOTOR1_ENCODER_B, 2086, false);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  Serial.println("Starting motor control...");
}

void loop() {
  Serial.println("Moving motor forward 360 degrees...");
  motor1.moveDegrees(360.0);
  delay(5000);

  Serial.println("Moving motor backward 360 degrees...");
  motor1.moveDegrees(-360.0);
  delay(5000);
}
