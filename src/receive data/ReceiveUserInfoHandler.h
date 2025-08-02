// #ifndef RECEIVE_DEVICE_INFO_H
// #define RECEIVE_DEVICE_INFO_H


// #include <Arduino.h>
// #include <WebServer.h>

// bool receiveDeviceInfo(WebServer* server, String &user_id);

// #endif 

#ifndef RECEIVE_DEVICE_INFO_HANDLER_H
#define RECEIVE_DEVICE_INFO_HANDLER_H

#include "./ReceiveHandler.h"
#include <Arduino.h>
#include <WebServer.h>

class ReceiveUserInfoHandler : public ReceiveHandler {
private:
    String userId;

public:
    ReceiveUserInfoHandler(const String& userIdRef) : userId(userIdRef) {}

    void handle(WebServer* server) override ;
    void setUserId(const String& id) {
        userId = id;
    }

    String getUserId() const {
        return userId;
    }
};

#endif