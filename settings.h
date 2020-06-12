#ifndef Settings_h
#define Settings_h

#include "configuration.h"

class Settings
{

  public:
    Settings();

    int GetVerticalCount();
    int GetHorizontalCount();

    void SetVerticalCount(int count);
    void SetHorizontalCount(int count);

    void SetConfigured(bool configured);

    int GetTotalCount();    
    int GetTotalBufferSize();

  private:
    int _vertical;
    int _horizontal;

    bool _configured;
};

#endif
