
#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <FS.h>
#include <SPIFFS.h>

extern WebServer* server;
extern Preferences preferences;


void resetPreferences();
bool checkSavedWifi(String& savedSSID, String& savedPASS);
bool connectToSavedWiFi();
void setupAPMode( );

#endif
