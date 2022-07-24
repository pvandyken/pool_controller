#include "base_encoder.h"
#include "ArduinoLog.h"

void encode(int *sequence, uint16 data)
{
    Log.errorln(F("BaseEncoder.encode should not be called!"));
};

uint16 BaseEncoder::reverse(uint16 b)
{
    b = (b & 0xFF00) >> 8 | (b & 0x00FF) << 8;
    b = (b & 0xF0F0) >> 4 | (b & 0x0F0F) << 4;
    b = (b & 0xCCCC) >> 2 | (b & 0x3333) << 2;
    b = (b & 0xAAAA) >> 1 | (b & 0x5555) << 1;
    return b;
}