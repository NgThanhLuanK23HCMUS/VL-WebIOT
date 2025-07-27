#include "route.h"
#include "../handler/handle.h"

extern WebServer* server;
extern Handle* handle;
extern Sensor* sensor;

Route route[] = {
    {
        "/api/user/send_id_to_device",
        HTTP_ANY,
        []() { handle->handleReceiveUserID(server, sensor); }  
    }
};

int routeCount = sizeof(route) / sizeof(Route);

void setupRoutes()
{
    for(int i = 0; i < routeCount; ++i){
        server->on(route[i].path, route[i].method, route[i].handler);
    }
}
