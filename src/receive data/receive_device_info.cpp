#include "receive_device_info.h"

bool receiveDeviceInfo(WebServer* server, String &user_id)
{
    if(server->method() == HTTP_POST){
        if(server->hasArg("user_id"))
            user_id = server->arg("user_id");
            return true;
    }
    return false;
}