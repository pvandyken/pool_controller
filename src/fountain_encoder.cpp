#include "fountain_encoder.h"

void FountainEncoderType::encode(int *sequence, uint16 data)
{
    int length;
    sequence[1] = 1;
    length = convert(preamble, sequence, 2, 12);
    length = convert(data, sequence, length, 13);
    sequence[0] = length;
}

int FountainEncoderType::convert(uint16 data, int *sequence, int index, int length)
{
    data = reverse(data) >> (16 - length);
    int sLength = index;
    for (int n = 0; n < length; n++)
    {
        int *t = timings[data & 1];
        sequence[sLength] = t[0];
        sLength++;
        sequence[sLength] = t[1];
        sLength++;
        data = data >> 1;
    }
    return sLength;
}

FountainEncoderType FountainEncoder;
