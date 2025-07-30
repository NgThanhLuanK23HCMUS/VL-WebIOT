    #include "send_sensor_data.h"
    #include <WiFi.h>
    #include <HTTPClient.h>

    void sendSensorData(const char *infoURL, Sensor* sensor)
    {
        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.begin(infoURL);
            http.addHeader("Content-Type", "application/json");

            float humidity = sensor->getHumidity();
            float temperature = sensor->getTemperature();
            float soilMoisture = sensor->getSoilMoisture();
            bool is_on = sensor->getIsOn();

            String json = "{";
            json += "\"device_name\":\"" + sensor->getDeviceName() + "\",";
            json += "\"temperature\":" + String(temperature, 2) + ",";
            json += "\"humidity\":" + String(humidity, 2) + ",";
            json += "\"soil_moisture\":" + String(soilMoisture, 2) + ",";
            json += "\"is_on\":" + String(is_on);
            json += "}";

            Serial.println("📦 JSON gửi đi:");
            Serial.println(json);

            int responseCode = http.POST(json);
            Serial.print("📡 Trả lời từ server (sensor data): ");
            Serial.println(responseCode);

            http.end();
        } else {
            Serial.println("❌ WiFi không kết nối!");
        }
    }
