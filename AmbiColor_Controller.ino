#include "settings.h"
#include "configuration.h"
#include "controller.h"

Settings _settings;
Controller _controller;

uint8_t* _buffer;

void setup() {
  Serial.begin(460800);  
  ClearSerialBuffer();
  _buffer = new uint8_t[_settings.GetTotalBufferSize()];
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  delay(2000);    
  Serial.println("AMBICOLOR CONTROLLER");
  SendInfo();
}

void loop() {
  CheckSerialConnected();
  if(_settings.GetTotalBufferSize() <= Serial.available())
  {    
    CaptureBuffer();
    #ifdef DEBUG_INPUT
      Serial.print("Command byte:");
      Serial.println(char(_buffer[0]));
    #endif
        
    switch(char(_buffer[0]))
    {
      case 'I':
        SendInfo();
        break;
      case 'C':
        Config();
        break;
      case 'F':
        _controller.ShowBuffer(_buffer, _settings.GetTotalBufferSize());
        break;
      default:
        #ifdef DEBUG_INPUT
          Serial.println("Command not accepted");
        #endif
        break;
    }
  }  
}

void CheckSerialConnected(){
    digitalWrite(LED_BUILTIN, Serial.dtr());
    if(!Serial.dtr()){
      _settings.SetConfigured(false);
      ClearSerialBuffer();      
    }
}

void ClearSerialBuffer(){
  //Clear buffer  
  while(Serial.available() != 0)
    Serial.read();
}

void CaptureBuffer(){
  bool state = false;
  
  #ifdef DEBUG_INPUT
    Serial.print("CaptureBuffer:");
    Serial.println(Serial.available());
  #endif
  
  for (int pos = 0; pos < _settings.GetTotalBufferSize(); pos++) {
    _buffer[pos] = Serial.read();
    digitalWrite(LED_BUILTIN, state = !state);
    
    #ifdef DEBUG_INPUT
      Serial.print(_buffer[pos]);
    #endif
  }
  
  #ifdef DEBUG_INPUT
      Serial.println();
  #endif
}

void SendInfo(){
  Serial.print("V:");
  Serial.println(VERSION);
}

void Config()
{
  int horizontal = _buffer[1] + _buffer[2] + _buffer[3] + _buffer[4];
  int vertical = _buffer[5] + _buffer[6] + _buffer[7] + _buffer[8];

  char order[4] = {_buffer[9], _buffer[10], _buffer[11], _buffer[12]};
  int numOfStrips = _buffer[13];
  
  _settings.SetHorizontalCount(horizontal);
  _settings.SetVerticalCount(vertical);
  
  if(_controller.InitLeds(vertical, horizontal, numOfStrips, order))
    _settings.SetConfigured(true);
  _buffer = new uint8_t[_settings.GetTotalBufferSize()]; 
}
