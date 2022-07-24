#ifndef C_SWITCHES
#define C_SWITCHES
#include <Arduino.h>
#include "../config/config.h"

struct SwitchesClass
{
    void setup();
    void pumpOn();
    void pumpOff();
    void fountainOn();
    void fountainOff();
    void poolLightOn();
    void poolLightOff();
};

extern SwitchesClass Switches;
#endif