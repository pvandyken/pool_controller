#ifndef N_CONFIG_IMPLEMENT
#define N_CONFIG_IMPLEMENT
#include <Arduino.h>
#include <connections.h>

#include "config.local.h"
#include "config/topics.h"

namespace PoolController {
struct Config {
  ConnectionUtils::Config connections = {
      CONFIG_SSID,
      CONFIG_PASSWORD,
      CONFIG_MQTT_SERVER,
      CONFIG_MQTT_PORT,
      CONFIG_MQTT_USER,
      CONFIG_MQTT_PASS,
      CONFIG_HOSTNAME,
  };

  // Pinouts
  const int tx315 = CONFIG_TX315;
  const int tx433 = CONFIG_TX433;

  const int pump = CONFIG_PUMP;
  const int fountain = CONFIG_FOUNTAIN;
  const int pool_light = CONFIG_POOL_LIGHT;

  // Analogue Read Channels
  const int pool_channel = CONFIG_POOL_CHANNEL;
  const int air_channel = CONFIG_AIR_CHANNEL;
  const int pressure_channel = CONFIG_PRESSURE_CHANNEL;

  // Fireplace Codes
  const uint16 basement_on_beep[7] = {511, 2011, 19, 11, 49, 403, 659};
  const uint16 basement_on_silent[7] = {511, 2011, 19, 19, 49, 651, 659};
  const uint16 basement_off_beep[7] = {511, 2011, 19, 1, 49, 155, 659};
  const uint16 basement_off_silent[7] = {511, 2011, 19, 19, 1, 651, 1187};

  const uint16 family_on_beep[7] = {301, 1187, 19, 11, 49, 1787, 1547};
  const uint16 family_on_silent[7] = {301, 1187, 19, 19, 49, 1507, 1547};
  const uint16 family_off_beep[7] = {301, 1187, 19, 1, 49, 2035, 1547};
  const uint16 family_off_silent[7] = {301, 1187, 19, 19, 1, 1507, 59};

  // Fountain Codes
  const uint16 power = 384;
  const uint16 red = 30;
  const uint16 green = 102;
  const uint16 blue = 390;
  const uint16 white = 120;
  const uint16 orange = 408;
  const uint16 yellow = 480;
  const uint16 cyan = 1542;
  const uint16 purple = 6150;
  const uint16 auto_change = 1560;
  const uint16 jump3 = 6168;
  const uint16 jump7 = 1920;
  const uint16 fade3 = 6246;
  const uint16 fade7 = 1536;
  const uint16 flash = 6528;
  const uint16 speed_up = 1632;
  const uint16 speed_down = 6144;

  const Topics topics = Topics();
};
}  // namespace PoolController

#endif