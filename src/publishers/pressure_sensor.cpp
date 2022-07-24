#include "publishers/pressure_sensor.h"

#include <ArduinoLog.h>

#include <cmath>

#include "config/config.h"
#include "config/topics.h"
#include "connections.h"
#include "globals.h"

namespace {
float round_to(float x, int decimals) {
  const double exp = pow(10, decimals);
  return round(exp * x) / exp;
}
}  // namespace

using namespace PoolController;
using namespace PoolController::Components;

const std::string PressureSensor::publish() {
  const std::string pressure = std::to_string(round_to(
      smooth(volt_sensor.measure_volts(Globals::config.pressure_channel)), 2));

  Log.notice(F("Pressure: %s" CR), pressure.c_str());

  return get_json("pressure", pressure);
}

std::string const& PressureSensor::get_topic() {
  return Globals::config.topics.pump_pressure;
}

float PressureSensor::smooth(float input) {
  if (measurements.size() >= 10) {
    measurements.pop_front();
  }
  measurements.push_back(input);
  float sum = 0;
  for (auto i : measurements) {
    sum += i;
  }
  return sum / measurements.size();
}