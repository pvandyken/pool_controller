#ifndef C_VOLTAGE_SENSOR
#define C_VOLTAGE_SENSOR

#include <Adafruit_ADS1X15.h>

namespace PoolController {
namespace Components {
class VoltageSensor {
 public:
  VoltageSensor() : ads(Adafruit_ADS1115()){};
  void setup();
  float measure_volts(int channel);

 private:
  Adafruit_ADS1115 ads;
};
}  // namespace Components
}  // namespace PoolController

#endif