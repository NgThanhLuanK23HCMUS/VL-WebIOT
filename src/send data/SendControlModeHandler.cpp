#include "SendControlModeHandler.h"
#include "../handler/handle.h"
#include <ArduinoJson.h>
#include "../handler/handle.h"

void SendControlModeHandler::send(const char *url)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(url);  

        http.addHeader("Content-Type", "application/json");

        String jsonData = "{";
        jsonData += "\"deviceId\":\"" + device->getDeviceId() + "\"";
        jsonData += "}";

        int httpResponseCode = http.POST(jsonData); 

        if (httpResponseCode > 0)
        {
            String response = http.getString();
            // Serial.println("Response code: " + String(httpResponseCode));
            // Serial.println("Response: " + response);
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, response);

            if (!error)
            {
                String mode = doc["mode"].as<String>();
                if(mode == "auto"){
                    receiveControlModeHandler->setControlMode(mode);
                } else if(mode == "manual") {
                    receiveControlModeHandler->setControlMode(mode);
                } 
            }
            else
            {
                Serial.println("Lỗi phân tích JSON");
            }
        }
        else
        {
            Serial.println("Lỗi gửi POST request: " + String(http.errorToString(httpResponseCode)));
        }

        http.end(); // Đóng kết nối
    }
    else
    {
        Serial.println("WiFi chưa được kết nối");
    }
}

