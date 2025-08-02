#ifndef RECEIVE_HANDLER_H
#define RECEIVE_HANDLER_H

#include <WebServer.h>

class ReceiveHandler {
public:
    virtual void handle(WebServer* server) = 0; 
    virtual ~ReceiveHandler() {}
};

#endif
