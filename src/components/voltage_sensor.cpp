#include "components/voltage_sensor.h"

namespace PoolController {
using namespace Components;

void VoltageSensor::setup() { ads.begin(); }

float VoltageSensor::measure_volts(int channel) {
  uint16_t raw = ads.readADC_SingleEnded(channel);
  return (0.000184707 * raw) + 0.01489;
}
}  // namespace PoolController