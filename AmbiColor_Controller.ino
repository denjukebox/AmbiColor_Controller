#include "settings.h"
#include "configuration.h"
#include "controller.h"

Settings _settings;
Controller _controller;

char _buffer[INITIAL_SERIAL_RX_SIZE];

void setup() {  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  delay(3000);    
  Serial.println("AMBICOLOR CONTROLLER");
  SendInfo();
}

void loop() {
  CheckSerialConnected();
  
  int startChar = 0;
  
  if(Serial.available()){
    startChar = Serial.read();
  }
  
  if(startChar == '*' && Serial.available()){
    startChar = 0;
    int commandChar = Serial.read();
    startChar = Serial.read();
    
    if(startChar == '*' && Serial.available())
    {
      #ifdef DEBUG_INPUT
        Serial.print("CB:");
        Serial.print(char(commandChar));
        Serial.print(" S:");
        Serial.println(Serial.available(), DEC);
      #endif
    
      switch(char(commandChar))
      {
        case 'I':
          SendInfo();
          break;
        case 'C':
          Config();
          break;
        case 'F':
          _controller.ShowBuffer(_settings.GetTotalLeds(), _settings.GetLedStripCount());
          break;
        case 'D':
              _controller.PrintBuffer(_settings.GetTotalLeds());
          break;
        default:
          break;
      }
    }
  }    
}

void CheckSerialConnected(){
    if(!Serial.dtr()){
      digitalWrite(LED_BUILTIN, LOW);
      _settings.SetConfigured(false);
    }
}

void SendInfo(){
  Serial.print("V:");
  Serial.println(VERSION);
}

void Config()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.readBytes(_buffer, INITIAL_SERIAL_RX_SIZE);
  
  int horizontal = _buffer[0] + _buffer[1] + _buffer[2] + _buffer[3];
  int vertical = _buffer[4] + _buffer[5] + _buffer[6] + _buffer[7];

  char ledConfig = _buffer[8];
  int numOfStrips = _buffer[12];
  
  _settings.SetLedStripCount(numOfStrips);
  _settings.SetLedConfiguration(ledConfig);
  _settings.SetHorizontalCount(horizontal);
  _settings.SetVerticalCount(vertical);
  
  if(_controller.InitLeds(_settings.GetLedsPerStrip(), numOfStrips, ledConfig))
    _settings.SetConfigured(true);
  
  #ifdef DEBUG_SETTINGS
        Serial.print("[SETTINGS] ");
        Serial.print("Vertical:");
        Serial.print(vertical);
        Serial.print(" Horizontal:");
        Serial.print(horizontal);
        Serial.print(" NumerOfStrips:");
        Serial.print(numOfStrips);
        Serial.print(" Buffersize:");
        Serial.print(_settings.GetTotalBufferSize());
        Serial.print(" LedOrder:");
        switch(ledConfig){
          case 0: Serial.print("RGB"); break;
          case 1: Serial.print("RBG"); break;
          case 2: Serial.print("GRB"); break;
          case 3: Serial.print("GBR"); break;
          case 4: Serial.print("BRG"); break;
          case 5: Serial.print("BGR"); break;
        }
        Serial.print(" Configured:");
        Serial.println(_settings.GetConfigured());
  #endif
}
