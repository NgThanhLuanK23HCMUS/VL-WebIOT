#ifndef SEND_DEVICE_INFO_AND_USER_HANDLER_H
#define SEND_DEVICE_INFO_AND_USER_HANDLER_H

#include "SendHandler.h"
#include "../Config/globalSensorConfig.h"

class SendDeviceInfoAndUserHandler : public SendHandler {
private:
    Device* device;

public:
    SendDeviceInfoAndUserHandler(Device* device) : device(device) {}

    void send(const char* url) override;

};

#endif
