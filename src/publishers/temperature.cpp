#include "publishers/temperature.h"

#include <ArduinoLog.h>

#include <functional>
#include <string>

namespace PoolController {
using namespace Components;

const std::string Temperature::publish() {
  const std::string temp = std::to_string(tempLookup(channel));
  Log.notice(F("%s Temperature: %s" CR), name.c_str(), temp.c_str());
  return get_json("temperature", temp);
}

std::string const& Temperature::get_topic() { return topic; }

int Temperature::tempLookup(int channel) {
  float voltage = volt_sensor.measure_volts(channel);

  // Mulitply by 100 to match against the lookup table
  voltage *= 100;
  int voltageInt = static_cast<int>(voltage);
  for (int i = 0; i < 160; i++) {
    if (data[i] < voltageInt) {
      return i;
    }
  }
  return 0;
}

}  // namespace PoolController