int motor_right[] = {7,  13};
int motor_left[] = {10, 11};
int ENABLE = 3;
int reverse;


void setup()
{
    Serial.begin(9600);


  // Setup motors
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  pinMode(ENABLE, OUTPUT);
   digitalWrite(ENABLE, HIGH);//half motor speed
}

void loop()
{
  drive_forward();
  delay(500);
  
  motor_stop();
  delay(500);
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

void left_only(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

void right_only(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
}

