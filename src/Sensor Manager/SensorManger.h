#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <DHT.h>
#include "../Sensor/Sensor.h"

class SensorManager {
private:
    DHT dht;
    Sensor* sensor;

public:
    SensorManager(uint8_t pin, uint8_t type, Sensor* sensor)
        : dht(pin, type), sensor(sensor) {}

    void begin() {
        dht.begin();
    }

    void readTemAndHum();

    // Sensor* getSensor() const {
    //     return sensor;
    // }
};

#endif
