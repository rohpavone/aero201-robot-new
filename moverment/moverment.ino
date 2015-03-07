// motor control stuff
const int wheel_radius = 5;
const int wheel_distance = 5;
const int motor_omega = 7.456; // rotations per second per volt
const int motor_left = 3;
const int motor_right = 5; // PWM channels set now
const int motor_max = 5;

const float pi = 3.1415926;
const float circ = 2*pi*wheel_radius;

// initial coordinates
const int x0 = 70;
const int y0 = 70; 

// coordinates
float x = 0, y = 0;
float average_s = 0;
float angle = 0;
float sR = 0;
float sL = 0;
char dir = 1; // 1 is turning left, 0 is turning right, -2 is forward, 2 is backwards

void setup()
{
  Serial.begin(9600);
}

void mov(char dir, float dist, float sped)
{
  if(dir < 2 && dir >= 0)
  {
     if(dir)
    {
      // turn left
    } 
    else
    {
       // turn right 
    }
  }
  else
  {
      float voltage = sped/(circ*motor_omega);
      float t = dist/sped;
      voltage = map(voltage, 0, motor_max, 0, 255)
      analogWrite(motor_left, voltage);
      analogWrite(motor_right, voltage);
      // set timer interup for time t to interupt this operation 
  }
}

void loop()
{
  // get turn signals
  
  // turn here
  turn();

  
}
