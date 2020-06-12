#include "settings.h"

Settings::Settings(){
  
}

int Settings::GetVerticalCount(){
  return _vertical;
}

int Settings::GetHorizontalCount(){
  return _horizontal;
}

int Settings::GetTotalCount(){
  return (_vertical * 2) + (_horizontal * 2);
}

int Settings::GetTotalBufferSize(){
  return _configured ? GetTotalCount() * 3 : INITIAL_SERIAL_RX_SIZE;
}

void Settings::SetConfigured(bool configured){
  _configured = configured;
}

void Settings::SetVerticalCount(int count){
  _vertical= count;
}

void Settings::SetHorizontalCount(int count){
  _horizontal = count;
}
