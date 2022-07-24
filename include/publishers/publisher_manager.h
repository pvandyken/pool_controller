#ifndef C_COMPONENT_MANAGER
#define C_COMPONENT_MANAGER

#include <connections.h>

#include "components/voltage_sensor.h"
#include "globals.h"
#include "publishers/pressure_sensor.h"
#include "publishers/temperature.h"
#include "scheduler/scheduler.h"

namespace PoolController {
namespace Components {
class ComponentManager {
 public:
  ComponentManager(Scheduler &scheduler,
                   ConnectionUtils::ConnectionsManager &connections)
      : voltage(VoltageSensor()),
        scheduler(scheduler),
        poolTemp("Pool", Globals::config.topics.pool_temp,
                 Globals::config.pool_channel, voltage, scheduler, connections),
        airTemp("Air", Globals::config.topics.air_temp,
                Globals::config.air_channel, voltage, scheduler, connections),
        pres(voltage, scheduler, connections){};
  void setup();
 private:
  VoltageSensor voltage;
  Scheduler &scheduler;
  Temperature poolTemp;
  Temperature airTemp;
  PressureSensor pres;
};
}  // namespace Components
}  // namespace PoolController

#endif