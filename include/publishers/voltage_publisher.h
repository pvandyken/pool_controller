#ifndef C_VOLTAGE_PUBLISHER
#define C_VOLTAGE_PUBLISHER
#include <connections.h>

#include "components/voltage_sensor.h"
#include "publishers/publisher.h"

namespace PoolController {
namespace Components {
class VoltagePublisher : public Publisher {
 public:
  VoltagePublisher(VoltageSensor &voltage, Scheduler &scheduler,
                   ConnectionUtils::ConnectionsManager &connections)
      : Publisher(scheduler, connections), volt_sensor(voltage) {}

 protected:
  VoltageSensor &volt_sensor;
};
}  // namespace Components
}  // namespace PoolController

#endif