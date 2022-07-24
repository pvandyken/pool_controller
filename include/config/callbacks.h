#ifndef N_CALLBACKS
#define N_CALLBACKS

#include <ArduinoLog.h>
#include <connections.h>

#include <string>

#include "components/switches.h"
#include "fire_encoder.h"
#include "fountain_encoder.h"
#include "globals.h"
#include "rf_transmitter.h"

namespace PoolController {
namespace G = Globals;

struct Callbacks {
  ConnectionUtils::Subscriptions subscriptions{
      {"fireplace/basement",
       [](std::string payload) {
         if (payload == "on") {
           Log.notice(F("Turning on Basement Fire" CR));
           RfTransmitter.transmit315(FireEncoder, G::config.basement_on_silent,
                                     7);
         } else if (payload == "off") {
           Log.notice(F("Turning OFF Basement Fire" CR));
           RfTransmitter.transmit315(FireEncoder, G::config.basement_off_silent,
                                     7);
         }
       }},

      {"fireplace/family",
       [](std::string payload) {
         if (payload == "on") {
           Log.notice(F("Turning ON Family Fire" CR));
           RfTransmitter.transmit315(FireEncoder, G::config.family_on_silent,
                                     7);
         } else if (payload == "off") {
           Log.notice(F("Turning OFF Family Fire" CR));
           RfTransmitter.transmit315(FireEncoder, G::config.family_off_silent,
                                     7);
         }
       }},
      {"fountain/light",
       [](std::string payload) {
         if (payload == "power") {
           Serial.println(F("Toggling Power on the Fountain Lights"));
           RfTransmitter.transmit433(FountainEncoder, &G::config.power, 1);
         } else if (payload == "red") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.red, 1);
         } else if (payload == "green") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.green, 1);
         } else if (payload == "blue") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.blue, 1);
         } else if (payload == "white") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.white, 1);
         } else if (payload == "orange") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.orange, 1);
         } else if (payload == "yellow") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.yellow, 1);
         } else if (payload == "cyan") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.cyan, 1);
         } else if (payload == "purple") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.purple, 1);
         } else if (payload == "autoChange") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.auto_change,
                                     1);
         } else if (payload == "jump3") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.jump3, 1);
         } else if (payload == "jump7") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.jump7, 1);
         } else if (payload == "fade3") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.fade7, 1);
         } else if (payload == "flash") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.flash, 1);
         } else if (payload == "speedUp") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.speed_up, 1);
         } else if (payload == "speedDown") {
           RfTransmitter.transmit433(FountainEncoder, &G::config.speed_down, 1);
         }
       }},
      {"fountain/state",
       [](std::string payload) {
         if (payload == "on") {
           Log.notice(F("Turning the fountain ON" CR));
           Switches.fountainOn();
         } else if (payload == "off") {
           Log.notice(F("Turning the fountain OFF" CR));
           Switches.fountainOff();
         }
       }},
      {"pool/light",
       [](std::string payload) {
         if (payload == "on") {
           Log.notice(F("Turning the pool light ON" CR));
           Switches.poolLightOn();
         } else if (payload == "off") {
           Log.notice(F("Turning the pool light OFF" CR));
           Switches.poolLightOff();
         }
       }},
      {"pool/pump", [](std::string payload) {
         if (payload == "on") {
           Log.notice(F("Turning the pool pump ON" CR));
           Switches.pumpOn();
         } else if (payload == "off") {
           Log.notice(F("Turning the pool pump OFF" CR));
           Switches.pumpOff();
         }
       }}};
};
}  // namespace PoolController
#endif
