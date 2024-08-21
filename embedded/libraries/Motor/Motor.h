#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  public:
    // Constructor
    Motor(int in1Pin, int in2Pin, int encoderAPin, int encoderBPin, int resolution, bool invertPolarity = false);

    // Get functions
    long getEncoderCount();
    float getPositionDegrees();

    // Move functions
    void moveDegrees(float degrees);
    void moveTicks(long ticks);

    // Update function for encoder
    void updateEncoder();

  private:
    int _in1Pin;
    int _in2Pin;
    int _encoderAPin;
    int _encoderBPin;
    int _resolution;
    bool _invertPolarity;
    volatile long _encoderCount;

    // Internal move function
    void _moveMotor(int direction, long ticks);
};

#endif
