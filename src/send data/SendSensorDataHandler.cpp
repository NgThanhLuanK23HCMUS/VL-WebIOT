#include "SendSensorDataHandler.h"

void SendSensorDataHandler::send(const char *url)
{
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
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
        Serial.printf("📡 Server trả lời: %d\n", responseCode);

        if (responseCode > 0) {
            Serial.println("📬 Response: " + http.getString());
        } else {
            Serial.printf("❌ Lỗi gửi dữ liệu: %s\n", http.errorToString(responseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("WiFi không kết nối!");
    }
}

void SendSensorDataHandler::sendShockData(const char *url)
{
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        String fullUrl = String(url) + "?data=1";

        http.begin(fullUrl);

        int responseCode = http.GET();  

        if (responseCode > 0) {
            Serial.println("📬 Response: " + http.getString());
        } else {
            Serial.printf("❌ Lỗi gửi dữ liệu: %s\n", http.errorToString(responseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("WiFi không kết nối!");
    }
}
