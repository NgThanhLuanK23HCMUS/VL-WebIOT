#ifndef RECEIVE_PUMP_CONFIG_HANDLER_H
#define RECEIVE_PUMP_CONFIG_HANDLER_H



#include "ReceiveHandler.h"
#include "../Config/globalSensorConfig.h"
#include <WebServer.h>

class ReceivePumpConfigHandler : public ReceiveHandler {
private:
    Relay* relay;

public:
    ReceivePumpConfigHandler(Relay* relay) : relay(relay) {}

    void handle(WebServer* server) override;
};


#endif