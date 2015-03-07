#include <Debug.h>

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
// motor
int reverse =0;
int motor_left[] = {12,  13};
int motor_right[] = {10, 11};
int ENABLE = 2;

char by = ' ';

void setup()
{
  Serial.begin(9600);
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
  if(Serial.available()>0)
  {
      by = Serial.read();
      if(String(by) == "R")
      {
         turn_right(); 
      }
      else if(String(by)=="L")
      {
       turn_left(); 
      }
      else if(String(by) =="F")
      {
       drive_forward(); 
      }
      else if(String(by) == "
  }
}

