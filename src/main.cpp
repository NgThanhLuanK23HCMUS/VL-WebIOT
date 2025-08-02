#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "Sensor/Sensor.h"
#include "./Routes/route.h"
#include"./handler/handle.h"
#include "./Config/globalSensorConfig.h"
#include <SPIFFS.h>
#include <Preferences.h>
#include "./Config/urlConfig.h"
#include "./Config/wifiConfig.h"

Preferences preferences;
WebServer* server = new WebServer(80);
String user_id = "";
// Handle* handle = new Handle();
unsigned long lastReadTime = 0;
const unsigned long readInterval = 10000;  // 60,000 ms = 1 phút
bool wifiJustConnectedFromAP = false;

enum AppState {
  STATE_WIFI_CONFIG,
  STATE_AP_MODE,
  STATE_WAIT_FOR_WIFI_CONFIG,
  STATE_WIFI_CONNECTED, 
  STATE_AUTO_MODE,
  STATE_MANUAL_MODE
};
AppState currentState = STATE_WIFI_CONFIG;



void setup() {
  
  Serial.begin(115200);
  resetPreferences();
  if (!SPIFFS.begin(true)) {
    Serial.println("Lỗi SPIFFS");
    return;
  }

  initializeGlobalSensorConfig();
  initializeGlobalHandlers(sensor, trafficLight);

  tempAndHumSensor->begin();
  soilSensor->begin();
  lightSensor->begin();
  trafficLight->begin();
}

void runMainApp(){
  lightSensor->readSensorData();
  if(sensor->getIsOn()) {
    trafficLight->turnOnfAll();
  } else {
    trafficLight->turnOffAll();
  }
  server->handleClient();  
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= readInterval) {
    lastReadTime = currentTime;
    tempAndHumSensor->readSensorData();
    soilSensor->readSensorData();
    if (sendSensorDataHandler != nullptr) 
      sendSensorDataHandler->send(dataUrl);
  }
}



void loop() {
  server->handleClient();  // Luôn xử lý request
 


    
  switch (currentState) {
    case STATE_WIFI_CONFIG:
      Serial.println("Đang kết nối WiFi đã lưu...");
      if (connectToSavedWiFi()) {
        Serial.println("Kết nối WiFi thành công");
        wifiJustConnectedFromAP = true;     // Đánh dấu là vừa kết nối
        currentState = STATE_WIFI_CONNECTED;
      } else {
        Serial.println("Không có WiFi đã lưu - chuyển sang AP Mode");
        currentState = STATE_AP_MODE;
      }
      break;

    case STATE_AP_MODE:
      setupAPMode();       
      setupAPRoutes();         
      server->begin();         
      Serial.println("Server AP mode đã khởi động");
      currentState = STATE_WAIT_FOR_WIFI_CONFIG;
      break;

    case STATE_WAIT_FOR_WIFI_CONFIG:
      if (receiveWifiConfigHandler->getFinishedConfigWifi()) {
        Serial.println("WiFi đã được cấu hình, đang kết nối...");
        wifiJustConnectedFromAP = true;  
         Serial.println(WiFi.localIP());

        currentState = STATE_WIFI_CONNECTED;
      }
      break;

    case STATE_AUTO_MODE:
      if(receiveControlModeHandler->getControlMode() == false) 
        currentState = STATE_MANUAL_MODE;
      
      runMainApp();    
      break;

    case STATE_MANUAL_MODE:
      if(receiveControlModeHandler->getControlMode() == true) {
        currentState = STATE_AUTO_MODE;
      }

      if(trafficLight->getIsOpen()) {
        trafficLight->turnOnfAll();
      } else {
        trafficLight->turnOffAll();
      }
      break;
    case STATE_WIFI_CONNECTED:
      if (wifiJustConnectedFromAP) {
        setupWiFiRoutes();     
        server->begin();     
        sendDeviceInfoHandler->send(infoDeviceUrl);
        wifiJustConnectedFromAP = false;    
        currentState = STATE_AUTO_MODE;
      }          
      break;
  }
}


