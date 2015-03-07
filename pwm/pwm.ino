int * output = {3, 5,6};
int [3] sensors ={A5, A4, A3};
int[3] sensVals; 
void setup(){
 Serial.begin(9600);
 pinMode(redLed, OUTPUT);
 pinMode(greenLed, OUTPUT);
 pinMode(blueLed, OUTPUT);
 for(int i = 0; i < 3; i++)
 {
    sensVals[i] = 0; 
 }
}

void loop()
{
  for( int i = 0; i <3;i++)
  {
     sensVals[i] = analogRead(sensors[i])/4;
     analogWrite(output[i], sensVals[i]);
  }
 
}

