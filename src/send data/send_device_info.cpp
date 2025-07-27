#include "send_device_info.h"
#include <WiFi.h>
#include <HTTPClient.h>

void sendDeviceInfo(const char * infoURL, const String& device_name, const String& user_id )
{
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        http.begin(infoURL);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String data = "";

        if(user_id != "")
            data = "device_name="+device_name + "&user_id=" + user_id;
        else
            data = "device_name=" + device_name;
        int responseCode = http.POST(data);
        Serial.print("📡 Trả lời từ server (thông tin thiết bị): ");
        Serial.println(responseCode);
        http.end();
        } 
}