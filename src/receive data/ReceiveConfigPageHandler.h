#ifndef RECEIVE_CONFIG_PAGE_HANDLER_H
#define RECEIVE_CONFIG_PAGE_HANDLER_H

#include "ReceiveHandler.h"
#include <WebServer.h>
#include <SPIFFS.h>

class ReceiveConfigPageHandler : public ReceiveHandler {
public:
    void handle(WebServer* server) override {
        File file = SPIFFS.open("/index.html", "r");
        if (!file) {
            server->send(500, "text/plain", "Không thể mở file HTML");
            return;
        }
        server->streamFile(file, "text/html");
        file.close();
    }
};

#endif
