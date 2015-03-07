#include "Drive.h"
int motol[2]={12, 13};
int motor[2] = {10,11};
int EN = 2;
Drive drive(motol, motor, EN);
String output_string = "";
// line sensors
int middle = A0;
int right_middle = A1;

int left_read = 0;
int right_read = 0;

void setup(){
  Serial.begin(9600);
  
}

void align()
{
    // ensure the alignment with the front line is correct
    read_lines(middle, right_middle); // get readings of pair

    if(left_read) // as long as this reads black, we're good
    {
      return;
    }
    else // getting off line
    {
      if(right_read) // right middle is black, so turn right to align
        drive.turn_right();
      else
        drive.turn_left(); // both are on right side of line, turn left
    }
}

void read_lines(int pin1, int pin2){
  int left_read = analogRead(pin1);
  int right_read = analogRead(pin2);
  if (left_read < 700)
  {
    left_read = 0; //white
  }
  else
  {
  left_read = 1; //black
  }
  if (right_read < 700)
  {
   right_read = 0;
  }
  else
  {
     right_read = 1;
  }
}

void loop(){
  align();
}
