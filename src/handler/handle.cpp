
#include "handle.h"

// Khai báo biến toàn cục
ReceiveUserInfoHandler* receiveUserInfoHandler = nullptr;
ReceiveHandler* receiveConfigPageHandler = nullptr;
ReceiveControlModeHandler* receiveControlModeHandler = nullptr;
ReceiveLedConfigHandler* receiveLedConfigHandler = nullptr;
ReceiveWifiConfigHandler* receiveWifiConfigHandler = nullptr;
ReceivePumpConfigHandler* receivePumpConfigHandler = nullptr;
ReceiveBuzzerConfigHandler* receiveBuzzerConfigHandler = nullptr;

SendDeviceInfoHandler* sendDeviceInfoHandler = nullptr;
SendSensorDataHandler* sendSensorDataHandler = nullptr;
SendDeviceInfoAndUserHandler* sendDeviceInfoAndUserHandler = nullptr;
SendControlModeHandler* sendControlModelHandler = nullptr;

void initializeGlobalHandlers(Sensor* sensor, TrafficLight* trafficLight, Relay* relay, Buzzer* buzzer, Device* device) {
    receiveUserInfoHandler = new ReceiveUserInfoHandler(device);
    receiveConfigPageHandler = new ReceiveConfigPageHandler();
    receiveControlModeHandler = new ReceiveControlModeHandler();
    receiveLedConfigHandler = new ReceiveLedConfigHandler(trafficLight);
    receivePumpConfigHandler = new ReceivePumpConfigHandler(relay);
    receiveWifiConfigHandler = new ReceiveWifiConfigHandler();
    receiveBuzzerConfigHandler = new ReceiveBuzzerConfigHandler(buzzer);


    sendDeviceInfoHandler = new SendDeviceInfoHandler(device);
    sendSensorDataHandler = new SendSensorDataHandler(sensor, device);
    sendDeviceInfoAndUserHandler = new SendDeviceInfoAndUserHandler(device);
    sendControlModelHandler = new SendControlModeHandler(device);
}


