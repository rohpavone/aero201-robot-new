#include <Debug.h>
#include "Servo.h"
// set the pins for signal
int left_bumper = 5;
int right_bumper = 4;
int left_read = 0;
int right_read = 0;
String out = "";

// motor
int reverse =0;
int motor_left[] = {12,  13};
int motor_right[] = {10, 11};
int ENABLE = 2;

// output to servo
Servo claw;
int servo = 3;

// debug 
Debug deb;

void setup()
{
  Serial.begin(9600);
 pinMode(left_bumper, INPUT);
  pinMode(right_bumper, INPUT);
  claw.attach(servo);
  deb.write_out("Ready!");
  
   int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, HIGH);
}

void loop()
{
  left_read = digitalRead(left_bumper);
  right_read = digitalRead(right_bumper);
  out = "LEFT: " + String(left_read) + ", RIGHT: " + String(right_read) + " - ";
  
  motor_stop();
  if(left_read && right_read)
  {
      claw.write(0);
      out+="CLAW CLOSE";
  }
  else if(left_read)
  {
     left_only(); 
  }
  else if(right_read)
  {
    right_only();
  }
  else
  {
     claw.write(90); 
     out+="CLAW OPEN";
  }
  deb.write_out(out);
}


// xoring with reverse does following: if reverse is 0, then remains same
// if reverse is 1, then the signal is switched (reversing directions)
void motor_stop(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], LOW);
out += "STATE STOP - ";
}
void drive_forward(){

digitalWrite(motor_left[0], HIGH^reverse);
digitalWrite(motor_left[1], LOW^reverse);

digitalWrite(motor_right[0], HIGH^reverse);
digitalWrite(motor_right[1], LOW^reverse);
out += "STATE FORWARD - ";
}

void drive_backward(){
digitalWrite(motor_left[0], LOW^reverse);
digitalWrite(motor_left[1], HIGH^reverse);

digitalWrite(motor_right[0], LOW^reverse);
digitalWrite(motor_right[1], HIGH^reverse);
out += "STATE REVERSE - ";
}

void turn_left(){
digitalWrite(motor_left[0], LOW^reverse);
digitalWrite(motor_left[1], HIGH^reverse);

digitalWrite(motor_right[0], HIGH^reverse);
digitalWrite(motor_right[1], LOW^reverse);
out += "STATE LEFT - ";
}

void turn_right(){
digitalWrite(motor_left[0], HIGH^reverse);
digitalWrite(motor_left[1], LOW^reverse);

digitalWrite(motor_right[0], LOW^reverse);
digitalWrite(motor_right[1], HIGH^reverse);
out += "STATE RIGHT - ";
}

void left_only(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
  out += "STATE LEFT ONLY - ";
}

void right_only(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  out += "STATE RIGHT ONLY -  ";
}
