#include "route.h"
#include "../handler/handle.h"
#include "../Sensor/Sensor.h"
#include <SPIFFS.h>

extern WebServer* server;
extern Sensor* sensor;

// Route cho AP Mode
Route apRoutes[] = {
    {
        "/save", HTTP_POST,
        []() { receiveWifiConfigHandler->handle(server); }
    },
    {
        "/", HTTP_GET,
        []() { receiveConfigPageHandler->handle(server); }
    }
};

// Route cho WiFi Mode
Route wifiRoutes[] = {
    {
        "/api/control_led",
        HTTP_POST,
        []() { receiveLedConfigHandler->handle(server); }
    },
    {
        "/api/user/send_id_to_device",
        HTTP_ANY,
        []() { receiveUserInfoHandler->handle(server); }
    },
    {
        "/api/control_beep",
        HTTP_POST,
        []() { receiveBuzzerConfigHandler->handle(server); }
    },
    {
        "/api/control_pump", 
        HTTP_POST,
        []() { receivePumpConfigHandler->handle(server); }
    },
    {
        "/api/save/threshold",
        HTTP_POST,
        []() { receiveThresholdConfigHandler->handle(server); }
    },
    {
        "/api/control_mode",
        HTTP_POST,
        []() { receiveControlModeHandler->handle(server); }
    },      
};

int apRouteCount = sizeof(apRoutes) / sizeof(Route);

int wifiRouteCount = sizeof(wifiRoutes) / sizeof(Route);
void setupWiFiRoutes()
{
    for (int i = 0; i < wifiRouteCount; ++i) {
        server->on(wifiRoutes[i].path, wifiRoutes[i].method, wifiRoutes[i].handler);
    }
}

void setupAPRoutes()
{
    for (int i = 0; i < apRouteCount; ++i) {
        server->on(apRoutes[i].path, apRoutes[i].method, apRoutes[i].handler);
    }
}
