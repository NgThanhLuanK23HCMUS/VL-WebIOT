#include "SendSensorDataHandler.h"
#include <time.h>

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

void SendSensorDataHandler::sendToThingSpeak()
{
    const char* write_key = "5YDUCIRMRS3IAAT4";
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi không kết nối!");
        return;
    }

    HTTPClient http;
    const char* thingspeakUrl = "http://api.thingspeak.com/update";
    http.begin(thingspeakUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Đọc sensor
    float humidity = sensor->getHumidity();
    float temperature = sensor->getTemperature();
    float soilMoisture = sensor->getSoilMoisture();

    // Tạo payload form-encoded: api_key=...&field1=...&field2=...
    String postData = "api_key=";
    postData += String(writeKey);
    postData += "&field1=" + String(soilMoisture, 2);
    postData += "&field2=" + String(temperature, 2);
    postData += "&field3=" + String(humidity, 2);

    Serial.println("📦 Gửi tới ThingSpeak:");
    Serial.println(postData);

    int responseCode = http.POST(postData);
    Serial.printf("📡 ThingSpeak trả về: %d\n", responseCode);

    if (responseCode > 0) {
        String resp = http.getString();
        Serial.println("📬 Response body: " + resp);
        // resp là entry ID (>0) nếu thành công, 0 nếu lỗi (ví dụ quá nhanh)
    } else {
        Serial.printf("❌ Lỗi gửi dữ liệu: %s\n", http.errorToString(responseCode).c_str());
    }

    http.end();
}


void SendSensorDataHandler::sendCurrentTimeToThingSpeak(int field)
{
    const char* write_key = "5YDUCIRMRS3IAAT4";
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi không kết nối!");
        return;
    }

    // Thử lấy thời gian hiện tại
    time_t now = time(nullptr);

    if (now == 0) {
        // Serial.println("Chưa có thời gian hệ thống, đang cấu hình NTP...");
        configTime(0, 0, "pool.ntp.org"); // lấy UTC
        delay(1500); // đợi đồng bộ sơ bộ
        now = time(nullptr);
        if (now == 0) {
            Serial.println("❌ Không thể đồng bộ thời gian (NTP thất bại).");
            return;
        }
    }

    const long timezoneOffset = 7 * 3600; // sửa nếu cần múi giờ khác
    now += timezoneOffset;

    // Chuyển sang struct tm và format
    struct tm *ptm = gmtime(&now);
    char dateTimeBuffer[25];
    sprintf(dateTimeBuffer, "%04d-%02d-%02d %02d:%02d:%02d",
            (ptm->tm_year + 1900),
            (ptm->tm_mon + 1),
            ptm->tm_mday,
            ptm->tm_hour,
            ptm->tm_min,
            ptm->tm_sec);

    // Gửi lên ThingSpeak (field1 chứa chuỗi thời gian)
    HTTPClient http;
    const char* thingspeakUrl = "http://api.thingspeak.com/update";
    http.begin(thingspeakUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "api_key=";
    postData += String(write_key);
    // Gửi thời gian như một string vào field1
    postData += "&field" + String(field) + "=";
    postData += String(dateTimeBuffer);

    Serial.println("📦 Gửi thời gian tới ThingSpeak:");
    Serial.println(postData);

    int responseCode = http.POST(postData);
    Serial.printf("📡 ThingSpeak trả về: %d\n", responseCode);

    if (responseCode > 0) {
        String resp = http.getString();
        Serial.println("📬 Response body: " + resp);
        // resp là entry ID (>0) nếu thành công, 0 nếu lỗi (ví dụ rate limit)
    } else {
        Serial.printf("❌ Lỗi gửi dữ liệu: %s\n", http.errorToString(responseCode).c_str());
    }

    http.end();
}
