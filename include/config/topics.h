#ifndef N_CONFIG_TOPICS
#define N_CONFIG_TOPICS

#include <string>

namespace PoolController {
struct Topics {
  // Pool Temperature Topics
  const std::string pool_temp = "poolTemp/pool";
  const std::string air_temp = "poolTemp/air";
  const std::string pump_pressure = "poolPressure";
};

}  // namespace PoolController
#endif