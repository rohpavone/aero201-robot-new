int sensorMin = 1023; // minimum sensor value
int sensorMax = 0; // max value
int sensorValue = 0;
int counte = 0;
const int sensorPin = A0; 

void setup(){
  Serial.begin(9600);
   // turn on LED Signal
  
  analogReference(EXTERNAL);
}

void loop(){
   sensorValue = analogRead(sensorPin);
   counte = counte + 1;
    //sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);
   //sensorValue = constrain(sensorValue, 0, 255);
   Serial.print("Sensor value: ");
  Serial.print(sensorValue);
  float voltage = (sensorValue/1024.0)*3.3;
  float temperature = (voltage) * 100 - 50;
  Serial.print(", Temperature: ");
  Serial.println(temperature);
}
