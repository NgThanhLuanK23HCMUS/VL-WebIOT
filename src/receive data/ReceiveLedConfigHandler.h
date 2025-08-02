#ifndef RECEIVE_LED_CONFIG_HANDLER_H
#define RECEIVE_LED_CONFIG_HANDLER_H

#include "ReceiveHandler.h"
#include "../Config/globalSensorConfig.h"
#include <WebServer.h>

class ReceiveLedConfigHandler : public ReceiveHandler {
private:
    TrafficLight* trafficLight;

public:
    ReceiveLedConfigHandler(TrafficLight* light) : trafficLight(light) {}

    void handle(WebServer* server) override;
};

#endif
