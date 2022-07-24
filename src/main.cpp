#include <ArduinoLog.h>
#include <SPI.h>
#include <Stream.h>
#include <connections.h>

#include "components/switches.h"
#include "config/callbacks.h"
#include "debug.h"
#include "globals.h"
#include "publishers/publisher_manager.h"
#include "rf_transmitter.h"
#include "scheduler/scheduler_impl.h"

#define TX 12

typedef void (*FunctionPointer)();

const int _byte = 830;
const int _up = 450;    // Trying to achieve 396 as measured by SDR
const int _down = 370;  // Trying to achieve 433 as measured by SDR
const int _upUp = 855;
const int _downDown = 780;

const uint16 basement_on_beep[7] = {511, 2011, 19, 11, 49, 403, 659};
const uint16 basement_on_silent[7] = {511, 2011, 19, 19, 49, 651, 659};
const uint16 basement_off_beep[7] = {511, 2011, 19, 1, 49, 155, 659};
const uint16 basement_off_silent[7] = {511, 2011, 19, 19, 1, 651, 1187};

const uint16 family_on_beep[7] = {301, 1187, 19, 11, 49, 1787, 1547};
const uint16 family_on_silent[7] = {301, 1187, 19, 19, 49, 1507, 1547};
const uint16 family_off_beep[7] = {301, 1187, 19, 1, 49, 2035, 1547};
const uint16 family_off_silent[7] = {301, 1187, 19, 19, 1, 1507, 59};

uint16 reverse(uint16 b) {
  b = (b & 0xFF00) >> 8 | (b & 0x00FF) << 8;
  b = (b & 0xF0F0) >> 4 | (b & 0x0F0F) << 4;
  b = (b & 0xCCCC) >> 2 | (b & 0x3333) << 2;
  b = (b & 0xAAAA) >> 1 | (b & 0x5555) << 1;
  return b;
}

void initiateByte() {
  digitalWrite(TX, LOW);
  delayMicroseconds(500);
  digitalWrite(TX, HIGH);
  delayMicroseconds(1235);
}

void downDown() {
  // Serial.println("Down_Down (10)");
  digitalWrite(TX, LOW);
  delayMicroseconds(_downDown);
}

void upUp() {
  // Serial.println("Up_Up (01)");
  digitalWrite(TX, HIGH);
  delayMicroseconds(_upUp);
}

void downUp() {
  // Serial.println("Down_Up (11)");
  digitalWrite(TX, LOW);
  delayMicroseconds(_down);
  digitalWrite(TX, HIGH);
  delayMicroseconds(_up);
}

void upDown() {
  // Serial.println("Up_Down (00)");
  digitalWrite(TX, HIGH);
  delayMicroseconds(_up);
  digitalWrite(TX, LOW);
  delayMicroseconds(_down);
}

FunctionPointer signalFunctions[4] = {upDown, downDown, upUp, downUp};

void sendByte(uint16 data) {
  // uint16 func;
  initiateByte();
  // Serial.print("New Number: ");
  // Serial.println(data);
  data = (reverse(data) >> 4) | 1;
  // Serial.print("Reversed: ");
  // Serial.println(data);
  for (int n = 0; n < 11; n++) {
    signalFunctions[data & 3]();
    data = data >> 1;
  }
}

void sendBytes(const uint16 data[], int length, int times) {
  while (times) {
    for (int n = 0; n < length; n++) {
      sendByte(data[n]);
    }
    digitalWrite(TX, LOW);
    times--;
    if (times) {
      delayMicroseconds(4750);
    }
  }
}

void setBasementFire(bool on, bool beep) {
  if (on) {
    if (beep) {
      sendBytes(basement_on_beep, 7, 5);
    } else {
      sendBytes(basement_on_silent, 7, 5);
    }
  } else {
    if (beep) {
      sendBytes(basement_off_beep, 7, 5);
    } else {
      sendBytes(basement_off_silent, 7, 5);
    }
  }
}

void setFamilyFire(bool on, bool beep) {
  if (on) {
    if (beep) {
      sendBytes(family_on_beep, 7, 5);
    } else {
      sendBytes(family_on_silent, 7, 5);
    }
  } else {
    if (beep) {
      sendBytes(family_off_beep, 7, 5);
    } else {
      sendBytes(family_off_silent, 7, 5);
    }
  }
}
PoolController::Callbacks callbacks;
Scheduler scheduler;
ConnectionUtils::ConnectionsManager connections(
    PoolController::Globals::config.connections, callbacks.subscriptions, Log);

PoolController::Components::ComponentManager comps(scheduler, connections);

void setup() {
  Serial.begin(9600);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  scheduler.init();
  connections.setup();
  RfTransmitter.setup();
  comps.setup();
  Switches.setup();
}

void loop() {
  connections.loop();
  PoolController::Globals::timer.run();
  scheduler.execute();
}
