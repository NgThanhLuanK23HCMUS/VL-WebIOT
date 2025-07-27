#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "config.h"
#include "Sensor/Sensor.h"
#include "./Routes/route.h"
#include"./handler/handle.h"
#include "./Sensor Manager/SensorManger.h"

#define DHTPIN 14
#define DHTTYPE DHT11


Sensor* sensor = new Sensor("ESPPP");
SensorManager* sensorManager = new SensorManager(DHTPIN, DHTTYPE, sensor);
WebServer* server = new WebServer(80);
String user_id = "";

Handle* handle = new Handle();


void setup() {
  Serial.begin(115200);
  sensorManager->begin();


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
const unsigned long readInterval = 60000;  // 60,000 ms = 1 phút
void loop() {
  server->handleClient();  
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= readInterval) {
    lastReadTime = currentTime;

    sensorManager->readTemAndHum();
    handle->handleSendSensorData(sensor);
  }
}

