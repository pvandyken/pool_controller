#ifndef C_CONNECTIONS
#define C_CONNECTIONS

#include <ArduinoLog.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>

#include <functional>
#include <string>
#include <unordered_map>

#include "config.h"

namespace ConnectionUtils {

typedef std::unordered_map<std::string, std::function<void(std::string)>>
    Subscriptions;

class ConnectionsManager {
 public:
  ConnectionsManager(Config &config, Subscriptions &subscriptions, Logging &logger)
      : config(config), subscriptions(subscriptions), logger(logger){};
  void setup();
  void setup(IPAddress ip, IPAddress gateway);
  void loop();
  void publish(std::string const& topic,
               std::string const& payload);
  void addSubscriptions();
  void callback(char* topic, uint8_t* payload, unsigned int length);

 private:
  Config &config;
  Subscriptions const& subscriptions;
  Logging &logger;
  WiFiClient wClient = WiFiClient();
  PubSubClient mqtt = PubSubClient(wClient);

  // These values will be updated if the user provides a specifc
  // ip and gateway. Otherwise, they will remain 0, and DHCP will
  // supply them for us
  IPAddress ip = IPAddress(0, 0, 0, 0);
  IPAddress gateway = IPAddress(0, 0, 0, 0);
  IPAddress subnet = IPAddress(0, 0, 0, 0);

  void setupWifi();
  void setupOTA();
  void connectMQTT();
};

};  // namespace ConnectionUtils

#endif
