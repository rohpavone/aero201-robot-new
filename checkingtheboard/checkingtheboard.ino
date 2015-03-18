#include <Servo.h>

#define RED 7
#define GREEN 5
#define YELLOW 3


Servo myServo;
int servoPin = 7;
int sensorPins[] = {A9, A10,A11, A12,A13,A14,A15};

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
int sample_number = 1;


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
  
  //myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop(){
  // reset the values
  for(int i = 0; i < 7; i++)
  {
     sensorValues[i] = 0; 
  }
  
  int average = 0;
  
  // check all the rows

     // myServo.write(heights[i]);
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
        average += sensorValues[j];
        //check_values(sensorValues[j], i, j);
        Serial.print(String(j) + ". " + String(sensorValues[j]) + ", ");
      }
      Serial.println("");
}

void check_values(int value, int row, int column, int average)
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
 write_led(index);
  
}

void write_led(int mode){
   switch(mode)
  {
   case 0:
     // black
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, LOW);
     break;
   case 1:
      // blank
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, HIGH);
     break;
   case 2:
     // white
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
     break;
  } 
}
