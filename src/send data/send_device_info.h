#ifndef SEND_INFO_DEVICE_H
#define SEND_INFO_DEVICE_H
#include <Arduino.h>

void sendDeviceInfo(const char* infoURL, const String& device_name, const String& user_id);

#endif
