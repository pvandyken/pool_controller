#ifndef C_BASE_ENCODER
#define C_BASE_ENCODER
#include <Arduino.h>

class BaseEncoder
{
public:
    BaseEncoder(int gap, int times)
        : gap{gap}, times{times} {};
    virtual void encode(int *sequence, uint16 data);
    const int gap;
    const int times;

protected:
    uint16 reverse(uint16);
};
#endif