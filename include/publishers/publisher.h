#ifndef C_PUBLISHER
#define C_PUBLISHER
#include <functional>
#include <string>

#include <connections.h>

#include "scheduler/scheduler.h"

namespace PoolController {
namespace Components {
class Publisher {
 public:
  Publisher(Scheduler& scheduler,
            ConnectionUtils::ConnectionsManager& connections)
      : scheduler(scheduler),
        connections(connections),
        task(5000, TASK_FOREVER, [this]() {
          this->connections.publish(this->get_topic(), this->publish());
        }){};

  void setup();
  virtual const std::string publish() = 0;
  virtual std::string const& get_topic() = 0;

 protected:
  const std::string get_json(std::string const& key, std::string const& value);

 private:
  Scheduler& scheduler;
  ConnectionUtils::ConnectionsManager& connections;
  Task task;
};
}  // namespace Components
}  // namespace PoolController

#endif