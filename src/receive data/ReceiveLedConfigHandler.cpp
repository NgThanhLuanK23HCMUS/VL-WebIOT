#include "ReceiveLedConfigHandler.h"

void ReceiveLedConfigHandler::handle(WebServer *server)
{
    if (server->method() == HTTP_POST) {
        if (server->hasArg("state")) { 
            String state = server->arg("state");

            if (state == "on") {
                trafficLight->setIsOpen(true);
            } else {
                trafficLight->setIsOpen(false);
            }

            server->sendHeader("Access-Control-Allow-Origin", "*"); // cần cho fetch CORS
            server->send(200, "text/plain", "OK");
        } else {
            server->send(400, "text/plain", "Missing 'state' param");
        }
    }
}