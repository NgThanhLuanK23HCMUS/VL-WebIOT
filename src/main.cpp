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
unsigned long lastReadTime = 0;
const unsigned long readInterval = 120000;  // 60,000 ms = 1 phút

const unsigned long pumpInterval = 60000;
extern unsigned long lastPumpTime ;
unsigned long lastPumpTime = 0;

extern unsigned long lastBuzzerTime;
unsigned long lastBuzzerTime = 0;


bool wifiJustConnectedFromAP = false;
bool isFinishedConfigWifi = false;


enum AppState {
  STATE_WIFI_CONFIG,
  STATE_AP_MODE,
  STATE_WAIT_FOR_WIFI_CONFIG,
  STATE_WIFI_CONNECTED, 
  STATE_AUTO_MODE,
  STATE_MANUAL_MODE, 
  STATE_ERROR_MODE
};
AppState currentState = STATE_WIFI_CONFIG;


void setup() {
 
  Serial.begin(115200);
  // resetPreferences();
  if (!SPIFFS.begin(true)) {
    Serial.println("Lỗi SPIFFS");
    return;
  }

  initializeGlobalSensorConfig();
  initializeGlobalHandlers(sensor, trafficLight, relay);
  tempAndHumSensor->begin();
  soilSensor->begin();
  lightSensor->begin();
  trafficLight->begin();
  relay->begin();
  shockSensor->begin();
  // buzzer->begin();
}

void runAutoModeApp(){
  lightSensor->readSensorData();
  if(trafficLight->getIsOpen()) {
    trafficLight->turnOnfAll();
  } else {
    trafficLight->turnOffAll();
  }



  unsigned long currentTime = millis();
  
  if (currentTime - lastReadTime >= readInterval) {
    lastReadTime = currentTime;
    tempAndHumSensor->readSensorData();
    soilSensor->readSensorData();
    if (sendSensorDataHandler != nullptr) 
    sendSensorDataHandler->send(dataUrl);
    sendSensorDataHandler->sendToThingSpeak();
    
  }
  
  shockSensor->readSensorData();
  if(!shockSensor->getIsShock()){
    sendSensorDataHandler->sendShockData(shockDataUrl);
    sendSensorDataHandler->sendCurrentTimeToThingSpeak(5);
  }

}

void turnOffAllDevices() {
  trafficLight->setIsOpen(false);
  trafficLight->turnOffAll();
  relay->setIsOn(false);
  relay->turnOff();
}


void getCurrentState() {
  String controlMode = receiveControlModeHandler->getControlMode();
  if (controlMode == "auto") {
    if(currentState !=  STATE_AUTO_MODE)
      turnOffAllDevices(); 
    currentState = STATE_AUTO_MODE;
  } else if (controlMode == "manual") {
    if(currentState !=  STATE_MANUAL_MODE)
      turnOffAllDevices(); 
    currentState = STATE_MANUAL_MODE;
  } else if (controlMode == "null") {
    currentState = STATE_ERROR_MODE;
  }
}

void runManualModeApp() {
  if (trafficLight->getIsOpen()) {
    trafficLight->turnOnfAll();
  } else {
    trafficLight->turnOffAll();
  }

  if(relay->getIsOn()) {
    if (millis() - lastPumpTime >= pumpInterval) {
      relay->turnOff();  
      relay->setIsOn(false); 
      sendSensorDataHandler->sendCurrentTimeToThingSpeak(4);
    }
    else{

      relay->turnOn();  
    }
  }
 

}




void loop() {

  // lightSensor->readSensorData();


  server->handleClient();  // Luôn xử lý request
  if(isFinishedConfigWifi){
    getCurrentState();  
  }

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
      runAutoModeApp();    
      break;

    case STATE_MANUAL_MODE:
      runManualModeApp();
      break;


    case STATE_ERROR_MODE:
      turnOffAllDevices();
      break;



    case STATE_WIFI_CONNECTED:
      if (wifiJustConnectedFromAP) {
        setupWiFiRoutes();     
        server->begin();     
        sendDeviceInfoHandler->send(infoDeviceUrl);
        wifiJustConnectedFromAP = false; 
        isFinishedConfigWifi = true;     
        currentState = STATE_ERROR_MODE;
      }          
      break;
  }
}

