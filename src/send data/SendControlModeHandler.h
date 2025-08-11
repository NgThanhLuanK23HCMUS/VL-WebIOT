#ifndef SEND_CONTROL_MODE_HANDLER_H
#define SEND_CONTROL_MODE_HANDLER_H

#include "SendHandler.h"
#include "../Config/globalSensorConfig.h"

class SendControlModeHandler : public SendHandler {
private:
    Device* device;
public:
    SendControlModeHandler(Device* device) : device(device) {}
    void send(const char* url) override;
};

#endif

