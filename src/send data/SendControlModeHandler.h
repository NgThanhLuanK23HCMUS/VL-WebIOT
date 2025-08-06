#ifndef SEND_CONTROL_MODE_HANDLER_H
#define SEND_CONTROL_MODE_HANDLER_H

#include "SendHandler.h"

class SendControlModeHandler : public SendHandler {
public:
    void send(const char* url) override;
};

#endif

