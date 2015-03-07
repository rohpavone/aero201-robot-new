// stepper attempt

// pin layout for bipolar stepper motor
const int RED = 8, GREY = 9, YELLO = 10, BLCK = 11;
int counter= 0;
void setup(){
   pinMode(RED, OUTPUT);
  pinMode(GREY, OUTPUT);
 pinMode(YELLO, OUTPUT);
pinMode(BLCK, OUTPUT);
Serial.begin(9600);
}

void loop()
{
    one();
    two();
    three();
    four();
      
      
  
}

void one()
{
  Serial.println("ONE");
  digitalWrite(RED, LOW);
  digitalWrite(GREY, HIGH);
  digitalWrite(BLCK, HIGH);
  digitalWrite(YELLO, LOW);
  delay(10);
  
}
void two()
{
  Serial.println("TWO");
   digitalWrite(RED, LOW);
  digitalWrite(GREY, HIGH);
  digitalWrite(BLCK, LOW);
  digitalWrite(YELLO, HIGH);
    delay(10);
}
void three()
{
  Serial.println("THREE");
   digitalWrite(RED, HIGH);
  digitalWrite(GREY, LOW);
  digitalWrite(BLCK, LOW);
  digitalWrite(YELLO, HIGH);
    delay(10);
}
void four(){
 Serial.println("FOUR"); 
    digitalWrite(RED, HIGH);
  digitalWrite(GREY, LOW);
  digitalWrite(BLCK, HIGH);
  digitalWrite(YELLO, LOW);
    delay(10);
}
