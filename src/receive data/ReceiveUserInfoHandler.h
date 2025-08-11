

#ifndef RECEIVE_DEVICE_INFO_HANDLER_H
#define RECEIVE_DEVICE_INFO_HANDLER_H

#include "./ReceiveHandler.h"
#include <Arduino.h>
#include <WebServer.h>
#include "../Config/globalSensorConfig.h"

class ReceiveUserInfoHandler : public ReceiveHandler {
private:
    Device* device;
public:
    ReceiveUserInfoHandler(Device* device) : device(device) {} 

    void handle(WebServer* server) override ;

};

#endif