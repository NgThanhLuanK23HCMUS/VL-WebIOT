#ifndef ROUTE_H
#define ROUTE_H
#include <HTTPClient.h>
#include <WebServer.h>
#include "../receive data/receive_device_info.h"
#include <functional>
#include "../config.h"

struct Route
{
    const char* path;
    HTTPMethod method;
    std::function<void()> handler;
};

void setupRoutes();


#endif