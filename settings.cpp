#include "settings.h"

Settings::Settings(){
  
}

int Settings::GetLedStripCount(){
  return _numOfStrips;
}

int Settings::GetVerticalCount(){
  return _vertical;
}

int Settings::GetHorizontalCount(){
  return _horizontal;
}

int Settings::GetLedsPerStrip(){
  return _vertical + _horizontal;
}

int Settings::GetTotalLeds(){
  return _configured ? GetLedsPerStrip() * _numOfStrips : 0;
}

int Settings::GetTotalBufferSize(){
  return _configured ? (GetLedsPerStrip() * _numOfStrips) * 3 : INITIAL_SERIAL_RX_SIZE;
}

char Settings::GetLedConfiguration(){
  return _ledConfiguration;
}

void Settings::SetConfigured(bool configured){
  _configured = configured;
}

bool Settings::GetConfigured(){
  return _configured;
}

void Settings::SetLedStripCount(int count){
  _numOfStrips = count;
}

void Settings::SetVerticalCount(int count){
  _vertical = count;
}

void Settings::SetHorizontalCount(int count){
  _horizontal = count;
}

void Settings::SetLedConfiguration(char ledConfig){
  _ledConfiguration = ledConfig;
}
