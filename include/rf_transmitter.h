#ifndef C_RF_TRANSMITTER
#define C_RF_TRANSMITTER
#include <Arduino.h>
#include "base_encoder.h"
#include "config/config.h"

class RfTransmitterType
{
public:
    void setup();
    void transmit315(BaseEncoder &encoder, const uint16 *data, int length);
    void transmit433(BaseEncoder &encoder, const uint16 *data, int length);

private:
    int pin433;
    int pin315;
    void sendBytes(BaseEncoder &encoder, const uint16 *data, int length, int pin);
    void sendByte(int *sequence, int pin);
    int compiled[10][100];
};

extern RfTransmitterType RfTransmitter;

#endif