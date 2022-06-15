#ifndef Controller_h
#define Controller_h

#include <OctoWS2811.h>
#include "configuration.h"

class Controller
{

  public:
    Controller();

    bool InitLeds(uint32_t ledsPerStrip, uint32_t numOfStrips, uint8_t configBits);
    void ShowBuffer(uint32_t leds, uint32_t numOfStrips);
    void PrintBuffer(uint32_t leds);
    
  private:
    OctoWS2811* _leds;
    uint32_t _bufferSize;

    byte _pinList[4] = {DATA_PIN_1, DATA_PIN_2, DATA_PIN_3, DATA_PIN_4};
    void PrintAsRGB(int pos, int color);
};

#endif
