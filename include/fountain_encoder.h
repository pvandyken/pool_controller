#ifndef C_FOUNTAIN_ENCODER
#define C_FOUNTAIN_ENCODER
#include "base_encoder.h"

// Fountain encoding:
//  0     0     0     1     1     1     0     1
//  _     _     _     _ _   _ _   _ _   _     _ _
// | |_ _| |_ _| |_ _|   |_|   |_|   |_| |_ _|   |_
//

class FountainEncoderType : public BaseEncoder
{
public:
    FountainEncoderType()
        : BaseEncoder{3501, 10} {};
    void encode(int *sequence, uint16 data);

private:
    uint16 preamble = 1328;
    int timings[2][2]{
        {160, 291}, // 0 target {110, 352}
        {400, 83}   // 1 target {365, 128}
    };
    int convert(uint16 data, int *sequence, int index, int length);
};

extern FountainEncoderType FountainEncoder;

#endif