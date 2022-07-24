#include "connections.h"
//#include <Arduino.h>

using namespace ConnectionUtils;

void ConnectionsManager::setup() {
  setupWifi();
  setupOTA();

  // Setup MQTT
  mqtt.setServer(config.mqtt_server, config.mqtt_port);
  connectMQTT();
  addSubscriptions();
  mqtt.setCallback([this](char *topic, uint8_t *payload, unsigned int length) {
    this->callback(topic, payload, length);
  });
}

void ConnectionsManager::setup(IPAddress ip, IPAddress gateway) {
  this->ip = ip;
  this->gateway = gateway;
  this->subnet = IPAddress(255, 255, 255, 0);
  setup();
}

void ConnectionsManager::loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setupWifi();
  }
  ArduinoOTA.handle();

  if (!mqtt.connected()) {
    connectMQTT();
    addSubscriptions();
  }
  if (mqtt.connected()) {
    mqtt.loop();
  }
}

void ConnectionsManager::setupWifi() {
  // WiFi.config(ip, gateway, subnet);
  logger.notice("Connecting to %s" CR, config.ssid);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(config.hostname);
  WiFi.begin(config.ssid, config.password);

  std::string progressBar;
  while (WiFi.status() != WL_CONNECTED) {
    progressBar.append(".");
    delay(500);
    logger.notice("%s\r", progressBar.c_str());
  }

  logger.notice(CR);
  logger.notice(F("WiFi connected" CR));
  logger.notice("IP address: %p", WiFi.localIP());
}

void ConnectionsManager::setupOTA() {
  // ArduinoOTA.onStart([this]() { Logger.notice("Start"); });
  // ArduinoOTA.onEnd([this]() { logger.notice("\nEnd"); });
  ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
    logger.notice(F("Progress: %u%%\r"), (progress / (total / 100)));
  });

  ArduinoOTA.onError([this](ota_error_t error) {
    logger.error(F(CR "Error[%u]: "), error);
    if (error == OTA_AUTH_ERROR)
      logger.error(F("Auth Failed" CR));
    else if (error == OTA_BEGIN_ERROR)
      logger.error(F("Begin Failed" CR));
    else if (error == OTA_CONNECT_ERROR)
      logger.error(F("Connect Failed" CR));
    else if (error == OTA_RECEIVE_ERROR)
      logger.error(F("Receive Failed" CR));
    else if (error == OTA_END_ERROR)
      logger.error(F("End Failed" CR));
  });

  ArduinoOTA.setHostname(config.hostname);
  ArduinoOTA.begin();
  logger.notice(F("OTA up and running!" CR));
}

void ConnectionsManager::connectMQTT() {
  int retries = 0;
  const std::string status = "devices/status/" + std::string(config.hostname);
  while (!mqtt.connected()) {
    if (retries < 5) {
      logger.notice(F("Attempting MQTT connection..." CR));
      if (mqtt.connect(config.hostname, config.mqtt_user,
                       config.mqtt_pass, status.c_str(), 0, true,
                       "offline")) {
        logger.notice(F("connected" CR));
        mqtt.publish(status.c_str(), "online", true);
      } else {
        logger.notice(F("failed (rc=%d) try again in 5 seconds" CR),
                      mqtt.state());
        retries++;
        delay(5000);
      }
    } else {
      return;
    }
  }
}

void ConnectionsManager::addSubscriptions() {
  if (!mqtt.connected()) {
    return;
  }
  for (auto &[sub, _] : subscriptions) {
    const std::string topic = std::string(config.hostname) + "/" + sub;
    mqtt.subscribe(topic.c_str());
    logger.notice(F("Subscribed to %s" CR), topic.c_str());
  }
}

void ConnectionsManager::publish(std::string const &topic,
                                 std::string const &payload) {
  if (!mqtt.connected()) {
    return;
  }
  std::string fTopic = std::string(config.hostname) + "/" + topic;
  mqtt.publish(fTopic.c_str(), payload.c_str());
  logger.notice(F("Published [%s]: %s" CR), fTopic.c_str(), payload.c_str());
}

void ConnectionsManager::callback(char *topic, uint8_t *payload,
                                  unsigned int length) {
  topic += strlen(config.hostname) + 1;
  payload[length] = '\0';
  logger.notice(F("Message arrived [%s]: %s" CR), topic, payload);
  subscriptions.at(topic)((char *)payload);
};
