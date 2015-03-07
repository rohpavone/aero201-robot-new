#include <Servo.h>

// servo stuff
int total = 0;
Servo myServo;  // create a servo object 
int servo_pin = 3;


int motor_right[] = {12,  13};
int motor_left[] = {10, 11};
int ENABLE1 = 9;
int ENABLE2 = 6;
int reverse;
// analog read pins of the line readers
int left = A0;
int right = A1;

// line following sensors
int left_middle = A0;
int middle = A1;
int right_middle = A2;

// front sensor
int front_claw = A3;
 
// driving states
String state="";
String prev_state="";

// timing for line counting
long previousMillis = 0;
int onTime = 250;

// index along path
int index = 0;

//int target[] = {3,1};

// LINE COUNTING 
int path[] = {1}; // SET THIS TO DESIRED NUMBER OF STRAIGHT LINES WANTED along each path
                  // this needs to be determined dynamically with simple coordinates in
                  // the future 
int lines_so_far= 0;
int total_paths = 1;

// TURNING
// direction of bot
// 1: East (+x direction)
// 2: South (+y direction)
// 3: West (-x direction)
// 4: North (-y direction)
int dire = 1; 

// target direction (testing for now)
int directions[]= {1}; // 2 = SOUTH -> need to direction associated with each path.


// control variables
boolean ENABLE_COUNT = true;
boolean DONE = false;
boolean REFRACT = false;
boolean LEFT = false;

// read state
int line_read[] = {LOW, LOW}; // 0 is left, 1 is right
void setup()
{
   Serial.begin(9600);
myServo.attach(servo_pin);
  myServo.write(90); // close it first

  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  pinMode(ENABLE1, OUTPUT);
  pinMode(ENABLE2, OUTPUT);
   analogWrite(ENABLE1, 255);//half motor speed
  analogWrite(ENABLE2, 255);//half motor speed
  reverse = 0;
  pinMode(5, OUTPUT); // indicator for certain variables
    pinMode(8, OUTPUT); // indicator for certain variables
    

    //determine_path();

  

}

//void determine_path(){
//    path[0] = target[0];
//  path[1] = target[1];
//    if(path[0] >= 0)
//  {
//     directions[0] = 1;
//  }
//  else
//  {
//     directions[0] = 3;
//  }
//  
//  if(path[1] >= 0)
//  {
//     directions[1] = 2; 
//  }
//  else
//  {
//    directions[2]= 4;  
//  }
//}

void loop()
{
drive();
}

int check_rotate(){
  // get difference to determine orientation required
  int dif = directions[index] - dire;
//  Serial.println(dif);
  
  switch(dif){
    case 0:
      break;
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
  return dif; // if 0, then direction is good and can proceed with motion
}

void turn(boolean dir){
  int left_m =  read_line(left_middle);
  int mid =  read_line(middle);
  int right_m =  read_line(right_middle);
  int first_time = 0;
  int wait = 250;
  boolean reversing = true, turning = true;
  read_lines(left, right);
  
  analogWrite(ENABLE1, 255);
    analogWrite(ENABLE2, 255);
 
 first_time = millis();
 while(millis() - first_time <= wait)
 {
    state = "FORWARD";
   choose_drive(); 
 }
 first_time = millis();
 while(millis() - first_time <=wait*2)
 {
   if(dir)
    {
       state = "LEFT"; 
    }
    else
    {
       state = "RIGHT"; 
    }
    choose_drive();
    Serial.println("AUTO TURN");
 }
 mid = read_line(middle);
 while(!(mid||left_m||right_m)){
    if(dir)
    {
       state = "LEFT"; 
    }
    else
    {
       state = "RIGHT"; 
    }
    choose_drive();
      left_m =  read_line(left_middle);
  mid =  read_line(middle);
  right_m =  read_line(right_middle);
    Serial.println("ALIGN with middle - " + mid);
  }
  
  state = "STOP";
  choose_drive();
  if(dir)
  {
    if(dire == 1)
    {
       dire = 4;
    }
    else{
      dire -=1;
    }
  }
  else
  {
    if(dire == 4)
    {
       dire = 1; 
    }
    else{
       dire += 1;
    }
  }

  // turn successful
  left_m =  read_line(left_middle);
  mid =  read_line(middle);
  right_m =  read_line(right_middle);
  Serial.println("LEFT - " + String(left_m) + ", MID - " + String(mid) + ", RIGHT - " + String(right_m));
  ENABLE_COUNT = false;
  analogWrite(ENABLE1,125);
  
  analogWrite(ENABLE2,125);
}

int align(boolean reversing)
{
    // ensure the alignment with the front line is correct
    int left_m = read_line(left_middle);
    int mid = read_line(middle);
    int right_m = read_line(right_middle);
    Serial.print(" ALIGNING: ( " + String(left_m) + ", " + String(mid) + ", " + String(right_m) + ") - ");
    reverse = false;
    if(!left_m && !right_m) // black is true, white is false
    {
        Serial.print(" Middle is triggered - ");
        ENABLE_COUNT = true;
        reverse = reversing;
        state = "FORWARD";
        REFRACT = false;
        return 0;
    }
    else if ((mid && left_m || mid && right_m || left_m && right_m) && ENABLE_COUNT)
    {
       Serial.print("Line crossing - count down");
       ENABLE_COUNT = false;
       state = "FORWARD";
       REFRACT=false;
       return 1;
    }
    else if(!REFRACT)
    {
        if(!right_m && left_m) // right of line
        {
          Serial.print(" -  RIGHT OF LINE - ");
          LEFT = false;
          state = "LEFT";
          REFRACT = true;
        }
        else if(!left_m && right_m) // left of line
        {
          Serial.print(" -  LEFT OF LINE - ");
          LEFT = true;
          REFRACT = true;
           state = "RIGHT"; 
        }
    }
    return 0;
   
   
}

int read_line(int pin)
{
  int left_read = analogRead(pin);
 // Serial.print(" - PIN READ - " + String(left_read) + " - ");
  if (left_read < 200) // bias to trigger black easier
  {
      return 0; //white
  }
  else
  {
        return 1; //black
  }
}
void read_lines(int pin1, int pin2){
  int left_read = analogRead(pin1);
  int right_read = analogRead(pin2);
  if (right_read < 700)
  {
   line_read[1] = 0;
  }
  else
  {
     line_read[1] = 1;
  }
 // Serial.print("LEFT: "+ String(line_read[0])+  ", VAL: "+ String(left_read)+ " -  RIGHT: " + String(line_read[1]) + ", VAL: " + String(right_read));
}

void get_ball()
{
  // in front of leg now
  // rotate towards the brushes until ~1000
  int stamp = 0;
  int drive_time = 100;
  int first_val = 0;
  int second_val = 0;
  int brush_thresh = 950;
  analogWrite(ENABLE1, 255);
  analogWrite(ENABLE2, 255);
  Serial.println("GETTING BALL");
  while(analogRead(front_claw) < 1000)
  {
      choose_drive("RIGHT"); 
  }
    choose_drive("STOP");
    stamp = millis();
  while(millis() - stamp < drive_time)
  { choose_drive("RIGHT");
  }
  stamp = millis();
//  while(millis() - stamp < drive_time)
//  {   
//    Serial.println("LOOKING FOR BRUSHES");
//    choose_drive("FORWARD");
//
//  }
  choose_drive("STOP");
  // start drive-rotate process
  while(true){
    first_val=analogRead(front_claw);
    if(first_val < brush_thresh)
    {
      Serial.println(first_val);
      break;
    }
    else
    {    
        stamp = millis();
        while(millis() - stamp < drive_time/2) 
         choose_drive("RIGHT"); 
         
        choose_drive("STOP");
    }
  }
  Serial.println("FUOND THIS SHIT");
  // open claw
  myServo.write(180);
  first_val = analogRead(front_claw);
  
  while(first_val > 700)
  {
     choose_drive("FORWARD"); 
       first_val = analogRead(front_claw);
       Serial.println("CLAW READING - " + String(first_val));
  }
  choose_drive("STOP");
  myServo.write(90);
    
}

void drive(){
  
  if(DONE){

    return;
  }
  if(check_rotate()){
    return;
  }




  if(lines_so_far == path[index])
   {
      state = "STOP";
      choose_drive();
      lines_so_far = 0;
      index += 1;
        if(index == total_paths)
        {
          DONE = true;
              get_ball();
          return;
        }
      return;
      
   }
//   if(millis() - previousMillis >= onTime)
//   {
//       digitalWrite(8, HIGH);
//   }
//   else{
//      digitalWrite(8, LOW); 
//   }
//  // both black
//   if (left_read && right_read)
//   {
//     
//     
//        state="FORWARD"; 
//      // we were previously on white, now disable counting until
//      // on white again
//      if(ENABLE_COUNT && millis() - previousMillis >= onTime){
//        ENABLE_COUNT = false;
//        lines_so_far += 1;
//      }
//      
//   }
//
//   else if(!left_read && !right_read)
//   {
//     // if previously disabled, reenable now
//     if(!ENABLE_COUNT)
//     {
//         ENABLE_COUNT = true;
//         previousMillis = millis();
//       
//     }
//   }

  lines_so_far += align(false);
  choose_drive();
  
  
}
void choose_drive(String s){
   state = s;
  choose_drive(); 
}
void choose_drive()
{
 Serial.println(state);
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
 prev_state = state;
 
}

void motor_stop(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);

}

void drive_forward(){
  digitalWrite(motor_left[0], HIGH^reverse);
  digitalWrite(motor_left[1], LOW^reverse);

  digitalWrite(motor_right[0], HIGH^reverse);
  digitalWrite(motor_right[1], LOW^reverse);
}

void drive_backward(){
  digitalWrite(motor_left[0], LOW^reverse);
  digitalWrite(motor_left[1], HIGH^reverse);

  digitalWrite(motor_right[0], LOW^reverse);
  digitalWrite(motor_right[1], HIGH^reverse);
}

void turn_left(){
  digitalWrite(motor_left[0], LOW^reverse);
  digitalWrite(motor_left[1], HIGH^reverse);

  digitalWrite(motor_right[0], HIGH^reverse);
  digitalWrite(motor_right[1], LOW^reverse);
}

void turn_right(){
  digitalWrite(motor_left[0], HIGH^reverse);
  digitalWrite(motor_left[1], LOW^reverse);

  digitalWrite(motor_right[0], LOW^reverse);
  digitalWrite(motor_right[1], HIGH^reverse);
}

void right_only(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

void left_only(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}


