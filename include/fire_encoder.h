#pragma once
#include <Arduino.h>
#include "base_encoder.h"

// Fireplace encoding:
//  init  0   0   0   1   1   1   0   1   1   0
//  _ _ _     _   _   _ _   _   _     _ _   _
// |     |_ _| |_| |_|   |_| |_| |_ _|   |_| |_ _
//
// To encode the above, a binary number 0001110110
// is reversed to 0110111000. The init bit is appended
// as a 1: 01101110001. For each bit, the right-most two
// bits are processed, where the right-most bit represents
// the previously sent bit, and the second bit represents
// the current bit. From these two, the correct up/down
// sequence can be determined.

class FireEncoderType : public BaseEncoder
{
public:
    FireEncoderType()
        : BaseEncoder{4750, 5} {};
    void encode(int *sequence, uint16 data);

private:
    int intialByte[2]{
        500,
        1235};
    int timings[4][2]{
        {450, 370}, //upDown
        {780, 0},   //downDown
        {855, 0},   //upUp
        {370, 450}  //downUp
    };
};

extern FireEncoderType FireEncoder;