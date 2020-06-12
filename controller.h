#ifndef Controller_h
#define Controller_h

#include <OctoWS2811.h>
#include "configuration.h"

class Controller
{

  public:
    Controller();

    bool InitLeds(int vertical, int horizontal, int numOfStrips, char* order);
    bool ShowBuffer(uint8_t* buffer, int size);
    
  private:
    int _vertical;
    int _horizontal;
    int _numberOfStrips;
    char* _order;
    
    int _ledsPerStrip;
    int _colorsPerBuffer;
    int _bufferLength[MAX_OF_STRIPS];
    
    OctoWS2811* _leds;        
    
    int GetCount(int length, int offset);
};

#endif
