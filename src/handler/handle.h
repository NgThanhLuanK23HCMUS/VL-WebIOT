
#ifndef GLOBAL_HANDLERS_H
#define GLOBAL_HANDLERS_H

#include <WebServer.h>
#include "../Sensor/Sensor.h"
#include "../Sensor Manager/TrafficLight.h"

#include "../receive data/ReceiveUserInfoHandler.h"
#include "../receive data/ReceiveConfigPageHandler.h"
#include "../receive data/ReceiveControlModeHandler.h"
#include "../receive data/ReceiveLedConfigHandler.h"
#include "../receive data/ReceiveWifiConfigHandler.h"

#include "../send data/SendDeviceInfoHandler.h"
#include "../send data/SendSensorDataHandler.h"
#include "../send data/SendDeviceInfoAndUserHandler.h"

extern ReceiveUserInfoHandler* receiveUserInfoHandler;
extern ReceiveHandler* receiveConfigPageHandler;
extern ReceiveControlModeHandler* receiveControlModeHandler;
extern ReceiveHandler* receiveLedConfigHandler;
extern ReceiveWifiConfigHandler* receiveWifiConfigHandler;

extern SendDeviceInfoHandler* sendDeviceInfoHandler;
extern SendSensorDataHandler* sendSensorDataHandler;
extern SendDeviceInfoAndUserHandler* sendDeviceInfoAndUserHandler;

// Hàm khởi tạo tất cả các handler
void initializeGlobalHandlers(Sensor* sensor, TrafficLight* trafficLight);

#endif
