// motor characteristics
const int wheel_radius = 5;
const int wheel_distance = 5;
const int motor_omega = 7.456; // rotations per second per volt
const int motor_max = 5;


// set to PWM
const int LMPIN = 3;
const int RMPIN = 5;

// power LED
const int LED = 2; 

// input pins

const int NUMSENSOR = 6;
const int LINESENSOR[NUMSENSOR] =  {8,9,10,11,12, 13};

// global variables
int error = 0;
int prev_error = 0;
int p = 0;
int integral = 0;
int derivative = 0;
int correction = 0;
int target_pos = 0;
int current_pos = 0;
int Kp = 0;
int Ki = 0;
int Kd = 0;

void initPorts()
{
   // SET THE PINs
  pinMode(LMPIN, OUTPUT);
  pinMode(RMPIN, OUTPUT);
  pinMode(LED, OUTPUT);
  
  for(unsigned char i = 0; i < NUMSENSOR; i ++)
   {
   pinMode(LINESENSOR[i], INPUT);
   }
}
  
void initInterrupts()
{
  // what do here
  
}

void initPWM()
{
  // nothing to do here
}

void powerledoff()
{
  digitalWrite(LED, LOW);
}
void powerledon(){
  digitalWrite(LED, HIGH);
}

void calcError()
{
  error = target_pos - current_pos;
  p = error * Kp;
  integral = integral + error;
  integral = integral * Ki;
  derivative = error - previous_error;
  correction = p + integral + derivative;
  
  previous_error = error;
}

void leftMF(int sped)
{
  
}
void leftMB()
{
  
}

void leftMS(){
  
}

void rightMF(){
  
}

void rightMB(){
  
}

void rightMS(){
  
}

void setup()
{
   
}


