#include "SendSensorDataHandler.h"
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


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
    postData += String(write_key);
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


void SendSensorDataHandler::sendToThingSpeak(int field)
{
    // Cấu hình channel / keys — đổi theo channel của bạn nếu cần
    const char* channel_id = "3027556";          // channel ID
    const char* read_key   = "MOK8E9XJGEBTER1I"; // Read API key (nếu cần)
    const char* write_key  = "5YDUCIRMRS3IAAT4"; // Write API key

    // Kiểm tra WiFi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi không kết nối!");
        return;
    }

    // Giới hạn field hợp lệ (1..6)
    if (field < 1 || field > 6) {
        Serial.println("Field phải nằm trong khoảng 1..6");
        return;
    }

    // --- 1) Lấy bản ghi cuối cùng (last.json) để lấy giá trị hiện tại của các field ---
    HTTPClient httpGet;
    String lastUrl = String("https://api.thingspeak.com/channels/") + String(channel_id) + "/feeds/last.json";
    if (read_key && String(read_key).length() > 0) {
        lastUrl += "?api_key=";
        lastUrl += String(read_key);
    }

    Serial.println("🔎 Lấy bản ghi cuối từ ThingSpeak:");
    Serial.println(lastUrl);

    httpGet.begin(lastUrl);
    int codeGet = httpGet.GET();
    if (codeGet <= 0) {
        Serial.printf("❌ Lỗi GET last.json: %s (code=%d)\n", httpGet.errorToString(codeGet).c_str(), codeGet);
        httpGet.end();
        return;
    }

    String payloadGet = httpGet.getString();
    httpGet.end();

    // Parse JSON bằng ArduinoJson
    // Kích thước doc: thay đổi tuỳ JSON; 1024-2048 thường đủ cho last.json nhỏ
    DynamicJsonDocument doc(2048);
    DeserializationError err = deserializeJson(doc, payloadGet);
    if (err) {
        Serial.print("❌ Lỗi parse JSON last.json: ");
        Serial.println(err.c_str());
        return;
    }

    // Lấy giá trị 6 field hiện tại (dùng string để dễ gán)
    String fields[7]; // dùng index 1..6, bỏ index 0
    for (int i = 1; i <= 6; ++i) {
        const char* key = String("field" + String(i)).c_str();
        // Nếu trường tồn tại trong JSON và không null -> lấy; ngược lại để rỗng
        if (!doc.isNull() && doc.containsKey(key) && !doc[key].isNull()) {
            fields[i] = String((const char*)doc[key]);
        } else {
            // Nếu last.json không có giá trị cho field đó, ta đặt mặc định là "0"
            // Bạn có thể đổi thành "" hoặc "0" tuỳ mong muốn
            fields[i] = String(""); // giữ rỗng nếu muốn (hoặc "0")
        }
    }

    // --- 2) Gán giá trị mới cho field được chỉ định ---
    // Nếu bạn muốn lưu "turned_on" dưới dạng số (0/1), chuyển trước khi gán.
    fields[field] = "turned_on";

    // In ra các giá trị trước khi gửi
    Serial.println("📋 Giá trị sẽ gửi (field1..field6):");
    for (int i = 1; i <= 6; ++i) {
        Serial.printf("  field%d = %s\n", i, fields[i].c_str());
    }

    // --- 3) Tạo POST payload form-encoded ---
    String postData = "api_key=";
    postData += String(write_key);
    for (int i = 1; i <= 6; ++i) {
        postData += "&field" + String(i) + "=";
        // URL-encode cơ bản (space -> %20). Nếu cần an toàn hơn, nên viết hàm urlEncode.
        String v = fields[i];
        // Nếu rỗng thì gán giá trị mặc định "": (ThingSpeak sẽ giữ giá trị cũ? Không, gửi rỗng có thể tạo entry blank.)
        // Vì ta đã lấy từ last.json, fields[i] nên có giá trị. Nếu rỗng, hãy gán "0" để an toàn:
        if (v.length() == 0) v = "0";
        // Thay space thành %20 đơn giản:
        v.replace(" ", "%20");
        postData += v;
    }

    // --- 4) Gửi POST tới ThingSpeak ---
    HTTPClient httpPost;
    const char* thingspeakUrl = "http://api.thingspeak.com/update";
    httpPost.begin(thingspeakUrl);
    httpPost.addHeader("Content-Type", "application/x-www-form-urlencoded");

    Serial.println("📦 Gửi tới ThingSpeak:");
    Serial.println(postData);

    int responseCode = httpPost.POST(postData);
    Serial.printf("📡 ThingSpeak trả về: %d\n", responseCode);

    if (responseCode > 0) {
        String resp = httpPost.getString();
        Serial.println("📬 Response body: " + resp); // >0 là entry id, 0 là thất bại (rate-limit...)
    } else {
        Serial.printf("❌ Lỗi gửi dữ liệu: %s\n", httpPost.errorToString(responseCode).c_str());
    }

    httpPost.end();
}