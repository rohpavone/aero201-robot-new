#include <Debug.h>

// -------------------------------------------------------------- Motors

Debug deb;
int motor_left[] = {12,  13};
int motor_right[] = {10, 11};
int ENABLE = 2;

// analog read for line followers
int middle = A2;
int right_middle = A3;

// analog read pins of the line readers
int left = A0;
int right = A1;

// current location, with target, in x coords only
int current[] = {0,0};
int target[] = {0,0};
int path[20]; // potentially 20 max
int directions[20];
int dire = 1; // directions are 1 , 2 ,3,4 (East, South, West, North)
int reverse = 0; // 0 means drive forward, 1 means backwards
int TILE_SIZE = 1;
int tiles []= {0,0};
int line_count = 0;
int index = 0;
int total_paths = 1;

String state = "STOP";
String prev_state = state;
String output_string = "";


// read state
int line_read[] = {LOW, LOW}; // 0 is left, 1 is right


boolean ENABLE_COUNT = true;
boolean ENABLE_ROTATE = false;

//-------------------------------------------------------------- Setup
void setup() {
  Serial.begin(9600);
  deb.write_out("Ready!", 6);
  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, HIGH);


    // assuming manhattan distance and path for now
  // -> and v are positive direction for coordinates
  tiles[0] = (target[0] - current[0]) / TILE_SIZE;
  tiles[1] = (target[1] - current[1])/TILE_SIZE;

  // x first
  String s = "";
  for(int i = 1; i < total_paths; i++)
  {
    s =  "";
    path[i] = abs(tiles[i]); // set path distance as a tile distance
    if(tiles[i] < 0)
    {
      directions[i] = i  + 2;
    }
    else
    {
      directions[i] = i ;
    }
    s = "Tiles to go: " + String(tiles[i]) + ", Path length: " +  String(path[i]) +", Direction Chosen: " + String(directions[i]);
    deb.write_out(s, s.length());
  }
  path[0] = 1;
  directions[0] = dire; // get it to drive up to the first line to begin
}

// ------------------------------------------- Loop
void loop()
{
  output_string = "";
  // path already determined
  // if index is not through all the path, continue

   // align(); // check if line follower works -> does not work (line sensors are off for some reason. Cannot detect black at the given distance.
    if(index < total_paths)
    {
      if(dire == directions[index])
      {
        reverse = false;
        output_string += "DIRECTION: " + String(dire) + " - ";
        drive();
        }
        else
        {
        check_rotate();
        }
    }
    else
    {
       //at destination
     motor_stop();
    }
  deb.write_out(output_string);
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
  String message = "LEFT: " + String(left_read) + ", RIGHT: " + String(right_read) + " - ";
  output_string += message;
  line_read[0] = left_read;
  line_read[1] = right_read;
}

void check_rotate(){
  // get difference to determine orientation required
  int dif = directions[index] - dire;
  output_string += "DIFFERENCE: " + String(dif) + " - ";
  switch(dif){
    case -3:
      turn(false);
      break;
    case -2:
      turn(false);
      break;
    case -1:
      turn(true);
      break;
    case 1:
      turn(false);
      break;
    case 2:
      turn(false);
      break;
    case 3:
      turn(true);
      break;
  }
}

void alter_dire(){
  if(reverse)
    if(dire != 1)
      dire -= 1;
    else
      dire = 4;
  else
    if(dire != 4)
      dire += 1;
    else
      dire = 1;
}

void turn(boolean direction){
  reverse = direction;

  read_lines(left, right);
  if(ENABLE_ROTATE){ // we've crossed the original set of lines
    // negative direction is CCW
      if(line_read[0] && line_read[1]){ // we're on next lines
        motor_stop();
        ENABLE_ROTATE = false;
        alter_dire(); // change direction by one, lets it reset
      }
      else if(line_read[0]){ // left is now black, right is not
        right_only(); // moves right only
      }
      else if(line_read[1]){
        left_only();
      }
      else{
        turn_right();
      }
  }
  else
  {
      if(!line_read[0] && !line_read[1]) // on original black line
      {
        output_string += "STILL ON SAME LINE - ";
        ENABLE_ROTATE = true; // both on white now? allow decrease to occur
      }
      else
      {
        turn_right();
      }
  }
}

void align()
{
    // ensure the alignment with the front line is correct
    read_lines(middle, right_middle); // get readings of pair

 output_string += "MIDDLE: " + String(line_read[0]) +", MID_RIGHT: " + String(line_read[1]) + " - ";
    if(line_read[0]) // as long as this reads black, we're good
    {
      return;
    }
    else // getting off line
    {
      if(line_read[1]) // right middle is black, so turn right to align
        turn_right();
      else
        turn_left(); // both are on right side of line, turn left
    }



}

void drive(){
  //align();
  prev_state = state;
  read_lines(left, right);
  int left_read = line_read[0];
  int right_read = line_read[1];
  // stop driving because we reached our destination in this direction
  if (line_count == path[index])
  {
     state = "STOP";
     motor_stop();
     index += 1; // go to next direction/linear path
  }

  // both black
   if (left_read && right_read)
   {
      state = "FORWARD";
      // we were previously on white, now disable counting until
      // on white again
      if(ENABLE_COUNT){
        line_count+= 1;
        ENABLE_COUNT = false;
      }
   }
   // be sure to stay aligned when going on and coming off lines
   else if(left_read && ENABLE_COUNT || right_read && !ENABLE_COUNT)
   {
     state = "LEFT";
     turn_left();
   }
   else if(right_read && ENABLE_COUNT || left_read && !ENABLE_COUNT)
   {
     state = "RIGHT";
     turn_right();
   }
   // both on white
   else
   {
     // if previously disabled, reenable now
     if(!ENABLE_COUNT)
     {
       ENABLE_COUNT = true;
     }
     state = "FORWARD";
   }

   if(state != prev_state){
     if(state == "FORWARD")
          drive_forward();
     else if(state == "STOP")
          motor_stop();
     else if(state == "LEFT")
          turn_left();
     else if(state == "RIGHT")
          turn_right();

     }

}

//---------------------------------------------------- Drive


// xoring with reverse does following: if reverse is 0, then remains same
// if reverse is 1, then the signal is switched (reversing directions)
void motor_stop(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], LOW);
output_string += "STATE STOP - ";
}
void drive_forward(){

digitalWrite(motor_left[0], HIGH^reverse);
digitalWrite(motor_left[1], LOW^reverse);

digitalWrite(motor_right[0], HIGH^reverse);
digitalWrite(motor_right[1], LOW^reverse);
output_string += "STATE FORWARD - ";
}

void drive_backward(){
digitalWrite(motor_left[0], LOW^reverse);
digitalWrite(motor_left[1], HIGH^reverse);

digitalWrite(motor_right[0], LOW^reverse);
digitalWrite(motor_right[1], HIGH^reverse);
output_string += "STATE REVERSE - ";
}

void turn_left(){
digitalWrite(motor_left[0], LOW^reverse);
digitalWrite(motor_left[1], HIGH^reverse);

digitalWrite(motor_right[0], HIGH^reverse);
digitalWrite(motor_right[1], LOW^reverse);
output_string += "STATE LEFT - ";
}

void turn_right(){
digitalWrite(motor_left[0], HIGH^reverse);
digitalWrite(motor_left[1], LOW^reverse);

digitalWrite(motor_right[0], LOW^reverse);
digitalWrite(motor_right[1], HIGH^reverse);
output_string += "STATE RIGHT - ";
}

void left_only(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
  output_string += "STATE LEFT ONLY - ";
}

void right_only(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  output_string += "STATE RIGHT ONLY -  ";
}
