// motor points
int LED[] = {12, 13};
int ENABLE = 7;
int VOLTAGE = 5;
unsigned char counter = 0;
void setup()
{
   pinMode(ENABLE, OUTPUT);
  pinMode(VOLTAGE, OUTPUT);
 pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT); 
  
  digitalWrite(ENABLE, HIGH);
}

void loop()
{
    counter = counter + 1;
    analogWrite(VOLTAGE, counter);
    digitalWrite(LED[0], HIGH);
    digitalWrite(LED[1], LOW);
    digitalWrite(LED[0], LOW);
    digitalWrite(LED[1], HIGH);
}
