#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "config.h"
#include "Sensor/Sensor.h"
#include "./Routes/route.h"
#include"./handler/handle.h"
#include "./globalSensorConfig.h"


WebServer* server = new WebServer(80);
String user_id = "";

Handle* handle = new Handle();


void setup() {
  Serial.begin(115200);
  tempAndHumSensor->begin();
  soilSensor->begin();
  lightSensor->begin();
  trafficLight->begin();

  WiFi.begin(ssid, password);
  Serial.print("🔌 Đang kết nối WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n✅ Đã kết nối WiFi!");

  handle->handleSendDeviceInfo(sensor);
  setupRoutes();
  server->begin();
}


unsigned long lastReadTime = 0;
const unsigned long readInterval = 10000;  // 60,000 ms = 1 phút
void loop() {
  server->handleClient();  
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= readInterval) {
    lastReadTime = currentTime;
    // Serial.println(sensor->getIsOn());
    // if(sensor->getIsOn() == 1)
    //   trafficLight->turnOnfAll();
    // else
    //   trafficLight->turnOffAll();
    tempAndHumSensor->readSensorData();
    soilSensor->readSensorData();
    lightSensor->readSensorData();
    handle->handleSendSensorData(sensor);
  }
}

