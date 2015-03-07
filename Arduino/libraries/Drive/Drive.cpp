#include "Arduino.h"
#include "Drive.h"

Drive::Drive(int left_motor[], int right_motor[], int enable){
  motor_left = left_motor;
  motor_right = right_motor;
  ENABLE = enable;
  state = "STOP";
  prev_state = "";


  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, HIGH);
  reverse = 0;

}

void Drive::motor_stop(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}

void Drive::drive_forward(){
  digitalWrite(motor_left[0], HIGH^reverse);
  digitalWrite(motor_left[1], LOW^reverse);

  digitalWrite(motor_right[0], HIGH^reverse);
  digitalWrite(motor_right[1], LOW^reverse);
}

void Drive::drive_backward(){
  digitalWrite(motor_left[0], LOW^reverse);
  digitalWrite(motor_left[1], HIGH^reverse);

  digitalWrite(motor_right[0], LOW^reverse);
  digitalWrite(motor_right[1], HIGH^reverse);
}

void Drive::turn_left(){
  digitalWrite(motor_left[0], LOW^reverse);
  digitalWrite(motor_left[1], HIGH^reverse);

  digitalWrite(motor_right[0], HIGH^reverse);
  digitalWrite(motor_right[1], LOW^reverse);
}

void Drive::turn_right(){
  digitalWrite(motor_left[0], HIGH^reverse);
  digitalWrite(motor_left[1], LOW^reverse);

  digitalWrite(motor_right[0], LOW^reverse);
  digitalWrite(motor_right[1], HIGH^reverse);
}

void Drive::left_only(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

void Drive::right_only(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}
