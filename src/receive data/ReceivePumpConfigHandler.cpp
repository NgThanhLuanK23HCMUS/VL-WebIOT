#include "ReceivePumpConfigHandler.h"


extern unsigned long lastPumpTime;
void ReceivePumpConfigHandler::handle(WebServer *server)
{

    if (server->method() == HTTP_OPTIONS) {
        // Cho phép các domain khác gọi API này
        server->sendHeader("Access-Control-Allow-Origin", "*");
        server->sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
        server->sendHeader("Access-Control-Allow-Headers", "Content-Type");
        server->send(204);  // No Content
        return;
    }

    if (server->method() == HTTP_POST) {
        if (server->hasArg("state")) {
            String state = server->arg("state");
            if (state == "on") {
                relay->setIsOn(true);
                lastPumpTime = millis();  
            } else {
                relay->setIsOn(false);
                relay->turnOff(); 
            }

            server->sendHeader("Access-Control-Allow-Origin", "*");  
            server->send(200, "text/plain", "OK");
        } else {
            server->send(400, "text/plain", "Missing 'state' param");
        }
    }
}