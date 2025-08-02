// #include "handle.h"
// #include "../receive data/receive_device_info.h"
// #include "../receive data/receive_config_wifi.h"
// #include "../send data/send_device_info.h"
// #include "../send data/send_sensor_data.h"
// #include "../Config/urlConfig.h"
// #include "../Sensor/Sensor.h"


// bool finishSetUpMode = false;  


// extern String user_id;
// void Handle::handleReceiveUserID(WebServer* server, Sensor* sensor)
// {
//     if (receiveDeviceInfo(server, user_id)) {
//         sendDeviceInfoAndUser(infoDeviceAndUserUrl, sensor->getDeviceName(), user_id);
//         server->sendHeader("Access-Control-Allow-Origin", "*"); // ⚠️ Bắt buộc
//         server->send(200, "text/plain", "Đã nhận user_id: " + user_id);
//     }
// }

// void Handle::handleSendDeviceInfo(Sensor* sensor)
// {
//     sendDeviceInfo(infoDeviceUrl, sensor->getDeviceName());
// }

// void Handle::handleSendSensorData(Sensor* sensor)
// {
//     sendSensorData(dataURL, sensor);
// }

// void Handle::handleConfigPage(WebServer *server)
// {
//     receiveConfigPage(server);
// }

// void Handle::handleSaveWifi(WebServer *server)
// {
//     bool ok = receiveWifiConfig(server);
//     if (ok) {
//         Serial.println("📡 Đã xử lý và kết nối WiFi thành công.");
//         finishSetUpMode = true; 
//     }
// }

// void Handle::handleReceiveLedConfig(TrafficLight *trafficLight, WebServer *server)
// {
//     receiveLedConfig(trafficLight, server);
// }

// // void Handle::handleReceiveBeepConfig(Buzzer *buzzer, WebServer *server)
// // {
// //     receiveBeepConfig(buzzer, server);
// // }

// void Handle::handleReceiveControlMode(WebServer *server)
// {
//     receiveControlMode(server);
// }

#include "handle.h"

// Khai báo biến toàn cục
ReceiveUserInfoHandler* receiveUserInfoHandler = nullptr;
ReceiveHandler* receiveConfigPageHandler = nullptr;
ReceiveControlModeHandler* receiveControlModeHandler = nullptr;
ReceiveHandler* receiveLedConfigHandler = nullptr;
ReceiveWifiConfigHandler* receiveWifiConfigHandler = nullptr;

SendDeviceInfoHandler* sendDeviceInfoHandler = nullptr;
SendSensorDataHandler* sendSensorDataHandler = nullptr;
SendDeviceInfoAndUserHandler* sendDeviceInfoAndUserHandler = nullptr;

void initializeGlobalHandlers(Sensor* sensor, TrafficLight* trafficLight) {
    receiveUserInfoHandler = new ReceiveUserInfoHandler("");
    receiveConfigPageHandler = new ReceiveConfigPageHandler();
    receiveControlModeHandler = new ReceiveControlModeHandler();
    receiveLedConfigHandler = new ReceiveLedConfigHandler(trafficLight);
    receiveWifiConfigHandler = new ReceiveWifiConfigHandler();

    sendDeviceInfoHandler = new SendDeviceInfoHandler("ESP32");
    sendSensorDataHandler = new SendSensorDataHandler(sensor);
    sendDeviceInfoAndUserHandler = new SendDeviceInfoAndUserHandler("ESP32", "");
}