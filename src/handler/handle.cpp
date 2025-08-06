
#include "handle.h"

// Khai báo biến toàn cục
ReceiveUserInfoHandler* receiveUserInfoHandler = nullptr;
ReceiveHandler* receiveConfigPageHandler = nullptr;
ReceiveControlModeHandler* receiveControlModeHandler = nullptr;
ReceiveLedConfigHandler* receiveLedConfigHandler = nullptr;
ReceiveWifiConfigHandler* receiveWifiConfigHandler = nullptr;
ReceivePumpConfigHandler* receivePumpConfigHandler = nullptr;
// ReceiveBuzzerConfigHandler* receiveBuzzerConfigHandler = nullptr;

SendDeviceInfoHandler* sendDeviceInfoHandler = nullptr;
SendSensorDataHandler* sendSensorDataHandler = nullptr;
SendDeviceInfoAndUserHandler* sendDeviceInfoAndUserHandler = nullptr;
SendControlModeHandler* sendControlModelHandler = nullptr;

void initializeGlobalHandlers(Sensor* sensor, TrafficLight* trafficLight, Relay* relay) {
    receiveUserInfoHandler = new ReceiveUserInfoHandler("");
    receiveConfigPageHandler = new ReceiveConfigPageHandler();
    receiveControlModeHandler = new ReceiveControlModeHandler();
    receiveLedConfigHandler = new ReceiveLedConfigHandler(trafficLight);
    receivePumpConfigHandler = new ReceivePumpConfigHandler(relay);
    receiveWifiConfigHandler = new ReceiveWifiConfigHandler();
    // receiveBuzzerConfigHandler = new ReceiveBuzzerConfigHandler(buzzer);


    sendDeviceInfoHandler = new SendDeviceInfoHandler("ESP32", "1");
    sendSensorDataHandler = new SendSensorDataHandler(sensor);
    sendDeviceInfoAndUserHandler = new SendDeviceInfoAndUserHandler("1", "ESP32");
    sendControlModelHandler = new SendControlModeHandler();
}


