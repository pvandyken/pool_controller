#include "publishers/publisher_manager.h"

using namespace PoolController::Components;

void ComponentManager::setup() {
    voltage.setup();
    poolTemp.setup();
    airTemp.setup();
    pres.setup();
}