#ifndef RECEIVE_DEVICE_INFO_H
#define RECEIVE_DEVICE_INFO_H


#include <Arduino.h>
#include <WebServer.h>

bool receiveDeviceInfo(WebServer* server, String &user_id);

#endif 