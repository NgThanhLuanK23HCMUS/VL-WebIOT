#ifndef RECEIVE_WIFI_CONFIG_HANDLER_H
#define RECEIVE_WIFI_CONFIG_HANDLER_H

#include "ReceiveHandler.h"
#include <WebServer.h>
#include <Preferences.h>

class ReceiveWifiConfigHandler : public ReceiveHandler {
private:
    String finishConfigWifi = "null"; 
public:

    void setConfigFinished(String finished) {
        finishConfigWifi = finished;
    }

    void handle(WebServer* server) override;
    
    
    String getFinishedConfigWifi() const {
        return finishConfigWifi;
    }
};

#endif
