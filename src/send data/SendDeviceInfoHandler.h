#ifndef SEND_DEVICE_INFO_HANDLER_H
#define SEND_DEVICE_INFO_HANDLER_H

#include "SendHandler.h"

class SendDeviceInfoHandler : public SendHandler {
private:
    String deviceName;

public:
    SendDeviceInfoHandler(const String& name) : deviceName(name) {}

    void send(const char* url) override;
};

#endif
