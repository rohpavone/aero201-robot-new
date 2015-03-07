/*
  Set up the debug system for this program.
*/

#ifndef Debug_h
#define Debug_h

#include "Arduino.h"

class Debug
{
  public:
    Debug();
    void write_out(String str, int length);
    void write_out(String str);
    char read_in();
    boolean debug;
    boolean mobile;
};

#endif
