#ifndef SEND_DEVICE_INFO_AND_USER_HANDLER_H
#define SEND_DEVICE_INFO_AND_USER_HANDLER_H

#include "SendHandler.h"

class SendDeviceInfoAndUserHandler : public SendHandler {
private:
    String deviceName;
    String userId;

public:
    SendDeviceInfoAndUserHandler(const String& name, const String& uid)
        : deviceName(name), userId(uid) {}

    void send(const char* url) override;
    void setDeviceName(const String& name) {
        deviceName = name;
    }
    void setUserId(const String& uid) {
        userId = uid;
    }
};

#endif
