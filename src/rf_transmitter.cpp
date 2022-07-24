#include "rf_transmitter.h"

#include <ArduinoLog.h>

#include "globals.h"

namespace G = PoolController::Globals;
void RfTransmitterType::setup() {
  pinMode(G::config.tx315, OUTPUT);
  pinMode(G::config.tx433, OUTPUT);
}

void RfTransmitterType::transmit315(BaseEncoder &encoder, const uint16 *data,
                                    int length) {
  Log.trace(F("The first datum is %u" CR), data[0]);
  sendBytes(encoder, data, length, G::config.tx315);
}

void RfTransmitterType::transmit433(BaseEncoder &encoder, const uint16 *data,
                                    int length) {
  sendBytes(encoder, data, length, G::config.tx433);
}

void RfTransmitterType::sendBytes(BaseEncoder &encoder, const uint16 *data,
                                  const int length, int pin) {
  Log.trace(F("Ready to send bytes %i times!" CR), encoder.times);
  for (int n = 0; n < length; n++) {
    encoder.encode(compiled[n], data[n]);
  }
  int times = encoder.times;
  while (times) {
    for (int n = 0; n < length; n++) {
      sendByte(compiled[n], pin);
    }
    digitalWrite(pin, LOW);
    times--;
    if (times) {
      delayMicroseconds(encoder.gap);
    }
  }
}

void RfTransmitterType::sendByte(int *sequence, int pin) {
  int length = sequence[0];
  int pinMode = sequence[1];
  // Serial.println();
  // Serial.println(length);
  // Serial.println(pinMode);

  for (int i = 2; i < length; i++) {
    // Serial.print(sequence[i]);
    // Serial.print(", ");
    digitalWrite(pin, pinMode);
    delayMicroseconds(sequence[i]);
    pinMode ^= 1;
  }
}

RfTransmitterType RfTransmitter;