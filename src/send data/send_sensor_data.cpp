#include "send_sensor_data.h"
#include <WiFi.h>
#include <HTTPClient.h>

void sendSensorData(const char *infoURL, Sensor* sensor)
{
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(infoURL);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        float humidity = sensor->getHumidity();
        float temperature = sensor->getTemperature();

        String data = "device_name="+ sensor->getDeviceName() + "&temperature=" + String(temperature, 2) + "&humidity=" + String(humidity, 2);
        Serial.println(data);
        int responseCode = http.POST(data);

        Serial.print("📡 Trả lời từ server (sensor data): ");
        Serial.println(responseCode);

        http.end();
    } else {
        Serial.println("❌ WiFi không kết nối!");
    }
}
