// #include "App.h"
// #include "./Config/urlConfig.h"
// #include "./Routes/route.h"
// #include "./Config/wifiConfig.h"

// unsigned long lastReadTime = 0;
// const unsigned long readInterval = 10000;
// bool wifiJustConnectedFromAP = false;
// AppState currentState = STATE_WIFI_CONFIG;
// bool isFinishedConfigWifi = false;
// WebServer* server = new WebServer(80);

// void runAutoModeApp()
// {
//     lightSensor->readSensorData();
//     if (trafficLight->getIsOpen()) {
//         trafficLight->turnOnfAll();
//     } else {
//         trafficLight->turnOffAll();
//     }

//     server->handleClient();
//     unsigned long currentTime = millis();
//     if (currentTime - lastReadTime >= readInterval) {
//         lastReadTime = currentTime;
//         tempAndHumSensor->readSensorData();
//         soilSensor->readSensorData();
//         // if (sendSensorDataHandler != nullptr) 
//         //   sendSensorDataHandler->send(dataUrl);
//     }
// }

// void runManualModeApp() {
//     lightSensor->readSensorData();
//     if (trafficLight->getIsOpen()) {
//         trafficLight->turnOnfAll();
//     } else {
//         trafficLight->turnOffAll();
//     }

//     // if(relay->getIsOn()) {
//     //     relay->turnOn();
//     // } else {
//     //     relay->turnOff();
//     // }
// }


// void runErrorModeApp() {
//     trafficLight->setIsOpen(false);
//     trafficLight->turnOffAll();
//     // relay->turnOff();
// }



// void handleAppState() {
//     server->handleClient();
//     getCurrentState();



//     switch (currentState) {
//         case STATE_WIFI_CONFIG:
//             Serial.println("Đang kết nối WiFi đã lưu...");
//             if (connectToSavedWiFi()) {
//                 Serial.println("Kết nối WiFi thành công");
//                 wifiJustConnectedFromAP = true;
//                 currentState = STATE_WIFI_CONNECTED;
//             } else {
//                 Serial.println("Không có WiFi đã lưu - chuyển sang AP Mode");
//                 currentState = STATE_AP_MODE;
//             }
//             break;

//         case STATE_AP_MODE:
//             setupAPMode();
//             setupAPRoutes();
//             server->begin();
//             Serial.println("Server AP mode đã khởi động");
//             currentState = STATE_WAIT_FOR_WIFI_CONFIG;
//             break;

//         case STATE_WAIT_FOR_WIFI_CONFIG:
//             if (receiveWifiConfigHandler->getFinishedConfigWifi()) {
//                 Serial.println("WiFi đã được cấu hình, đang kết nối...");
//                 wifiJustConnectedFromAP = true;
//                 Serial.println(WiFi.localIP());
//                 currentState = STATE_WIFI_CONNECTED;
//             }
//             break;

//         case STATE_WIFI_CONNECTED:
//             if (wifiJustConnectedFromAP) {
//                 setupWiFiRoutes();
//                 server->begin();
//                 sendDeviceInfoHandler->send(infoDeviceUrl);
//                 wifiJustConnectedFromAP = false;
//                 isFinishedConfigWifi = true; 
//                 currentState = STATE_AUTO_MODE;
//             }
//             break;

//         case STATE_AUTO_MODE:
//             runAutoModeApp();
//             break;

//         case STATE_MANUAL_MODE:
//             runManualModeApp();
//             break;

//         case STATE_ERROR_MODE:
//             runErrorModeApp();
//             break;
//     }
// }

// void getCurrentState()
// {
//     if(receiveControlModeHandler->getControlMode() == "manual") {
//         currentState = STATE_MANUAL_MODE;
//     } else if (receiveControlModeHandler->getControlMode() == "auto") {
//         currentState = STATE_AUTO_MODE;
//     } else if (receiveControlModeHandler->getControlMode() == "null") {
//         currentState = STATE_ERROR_MODE;
//     }
// }
