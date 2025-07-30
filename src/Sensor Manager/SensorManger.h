#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "../Sensor/Sensor.h"

class SensorManager {
protected:
    Sensor* sensor;

public:
    SensorManager(Sensor* sensor) : sensor(sensor) {}

    virtual void begin() = 0;         // Bắt buộc lớp con phải hiện thực
    virtual void readSensorData() = 0;

    virtual ~SensorManager() {}
};

#endif
