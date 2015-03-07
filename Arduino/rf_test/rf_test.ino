//TRANSMITTER CODE
#include <VirtualWire.h>

int incomingByte = 0; 
int maxi = 1005;
String inString = "";    // string to hold input
int output[] = {45,47,49,51};
int analogIn = A7;
int left = 0;


void setup()
{
  Serial.begin(9600);	  // Debugging only
  Serial.println("setup");

  pinMode(52, OUTPUT);
  pinMode(43, INPUT);
  pinMode(analogIn, INPUT);
  for(int i = 0; i < 4; i++)
  {
     pinMode(output[i], OUTPUT);
  }
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(1000);	 // Bits per sec
  vw_set_tx_pin(53); //Pin 3 is connected to "Digital Output" of receiver

}

void loop()
{
  char msg[] = {'H','O','P','P','E','R',' ','R',':',' ',' ',0 };
//  if(Serial.available() > 0)
//  {
//    int inChar = Serial.read();
    // if you get a newline, print the string,
    // then the string's value:
    unsigned int value = analogRead(analogIn);
     unsigned int piece = value_check(value);
     int left = digitalRead(43);
     if(left){
        digitalWrite(52, HIGH);
       msg[7] = 'L';
     }
     else
     {
      digitalWrite(52, LOW);
     }
     msg[10] = piece + 32;
     LED_OUTPUT(piece);
    Serial.println(msg);
//    if (inChar == '\n') {

      inString.toCharArray(msg, inString.length());
      vw_send((byte *)msg,strlen(msg));
      vw_wait_tx();
      // clear the string for new input:
      inString = "";
//    }
//  }
}


void LED_OUTPUT(unsigned int input)
{
   unsigned int mask = 1;
  for (int i = 0; i < 4; i++)
 {
    digitalWrite(output[i], input & mask);
    mask = mask << 1;
 } 
}
unsigned int value_check(unsigned int value)
{
   if (value < maxi/12){
       return 1;   
   }
   else if( value < 2*maxi/12){
     return 2;  
   }
  else if( value < 3*maxi/12){
    return 3;      
  }
  else if(value < 4*maxi/12){
    return 4;
        
  }
  else if(value < 5*maxi/12){
    return 5;
      
  }
  else if(value < 6*maxi/12){
    return 6;
        
  }
  else if(value < 7*maxi/12){
    return 7;
    
  }
  else if(value < 8*maxi/12){
    return 8;
    
  }
  else if(value < 9*maxi/12){
    return 9;
    
  }
   else if( value < 10*maxi/12){
     return 10;

   }
    else if(value < 11*maxi/12){
      return 11;

    }
     else if(value < 12*maxi/12){
       return 12;

     }
    else{
      return 0;
   }
}
