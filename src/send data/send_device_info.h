#ifndef SEND_INFO_DEVICE_H
#define SEND_INFO_DEVICE_H
#include <Arduino.h>

void sendDeviceInfo(const char* infoURL, const String& deviceName);
void sendDeviceInfoAndUser(const char* inforUserUrl, const String& deviceName, const String& userId);

#endif
