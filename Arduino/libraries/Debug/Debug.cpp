#include "Arduino.h"
#include "Debug.h"

Debug::Debug()
{
  Serial.begin(9600);
   write_out("Ready!", 6);
   debug = true;
   mobile = false;
}

void Debug::write_out(String str, int length)
{
  if(debug)
      Serial.print(str+"\n");
}

char Debug::read_in()
{
  char in = ' ';
  if(Serial.available())
  {
    in = Serial.read();
  }
  return in;
}

void Debug::write_out(String str)
{
   write_out(str, str.length());
}
