#ifndef RECEIVE_WIFI_CONFIG_HANDLER_H
#define RECEIVE_WIFI_CONFIG_HANDLER_H

#include "ReceiveHandler.h"
#include <WebServer.h>
#include <Preferences.h>

class ReceiveWifiConfigHandler : public ReceiveHandler {
private:
    bool finishConfigWifi = false; 
public:
    void handle(WebServer* server) override;

    bool getFinishedConfigWifi() const {
        return finishConfigWifi;
    }
    void setConfigFinished(bool finished) {
        finishConfigWifi = finished;
    }
};

#endif
