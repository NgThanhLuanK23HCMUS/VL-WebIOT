#ifndef SEND_DEVICE_INFO_HANDLER_H
#define SEND_DEVICE_INFO_HANDLER_H

#include "SendHandler.h"

class SendDeviceInfoHandler : public SendHandler {
private:
    String deviceName;
    String deviceId;
public:
    SendDeviceInfoHandler(const String& name, const String& id) : deviceName(name), deviceId(id) {}

    void send(const char* url) override;
    String getDeviceId(){
        return this->deviceId;
    }
};

#endif
