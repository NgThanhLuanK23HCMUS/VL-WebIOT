#ifndef RECEIVE_BUZZER_CONFIG_HANDLER_H
#define RECEIVE_BUZZER_CONFIG_HANDLER_H


#include "ReceiveHandler.h"
#include "../Config/globalSensorConfig.h"
#include <WebServer.h>

class ReceiveBuzzerConfigHandler : public ReceiveHandler {
private:
    Buzzer* buzzer;
public:
    ReceiveBuzzerConfigHandler(Buzzer* buzzer) : buzzer(buzzer) {}

    void handle(WebServer* server) override;
};

#endif