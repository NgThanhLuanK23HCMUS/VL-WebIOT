#ifndef SEND_SENSOR_DATA_HANDLER_H
#define SEND_SENSOR_DATA_HANDLER_H

#include "SendHandler.h"
#include "../Sensor/Sensor.h"  // đảm bảo bạn include đúng đường dẫn tới lớp Sensor

class SendSensorDataHandler : public SendHandler {
private:
    Sensor* sensor;

public:
    SendSensorDataHandler(Sensor* s) : sensor(s) {}

    void send(const char* url) override ;
    void sendShockData(const char* url);
    void sendToThingSpeak();
    void sendCurrentTimeToThingSpeak(int field);
};

#endif
