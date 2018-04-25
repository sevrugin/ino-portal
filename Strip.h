#ifndef Strip_h
#define Strip_h

#include "Arduino.h"

#define LIGHT_TIME 15000
#define ALPHA_SH 1

class Strip 
{
  private:
    int _pin[3];
    byte _color[3] = {0,0,0};
    int _pir;
    int _timeOff = NULL;
    int _alpha = 0;
    int _currentAlpha = 0;
  public:
    Strip(int r, int g, int b);
    void setColor(byte r, byte g, byte b);
    void setPir(int pir);
    bool setAlpha(int alpha);
    bool checkPir();
    void test();
    void display();

    bool loop();
};

#endif


