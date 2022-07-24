#include "publishers/publisher.h"

using namespace PoolController::Components;

void Publisher::setup() {
  scheduler.addTask(task);
  task.enable();
}

const std::string Publisher::get_json(std::string const& key,
                                      std::string const& value) {
  return "{\"" + key + "\": " + value + "}";
}
