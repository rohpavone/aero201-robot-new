#include <Servo.h>
Servo myServo;

int const potPin = A5;
int potVal;
int angle;

void setup(){
 myServo.attach(3);
Serial.begin(9600); 
}

void loop(){
   potVal = analogRead(potPin);
  angle = map(potVal, 0, 1023, 0, 179); // map potVal from 0-1023 to 0-179, the angles for the servo
  Serial.print("potVal: ");
  Serial.print(potVal);
  Serial.print(", Angle Val: ");
  myServo.write(angle); //set it to this angle
}
