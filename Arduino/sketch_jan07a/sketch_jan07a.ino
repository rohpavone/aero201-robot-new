// two main functions in every arduino board
int yellow = 0;

void setup(){
  pinMode(2, INPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);  
}

void loop(){
  yellow = digitalRead(2); //read state of 2
  if(yellow == LOW){
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(4, LOW);
    digitalWrite(6, HIGH);
  }
}
