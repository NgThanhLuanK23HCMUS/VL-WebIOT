#include "ReceiveBuzzerConfigHandler.h"


extern unsigned long lastBuzzerTime ;

void ReceiveBuzzerConfigHandler::handle(WebServer *server)
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
            Serial.println(state);
            
            if (state == "on") {
                lastBuzzerTime = millis();
                buzzer->setIsBeep(true);
            } else {
                buzzer->setIsBeep(false);
                buzzer->stopTone();
                buzzer->setIsPlayingTone(false);
            }
            Serial.println(buzzer->getIsBeep());

            server->sendHeader("Access-Control-Allow-Origin", "*");  // CORS cho POST
            server->send(200, "text/plain", "OK");
        } else {
            server->send(400, "text/plain", "Missing 'state' param");
        }
    }
}