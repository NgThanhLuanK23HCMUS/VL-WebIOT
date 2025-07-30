#include "send_device_info.h"
#include <WiFi.h>
#include <HTTPClient.h>



void sendDeviceInfo(const char *infoURL, const String &deviceName)
{
    if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;
            http.begin(infoURL);
            http.addHeader("Content-Type", "application/json");

            // Tạo dữ liệu JSON
            String jsonData = "{";
            jsonData += "\"deviceName\":\"" + deviceName + "\"";
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

void sendDeviceInfoAndUser(const char *inforUserUrl, const String &deviceName, const String &userId)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(inforUserUrl);
        http.addHeader("Content-Type", "application/json");

        // Tạo dữ liệu JSON
        String jsonData = "{";
        jsonData += "\"deviceName\":\"" + deviceName + "\",";
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