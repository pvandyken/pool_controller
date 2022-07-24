#include "fire_encoder.h"
void FireEncoderType::encode(int *sequence, uint16 data)
{
    sequence[1] = 0;
    sequence[2] = this->intialByte[0];
    sequence[3] = this->intialByte[1];

    data = (reverse(data) >> 4) | 1;
    int length = 4;
    for (int n = 0; n < 11; n++)
    {
        int *t = timings[data & 3];
        sequence[length] = t[0];
        length++;
        if (t[1])
        {
            sequence[length] = t[1];
            length++;
        }
        data = data >> 1;
    }
    sequence[0] = length;
}

FireEncoderType FireEncoder;