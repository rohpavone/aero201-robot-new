#include <VirtualWire.h>

int IN = A0;
int output[] = {46,48,50,52};
int maxi = 1024;
int left_hopper = 44;
int send_signal = 53;

// communication
int data_out = 28;



boolean SENDING = false;
boolean sent = false;

unsigned int value = 0;
void setup()
{
    Serial.begin(9600);
    pinMode(IN, INPUT);
    for(int i = 0; i < 4; i++)
    {
       pinMode(output[i],  OUTPUT); 
    }
    
    pinMode(left_hopper, INPUT);
    pinMode(send_signal, INPUT);
    
    digitalWrite(26, LOW);
    digitalWrite(30, HIGH);
    digitalWrite(32, LOW);
  
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_set_tx_pin(28); //Pin 3 is connected to "Digital Output" of receiver
    
}

void loop()
{
     int left_val = digitalRead(left_hopper);
     int send_val = digitalRead(send_signal);
     value = analogRead(IN);
     left_val = digitalRead(left_hopper);
      send_val = digitalRead(send_signal);
     unsigned int piece = value_check(value);
     LED_OUTPUT(piece);
     Serial.println("Sending! ------------------------------------------");
     send_hopper_location(value);
     SENDING = true;
   
   if(left_val)
   {
      Serial.println("LEFT HOPPER"); 
   }
   
}

void send_hopper_location(unsigned int location){
  char * msg;
  msg[0] = location;
  Serial.println("Writing...");
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  sent = true;
  Serial.println("Sent!");
  
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
unsigned int value_check(unsigned int input)
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
