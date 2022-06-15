#ifndef Settings_h
#define Settings_h

#include "configuration.h"

class Settings
{

  public:
    Settings();

    int GetLedStripCount();
    int GetVerticalCount();
    int GetHorizontalCount();

    void SetLedStripCount(int count);
    void SetVerticalCount(int count);
    void SetHorizontalCount(int count);
    void SetLedConfiguration(char ledConfig);

    void SetConfigured(bool configured);
    bool GetConfigured();

    int GetLedsPerStrip();    
    int GetTotalBufferSize();
    int GetTotalLeds();
    char GetLedConfiguration();

  private:
    int _vertical;
    int _horizontal;
    int _numOfStrips;
    char _ledConfiguration;

    bool _configured;
};

#endif
