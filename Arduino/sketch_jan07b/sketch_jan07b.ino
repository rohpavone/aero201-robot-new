const int sensorPin = A0;

void setup(){
 Serial.begin(9600); // set baud rate
 
}

void loop(){
  int temperature_read = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.print(temperature_read);
  float voltage = (temperature_read/1024.0)*5.0;
  float temperature = (voltage) * 100;
  Serial.print(", Temperature: ");
  Serial.println(temperature);
  
  
}
