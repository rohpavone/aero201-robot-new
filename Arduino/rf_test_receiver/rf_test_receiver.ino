// RECEIVER CODE
#include <VirtualWire.h>

int coordinates [][24] = {{0,3, 1,2, 2,3},{1,3, 2,2, 3,3},{0,2, 1,3, 2,2},{1,2, 2,3, 3,2},{0,2, 1,1, 2,2},{1,2, 2,1, 3,2},{0,1, 1,2, 2,1},{1,1, 2,2, 3,1},{0,1, 1,0, 2,1},{1,1, 2,0, 3,1},{0,0, 1,1, 2,0},{1,0, 2,1, 3,0},{4,3, 5,2, 6,3},{5,3, 6,2, 7,3},{4,2, 5,3, 6,2},{5,2, 6,3, 7,2},{4,2, 5,1, 6,2},{5,2, 6,1, 7,2},{4,1, 5,2, 6,1},{5,1, 6,2, 7,1},{4,1, 5,0, 6,1},{5,1, 6,0, 7,1},{4,0, 5,1, 6,0},{5,0, 6,1, 7,0}};

int digital_out = 4;
void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");


  //Initialize the IO and ISR
  vw_set_ptt_inverted(true);
  vw_setup(1000);	    // Bits per sec
  vw_set_rx_pin(digital_out);         //Pin 2 is connected to "Digital Output" of receiver
  vw_rx_start();           // Start the receiver PLL running

}

void loop()
{

  //Set buffer array based on max message length
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  //Set variable to indicate buffer length
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  String str;
  boolean left = false;
  int index = -1;
  //Serial.println("In the loop!");
  if (vw_have_message()) // Non-blocking
  {

    vw_get_message(buf, &buflen);
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");
    
     for (int i = 0; i < buflen; i++)
    {
      str += String((char)buf[i]);      
      // Print message received in buffer through this loop
      //add space to distinguish characters from each other if showing ASCII decimal #
      //Serial.print(" "); 
    }
    Serial.println(str);
    left = (char)buf[7] == 'L';
      
    index = (char)buf[10] - 32 - 1;
    Serial.println(index);
    if(!left)
      index += 12;
    
    for(int i = 0; i < 3; i++)
    {
       Serial.print("(" + String(coordinates[(unsigned int)index][2*i]) + ", " + String(coordinates[(unsigned int)index][2*i + 1]) + "), "); 
    }
    Serial.println("");
    
//    if(left)
//      Serial.println("L");
//    else
//      Serial.println("R");
    
  }
}
