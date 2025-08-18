
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

void setupAPMode( );
bool connectToSavedWiFi();

bool checkSavedWifi(String& savedSSID, String& savedPASS);

#endif
