// Drive.h - Driving module for Arduino with H-bridge control

#ifndef Drive_h
#define Drive_h

#include "Arduino.h"

class Drive
{
  public:
    Drive(int left_motor[], int right_motor[], int enable);
    void motor_stop();
    void drive_forward();
    void drive_backward();
    void turn_left();
    void turn_right();
    void left_only();
    void right_only();
    int reverse; // 0 means drive forward, 1 means backwards
    String state;
    String prev_state;
    int motor_left[];
    int motor_right[];
    int ENABLE;
};

#endif
