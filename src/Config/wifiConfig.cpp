#include "wifiConfig.h"
// bool finishSetUpMode = false;  


void resetPreferences() {
  preferences.begin("wifi", false);
  preferences.clear();
  preferences.end();
}

bool checkSavedWifi(String &savedSSID, String& savedPASS){
  preferences.begin("wifi", true);
  savedSSID = preferences.getString("ssid", "");
  savedPASS = preferences.getString("password", "");
  preferences.end();
  return savedSSID != "";
}

bool connectToSavedWiFi() {
  String savedSSID = "";
  String savedPASS = "";
  if (!checkSavedWifi(savedSSID, savedPASS))
    return false;

  WiFi.begin(savedSSID.c_str(), savedPASS.c_str());

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nKết nối wifi đã được lưu thành công!");
    return true;
  }

  Serial.println("\nKết nối wifi đã được lưu thất bại");
  return false;
}

void setupAPMode() {
  WiFi.disconnect(true);       
  delay(1000);                 
  WiFi.mode(WIFI_AP);        
  WiFi.softAP("ESP32_NTT", "123456789");
  IPAddress IP = WiFi.softAPIP();
  Serial.println("🔧 AP mode IP: " + IP.toString());
}

