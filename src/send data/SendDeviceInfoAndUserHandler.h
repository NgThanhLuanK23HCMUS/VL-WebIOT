#ifndef SEND_DEVICE_INFO_AND_USER_HANDLER_H
#define SEND_DEVICE_INFO_AND_USER_HANDLER_H

#include "SendHandler.h"

class SendDeviceInfoAndUserHandler : public SendHandler {
private:
    String deviceId;
    String userId;

public:
    SendDeviceInfoAndUserHandler(const String& id, const String& uid)
        : deviceId(id), userId(uid) {}

    void send(const char* url) override;
    void setDeviceId(const String& id) {
        deviceId = id;
    }
    void setUserId(const String& uid) {
        userId = uid;
    }
};

#endif
