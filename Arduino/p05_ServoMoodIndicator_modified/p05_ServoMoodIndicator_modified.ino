/*
  Arduino Starter Kit example
 Project 5  - Servo Mood Indicator
 
 This sketch is written to accompany Project 5 in the
 Arduino Starter Kit
 
 Parts required:
 servo motor 
 10 kilohm potentiometer 
 2 100 uF electrolytic capacitors
 
 Created 13 September 2012
 by Scott Fitzgerald
 
 http://arduino.cc/starterKit
 
 This example code is part of the public domain 
 */

// include the servo library
#include <Servo.h>
int counter = 0;
int total = 0;
int reader = A0;

Servo myServo;  // create a servo object 

int angle;   // variable to hold the angle for the servo motor 

void setup() {
  myServo.attach(6); // attaches the servo on pin 9 to the servo object 
  pinMode(reader, INPUT);
  Serial.begin(9600); // open a serial connection to your computer
}

void loop() {
  counter = analogRead(reader);
  angle = 90;
  // scale the numbers from the pot 
  if(counter> 100 && counter < 700)
  {
      total += 1;

  }
  if(total > 500){
        // set the servo position  
      myServo.write(angle);
      
  }
  else
  {
     myServo.write(180); // open 
  }
 


  // wait for the servo to get there 
}


