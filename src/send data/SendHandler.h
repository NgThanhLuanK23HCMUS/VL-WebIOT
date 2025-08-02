#ifndef SEND_HANDLER_H
#define SEND_HANDLER_H

#include <Arduino.h>
#include <HTTPClient.h>

class SendHandler {
public:
    virtual void send(const char* url) = 0;
    virtual ~SendHandler() {}
};

#endif
