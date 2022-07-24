#ifndef CONUTIL_S_CONNECTION_CONFIG
#define CONUTIL_S_CONNECTION_CONFIG
#include <string>

namespace ConnectionUtils {
struct Config {
  const char* ssid;
  const char* password;
  const char* mqtt_server;
  const int mqtt_port;
  const char* mqtt_user;
  const char* mqtt_pass;
  const char* hostname;
};
}  // namespace ConnectionUtils

#endif