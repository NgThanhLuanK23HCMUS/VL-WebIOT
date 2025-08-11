#ifndef SEND_DEVICE_INFO_HANDLER_H
#define SEND_DEVICE_INFO_HANDLER_H

#include "SendHandler.h"
#include "../Config/globalSensorConfig.h"

class SendDeviceInfoHandler : public SendHandler {
private:
    Device* device;
public:
    SendDeviceInfoHandler(Device* device) : device(device) {}

    void send(const char* url) override;

};

#endif
