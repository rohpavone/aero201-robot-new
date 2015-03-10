#include <Servo.h>

Servo myServo;
int servoPin = 7;
int sensorPins[] = {A0, A1,A2, A3,A4,A5,A6};

// board values
int WHITE = 1;
int BLACK = -1;
int BLANK = 0;

// board holding all the game pieces
int board[42];

// these are comparison values used to determine if black, blank, or white
int black_value = 1000;
int blank_value = 900;
int white_value = 20; 

// number of samples before it is examined
int sample_number = 20;


// seven blank values to read the analog pins
int sensorValues[] = {0,0,0,0,0,0,0}; 

// height of different rows
// theta = arcsin(h/l)
int heights[] = {0, 11, 24, 37, 53, 90}; 


void setup(){
   for(int i = 0; i < 7; i++)
  {
      pinMode(sensorPins[i], INPUT);
  }
  for(int i = 0; i < 42;i++)
  {
     board[i] = BLANK; 
  }
  
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop(){
  // reset the values
  for(int i = 0; i < 7; i++)
  {
     sensorValues[i] = 0; 
  }
  
  // check all the rows
  for(int i = 0; i < 6; i ++)
  {
      myServo.write(heights[i]);
      // read the rows now
      for(int k = 0; k < sample_number; k++)
      {
        for(int j = 0; j < 7; j++)
        {
            sensorValues[j] += analogRead(sensorPins[j]);
        }
      }
      for(int j = 0; j < 7; j++){
        sensorValues[j] /= sample_number; // get the average of the sensor values
        check_values(sensorValues[j], i, j);
      }
  }
}

void check_values(int value, int row, int column)
{
  int array[]={0,0,0};
  int mini = 5000;
  int index = 0;
  array[0] = abs(black_value - value);
  array[1] = abs(blank_value - value);
  array[2] = abs(white_value - value);
  for(int i = 0; i < 3; i ++)
  {
     if(mini > array[i])
     {
        index = i;
       mini = array[i]; 
     }
  }
  switch(index)
 {
    case 0: // black
     board[7*row +column] = BLACK;
     break;
    case 1: // blank
      board[7*row + column] = BLANK;
      break;
    case 2: // white
      board[7*row + column] = WHITE;
      break;
 }
  
}
