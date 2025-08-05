#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <DHT.h>
#include "../Sensor/Sensor.h"

class SensorManager {
protected:
    Sensor* sensor;

public:
    SensorManager(){}
    SensorManager(Sensor* sensor)
        : sensor(sensor) {}
};

#endif
