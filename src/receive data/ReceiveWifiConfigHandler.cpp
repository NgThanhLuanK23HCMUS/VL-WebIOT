#include "ReceiveWifiConfigHandler.h"
extern Preferences preferences;

void ReceiveWifiConfigHandler::handle(WebServer *server)
{
     String ssid = server->arg("ssid");
    String password = server->arg("password");

    if (ssid == "" || password.length() < 8) {
        server->send(400, "text/plain", "❌ SSID hoặc mật khẩu không hợp lệ");
        this->finishConfigWifi = false;
    }

    Serial.println("🧠 Nhận được SSID: " + ssid);
    Serial.println("🔑 Mật khẩu: " + password);

    preferences.begin("wifi", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    int attempt = 0;
    const int maxAttempts = 10;
    while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nKết nối WiFi thành công sau khi cấu hình");
        server->send(200, "text/plain", "Kết nối WiFi thành công. Đang chuyển trạng thái...");
        this->finishConfigWifi = true;
    } else {
        Serial.println("\nKết nối thất bại. Giữ nguyên chế độ cấu hình.");
        server->send(200, "text/plain", "Không thể kết nối WiFi. Vui lòng kiểm tra lại.");
        this->finishConfigWifi = false;

    }
}