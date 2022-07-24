#include "components/switches.h"

#include "globals.h"

namespace G = PoolController::Globals;
void SwitchesClass::setup()
{
    pinMode(G::config.pump, OUTPUT);
    digitalWrite(G::config.pump, LOW);
    pinMode(G::config.fountain, OUTPUT);
    digitalWrite(G::config.fountain, HIGH);
    pinMode(G::config.pool_light, OUTPUT);
    digitalWrite(G::config.pool_light, HIGH);
}

void SwitchesClass::fountainOff()
{
    // Note that the relay is in reverse:
    //      LOW  -> ON
    //      HIGH -> OFF
    digitalWrite(G::config.fountain, HIGH);
}

void SwitchesClass::fountainOn()
{
    digitalWrite(G::config.fountain, LOW);
}

void SwitchesClass::pumpOff()
{
    digitalWrite(G::config.pump, LOW);
}

void SwitchesClass::pumpOn()
{
    digitalWrite(G::config.pump, HIGH);
}

void SwitchesClass::poolLightOff()
{
    // Not operated by the relay, so LOW and HIGH
    // work as expected.
    digitalWrite(G::config.pool_light, HIGH);
}

void SwitchesClass::poolLightOn()
{
    digitalWrite(G::config.pool_light, LOW);
}

SwitchesClass Switches = SwitchesClass();