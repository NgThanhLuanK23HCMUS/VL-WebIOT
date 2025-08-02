#include "ReceiveUserInfoHandler.h"
#include "../config/urlConfig.h"
#include "../handler/handle.h"

void ReceiveUserInfoHandler::handle(WebServer *server)
{
    
    if (server->method() == HTTP_POST) {
        if (server->hasArg("user_id")) {
            this->userId = server->arg("user_id");
            if(this->userId != ""){
                sendDeviceInfoAndUserHandler->setUserId(this->userId);
                sendDeviceInfoAndUserHandler->send(infoDeviceAndUserUrl);
            }
            server->send(200, "text/plain", "User ID received");
        } else {
            server->send(400, "text/plain", "Missing user_id");
        }
    }
}
