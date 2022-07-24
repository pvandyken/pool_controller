#ifndef C_PRESSURE_SENSOR
#define C_PRESSURE_SENSOR

#include <deque>
#include <functional>
#include <string>

#include "components/voltage_sensor.h"
#include "publishers/voltage_publisher.h"

namespace PoolController {
namespace Components {
class PressureSensor : public VoltagePublisher {
 public:
  PressureSensor(VoltageSensor &voltage, Scheduler &scheduler,
                 ConnectionUtils::ConnectionsManager &connections)
      : VoltagePublisher(voltage, scheduler, connections), measurements() {}
  const std::string publish();
  std::string const& get_topic();

 private:
  std::deque<float> measurements;

  float smooth(float input);
};
}  // namespace Components
}  // namespace PoolController

#endif