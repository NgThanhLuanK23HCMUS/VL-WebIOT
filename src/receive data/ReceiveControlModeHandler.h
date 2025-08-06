#ifndef RECEIVE_CONTROL_MODE_HANDLER_H
#define RECEIVE_CONTROL_MODE_HANDLER_H

#include "ReceiveHandler.h"
#include <WebServer.h>


class ReceiveControlModeHandler : public ReceiveHandler {
private:
    String controlMode = "null"; 
public:
    void handle(WebServer* server) override;

    void setControlMode(String mode) {
        controlMode = mode;
    }

    String getControlMode() const {
        return this->controlMode;
    }
};

#endif
