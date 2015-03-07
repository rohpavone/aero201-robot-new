// --------------------------------------------------------------------------- Motors
int motor_left[] = {12, 13};
int motor_right[] = {8, 9};
int input_pins[] = {A0, A1, A2};
int vals[3];
int ENABLE = 7;
unsigned char ena = HIGH;
// --------------------------------------------------------------------------- Setup
void setup() {
Serial.begin(9600);

// Setup motors
int i;
for(i = 0; i < 2; i++){
pinMode(motor_left[i], OUTPUT);
pinMode(motor_right[i], OUTPUT);
}
pinMode(ENABLE, OUTPUT);
for (int i = 0; i < 3;i++)
{
   pinMode(input_pins[i], OUTPUT);
}
digitalWrite(ENABLE, HIGH);

}
// --------------------------------------------------------------------------- Loop
void loop() {
for(char i = 0; i<3; i++)
{
  vals[i] = analogRead(input_pins[i]); 
  Serial.println(vals[i]);

}

if(vals[1] > 100)
{
  drive_forward();
}
else
{
  if(vals[0] >100)
  {
   turn_left(); 
  }
  else if(vals[2] > 100){
    turn_right(); 
  }
  else{
     motor_stop();
  }
}
  /*
Serial.println("1");
drive_forward();
delay(1000);
motor_stop();


Serial.println("2");
drive_backward();
delay(1000);
motor_stop();

Serial.println("3");
turn_left();
delay(1000);
motor_stop();

Serial.println("4");
turn_right();
delay(1000);
motor_stop();

Serial.println("5");
motor_stop();
delay(1000);
motor_stop();*/
}

// --------------------------------------------------------------------------- Drive

void motor_stop(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], LOW);
delay(25);
}

void drive_forward(){
digitalWrite(motor_left[0], HIGH);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], HIGH);
digitalWrite(motor_right[1], LOW);
}

void drive_backward(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], HIGH);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], HIGH);
}

void turn_left(){
digitalWrite(motor_left[0], LOW);
digitalWrite(motor_left[1], HIGH);

digitalWrite(motor_right[0], HIGH);
digitalWrite(motor_right[1], LOW);
}

void turn_right(){
digitalWrite(motor_left[0], HIGH);
digitalWrite(motor_left[1], LOW);

digitalWrite(motor_right[0], LOW);
digitalWrite(motor_right[1], HIGH);
}

