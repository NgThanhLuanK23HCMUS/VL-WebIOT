#ifndef HANDLE_H
#define HANDLE_H
#include <WebServer.h>
#include "../Sensor/Sensor.h"


class Handle{
public:
    static void handleReceiveUserID(WebServer* server, Sensor* sensor);
    static void handleSendDeviceInfo(Sensor* sensor);
    static void handleSendSensorData(Sensor* sensor);
};

#endif