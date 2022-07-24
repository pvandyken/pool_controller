#ifndef C_TEMPERATURE_READER
#define C_TEMPERATURE_READER
#include <connections.h>

#include <string>

#include "components/voltage_sensor.h"
#include "config/config.h"
#include "config/topics.h"
#include "debug.h"
#include "globals.h"
#include "publishers/voltage_publisher.h"

namespace PoolController {
namespace Components {
class Temperature : public VoltagePublisher {
 public:
  Temperature(std::string name, std::string const& topic,
              const int channel, VoltageSensor& voltage, Scheduler& scheduler,
              ConnectionUtils::ConnectionsManager& connections)
      : VoltagePublisher(voltage, scheduler, connections),
        name(name),
        topic(topic),
        channel(channel){};
  const std::string publish();
  std::string const& get_topic();

 private:
  std::string name;
  std::string const& topic;
  const int channel;
  int tempLookup(int channel);
  void publish_temp(int channel, const char* topic,
                    std::string const& debug_label);

  // Lookup table mapping temperatures in degrees F to voltages.
  // Temperatures are the item indices, and voltages (* 100) are the values
  const int data[160] = {
      446, 445, 443, 441, 440, 438, 436, 435, 433, 431, 429, 427, 425, 423, 421,
      419, 417, 415, 413, 411, 409, 407, 404, 402, 400, 397, 395, 393, 390, 388,
      385, 383, 380, 378, 375, 372, 370, 367, 364, 361, 359, 356, 353, 350, 347,
      345, 342, 339, 336, 333, 330, 327, 324, 321, 318, 315, 312, 309, 306, 302,
      299, 296, 293, 290, 287, 284, 281, 278, 275, 272, 268, 265, 262, 259, 256,
      253, 250, 247, 244, 241, 238, 235, 232, 229, 226, 223, 220, 217, 214, 212,
      209, 206, 203, 200, 198, 195, 192, 189, 187, 184, 181, 179, 176, 174, 171,
      169, 166, 164, 161, 159, 157, 154, 152, 150, 147, 145, 143, 141, 139, 137,
      134, 132, 130, 128, 126, 124, 122, 121, 119, 117, 115, 113, 111, 110, 108,
      106, 105, 103, 101, 100, 98,  97,  95,  93,  92,  90,  89,  88,  86,  85,
      84,  82,  81,  80,  78,  77,  76,  75,  73,  72};
};

}  // namespace Components
}  // namespace PoolController

#endif