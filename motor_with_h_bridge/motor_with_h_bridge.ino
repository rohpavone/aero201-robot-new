// --------------------------------------------------------------------------- Motors
int motor_left[] = {12, 13};
int motor_right[] = {9, 10};
int ENABLE = 2;

// digital read pins of the line readers
int left = A0;
int right = A1;

// current location, with target, in x coords only
int current = 0;
int target_x = 5000000;
int TILE_SIZE = 1;
int tiles_x = 0;
int line_count = 0;
// read state
int left_read = LOW;
int right_read = LOW;

boolean ENABLE_COUNT = true;

// --------------------------------------------------------------------------- Setup
void setup() {
  Serial.begin(9600);
  
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
  tiles_x = (target_x - current) / TILE_SIZE;
  line_count = 0;
}

// --------------------------------------------------------------------------- Loop
void loop() 
{
  left_read = analogRead(left);
   right_read = analogRead(right);
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
      Serial.print("LEFT: ");
   Serial.print(left_read);
   Serial.print(", RIGHT: ");
   Serial.print(right_read);
   Serial.print(", LINES LEFT: ");
   Serial.print(tiles_x - line_count);
   if (left_read && right_read)
   {
      drive_forward();
      if(ENABLE_COUNT){
        line_count += 1;
        ENABLE_COUNT = false;
      } 
   }
   else if(left_read && ENABLE_COUNT || right_read && !ENABLE_COUNT)
   {
      turn_left();
   }
   else if(right_read && ENABLE_COUNT || left_read && !ENABLE_COUNT)
   {
     turn_right();  
   }
   else
   {
     if(!ENABLE_COUNT)
     {
       ENABLE_COUNT = true;
     }
     drive_forward();  
   }
   if (line_count == tiles_x)
   {
      motor_stop(); 
   }
}

// --------------------------------------------------------------------------- Drive

void motor_stop(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], LOW);
//Serial.println(", STATE STOP");
}
void drive_forward(){
digitalWrite(motor_left[0], HIGH);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], HIGH);
digitalWrite(motor_right[1], LOW);
Serial.println(", STATE FORWARD");
}

void drive_backward(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], HIGH);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], HIGH);
Serial.println(", STATE BACK");
}

void turn_left(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], HIGH);

digitalWrite(motor_right[0], HIGH);
digitalWrite(motor_right[1], LOW);
Serial.println(", STATE LEFT");
}

void turn_right(){
digitalWrite(motor_left[0], HIGH);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], HIGH);
Serial.println(", STATE RIGHT");
}
