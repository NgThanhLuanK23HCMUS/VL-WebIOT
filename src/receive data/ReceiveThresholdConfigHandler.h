#ifndef RECEIVE_THRESHOLD_CONFIG_HANDLER_H
#define RECEIVE_THRESHOLD_CONFIG_HANDLER_H

#include <WebServer.h>
#include "../Config/globalSensorConfig.h"
class ReceiveThresholdConfigHandler {
private:
    Sensor* sensor;
public:
    ReceiveThresholdConfigHandler(Sensor* sensor) : sensor(sensor) {}
    void handle(WebServer* server);
};

#endif