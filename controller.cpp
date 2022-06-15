#include "controller.h"
#include <math.h>

DMAMEM uint32_t* _displayMemory;
uint32_t* _drawMemory;
int _startBightness;

Controller::Controller()
{
  
}

bool Controller::InitLeds(uint32_t ledsPerStrip, uint32_t numOfStrips, uint8_t configBits){
  
  //Init buffers
  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  _bufferSize = ledsPerStrip * numOfStrips * 3 / 4;
  _displayMemory = new uint32_t[_bufferSize];
  _drawMemory = new uint32_t[_bufferSize];

  _startBightness = 0;
 
  #ifdef DEBUG_CONTROLLER
        Serial.print("[CONTROLLER] ");
        Serial.print("NumerOfStrips:");
        Serial.print(numOfStrips);
        Serial.print(" ColorsPerBuffer:");
        Serial.print(ledsPerStrip * numOfStrips);
        Serial.print(" LedsPerStrip:");
        Serial.print(ledsPerStrip);
        Serial.print(" BufferSize:");
        Serial.print(_bufferSize);
        Serial.print(" ConfigByte:");
        Serial.print(configBits);
  #endif
  
  _leds = new OctoWS2811(ledsPerStrip, _displayMemory, _drawMemory, configBits | LED_TYPE, numOfStrips, _pinList);
  _leds->begin();
 
  #ifdef DEBUG_CONTROLLER
    Serial.print(" Leds:");
    Serial.println(_leds->numPixels());
  #endif
  
  return true;
}

void Controller::ShowBuffer(uint32_t leds, uint32_t numOfStrips){
  #ifdef DEBUG_TIME
    unsigned int startAt = micros();
  #endif
  
  #ifdef CHUNCK_COPY
    uint32_t ledsPerStrip = leds / numOfStrips;
    uint32_t bytesPerStrip = ledsPerStrip * 3;
    Serial.readBytes((char *)_drawMemory, leds * 3);
  #else
    //provides a little startup brightness ramp
    if(_startBightness < 255)
      _startBightness++;
    }
    
    for(uint32_t lPos = 0; lPos < leds; lPos ++)
    {
      auto r = (uint8_t) Serial.read();
      auto g = (uint8_t) Serial.read();
      auto b = (uint8_t) Serial.read();
      
      if(_startBightness < 255)
      {
        float factor = _startBightness / 255.0;
        r = floor(factor * r);
        g = floor(factor * g);
        b = floor(factor * b);
      }
      
      _leds->setPixel(lPos, _leds->Color(r, g, b));
    }
  #endif
    
  #ifdef DEBUG_TIME
    unsigned int endAt = micros();
    Serial.print("[FRAME] L:");
    Serial.print(leds);
    Serial.print(" T:");
    Serial.println(endAt - startAt, DEC);
  #endif
  
  _leds->show();
 
  #ifdef DEBUG_FRAME
    PrintBuffer(leds);
  #endif
}

void Controller::PrintBuffer(uint32_t leds){  
  Serial.print("[FRAMEDUMP] ");
  for(uint32_t pos = 0; pos < leds; pos++){
    auto color = _leds->getPixel(pos);
    PrintAsRGB(pos, color);
  }
    Serial.println();
}

void Controller::PrintAsRGB(int pos, int color){
    int red = (color>>16) &0x0ff;
    int green = (color>>8) &0x0ff;
    int blue = (color)    &0x0ff;
    Serial.print(pos, DEC);
    Serial.print(",");
    Serial.print(red, DEC);
    Serial.print(",");
    Serial.print(green, DEC);
    Serial.print(",");
    Serial.print(blue, DEC);
    Serial.print("|");
}
