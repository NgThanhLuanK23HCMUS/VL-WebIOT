#include "ReceiveControlModeHandler.h"

void ReceiveControlModeHandler::handle(WebServer *server)
{
    if (server->method() == HTTP_OPTIONS) {
        server->sendHeader("Access-Control-Allow-Origin", "*");
        server->sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
        server->sendHeader("Access-Control-Allow-Headers", "Content-Type");
        server->send(204);
        return;
    }

    if (server->method() == HTTP_POST) {
        if (server->hasArg("mode")) {
            String mode = server->arg("mode");

            if (mode == "auto") {
                this->controlMode = "auto";
            } else if (mode == "manual") {
                this->controlMode = "manual";
            } else if (mode == "null") { 
                this->controlMode = "null";
            }else {
                server->send(400, "text/plain", "Invalid 'mode' value");
                return;
            }

            server->sendHeader("Access-Control-Allow-Origin", "*");
            server->send(200, "text/plain", "Control mode set to: " + mode);
        } else {
            server->send(400, "text/plain", "Missing 'mode' param");
        }

    }
}