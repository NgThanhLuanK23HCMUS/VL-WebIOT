#ifndef RECEIVE_CONTROL_MODE_HANDLER_H
#define RECEIVE_CONTROL_MODE_HANDLER_H

#include "ReceiveHandler.h"
#include <WebServer.h>

extern bool controlMode;

class ReceiveControlModeHandler : public ReceiveHandler {
private:
    bool controlMode = false; 
public:
    void handle(WebServer* server) override;

    void setControlMode(bool mode) {
        controlMode = mode;
    }

    bool getControlMode() const {
        return controlMode;
    }
};

#endif
