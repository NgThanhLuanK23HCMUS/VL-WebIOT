#ifndef ROUTE_H
#define ROUTE_H
#include <HTTPClient.h>
#include <WebServer.h>
#include "../receive data/ReceiveUserInfoHandler.h"
#include <functional>
#include "../Config/urlConfig.h"

struct Route
{
    const char* path;
    HTTPMethod method;
    std::function<void()> handler;
};

void setupWiFiRoutes();
void setupAPRoutes();


#endif