
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
#include "../receive data/ReceivePumpConfigHandler.h"
#include "../receive data/ReceiveBuzzerConfigHandler.h"

#include "../send data/SendDeviceInfoHandler.h"
#include "../send data/SendSensorDataHandler.h"
#include "../send data/SendDeviceInfoAndUserHandler.h"
#include "../send data/SendControlModeHandler.h"



extern ReceiveUserInfoHandler* receiveUserInfoHandler;
extern ReceiveHandler* receiveConfigPageHandler;
extern ReceiveControlModeHandler* receiveControlModeHandler;
extern ReceiveLedConfigHandler* receiveLedConfigHandler;
extern ReceiveWifiConfigHandler* receiveWifiConfigHandler;
extern ReceivePumpConfigHandler* receivePumpConfigHandler;
extern ReceiveBuzzerConfigHandler* receiveBuzzerConfigHandler;


extern SendDeviceInfoHandler* sendDeviceInfoHandler;
extern SendSensorDataHandler* sendSensorDataHandler;
extern SendDeviceInfoAndUserHandler* sendDeviceInfoAndUserHandler;
extern SendControlModeHandler* sendControlModelHandler;

// Hàm khởi tạo tất cả các handler
void initializeGlobalHandlers(Sensor* sensor, TrafficLight* trafficLight, Relay* relay, Buzzer* buzzer);
#endif
