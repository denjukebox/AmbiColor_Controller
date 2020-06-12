#include "controller.h"

DMAMEM int* _displayMemory;
int* _drawingMemory;

byte LedPinList[NUM_OF_STRIPS] = {DATA_PIN_1, DATA_PIN_2};

Controller::Controller()
{
  
}

bool Controller::InitLeds(int vertical, int horizontal, int numOfStrips, char* order){ 
  //Setup buffer
  _vertical = vertical;
  _horizontal = horizontal;
  _numberOfStrips = numOfStrips;
  
  _colorsPerBuffer = (_vertical * 2) + (_horizontal * 2);  
  _ledsPerStrip = _colorsPerBuffer / _numberOfStrips;

  //Init buffers
  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  _displayMemory = new int[_colorsPerBuffer * 3 / 4];
  _drawingMemory = new int[_colorsPerBuffer * 3 / 4];
    
  _order = order;
  
  auto sidesPerStrip = MAX_OF_STRIPS / numOfStrips;  

  if(_numberOfStrips == 1){
    _bufferLength[0] = GetCount(sidesPerStrip, 0);
  }
  if(_numberOfStrips == 2){
    _bufferLength[0] = GetCount(sidesPerStrip, 0);
    _bufferLength[1] = GetCount(sidesPerStrip, 2);
  }
  if(_numberOfStrips == 4){
    _bufferLength[0] = GetCount(sidesPerStrip, 0);
    _bufferLength[1] = GetCount(sidesPerStrip, 1);
    _bufferLength[2] = GetCount(sidesPerStrip, 2);
    _bufferLength[3] = GetCount(sidesPerStrip, 3);
  }

  _leds = new OctoWS2811(_ledsPerStrip, _displayMemory, NULL, LED_TYPE, _numberOfStrips, LedPinList);
  _leds->begin();

 for (auto pos = 0; pos < _leds->numPixels(); pos++){
  _leds->setPixel(pos, 0x160000);
 }

 _leds->show();
  
  #ifdef DEBUG_CONTROLLER
        Serial.print("Vertical:");
        Serial.print(_vertical);
        Serial.print(" Horizontal:");
        Serial.print(_horizontal);
        Serial.print(" NumerOfStrips:");
        Serial.print(_numberOfStrips);
        Serial.print(" ColorsPerBuffer:");
        Serial.print(_colorsPerBuffer);
        Serial.print(" LedsPerStrip:");
        Serial.println(_ledsPerStrip);
  #endif
  return true;
}

bool Controller::ShowBuffer(uint8_t* buffer, int size){
  #ifdef DEBUG_BUFFER
      Serial.print("AddToBuffer:");
  #endif
  memcpy(_displayMemory, buffer, size);
  _leds->show();
}

int Controller::GetCount(int length, int offset){      
  #ifdef DEBUG_CONTROLLER
    Serial.print("GetCount:");
  #endif
  int totalCount = 0;
  for (int charPos = offset; charPos < offset + length; charPos++) {
      #ifdef DEBUG_CONTROLLER
        Serial.print(_order[charPos]);
        Serial.print(":");
      #endif
      switch ((char)_order[charPos]) {
        case 'T':
          totalCount += _horizontal;
          break;
        case 'B':
          totalCount += _horizontal;
          break;
        case 'L':
          totalCount += _vertical;
          break;
        case 'R':
          totalCount += _vertical;
          break;
        case 'H':
          totalCount += _horizontal;
          break;
        case 'V':
          totalCount += _vertical;
          break;
      }
  }

  #ifdef DEBUG_CONTROLLER
    Serial.println(totalCount);
  #endif
  return totalCount;
}
