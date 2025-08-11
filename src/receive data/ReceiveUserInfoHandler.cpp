#include "ReceiveUserInfoHandler.h"
#include "../config/urlConfig.h"
#include "../handler/handle.h"

void ReceiveUserInfoHandler::handle(WebServer *server)
{
    // Thêm header CORS cho mọi response
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    server->sendHeader("Access-Control-Allow-Headers", "Content-Type");

    if (server->method() == HTTP_OPTIONS) {
        server->send(204); // No Content
        return;
    }

    if (server->method() == HTTP_POST) {
        if (server->hasArg("user_id")) {
            device->setUserId(server->arg("user_id"));
            Serial.println(device->getUserId());
            if(device->getUserId() != ""){
                sendDeviceInfoAndUserHandler->send(infoDeviceAndUserUrl);
            }
            server->send(200, "text/plain", "User ID received");
        } else {
            server->send(400, "text/plain", "Missing user_id");
        }
    }
}
