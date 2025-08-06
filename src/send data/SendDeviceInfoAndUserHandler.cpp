#include "SendDeviceInfoAndUserHandler.h"

void SendDeviceInfoAndUserHandler::send(const char *url)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(url);
        http.addHeader("Content-Type", "application/json");

        // Tạo dữ liệu JSON
        String jsonData = "{";
        jsonData += "\"deviceId\":\"" + deviceId + "\",";
        jsonData += "\"userId\":\"" + userId + "\"";
        jsonData += "}";

        // Gửi POST request với nội dung JSON
        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0)
        {
            String response = http.getString();
            Serial.println("Response code: " + String(httpResponseCode));
            Serial.println("Response: " + response);
        }
        else
        {
            Serial.println("Error sending POST request: " + String(http.errorToString(httpResponseCode)));
        }

        http.end();
    }
    else
    {
        Serial.println("WiFi not connected");
    }
}