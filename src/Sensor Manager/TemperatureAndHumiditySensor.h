#ifndef TEMPERATURE_AND_HUMIDITY_Sensor_H
#define TEMPERATURE_AND_HUMIDITY_Sensor_H

#include "./SensorManger.h"
#include <DHT.h>

class TemperatureAndHumiditySensor : public SensorManager {
private:
    DHT dht;
    uint8_t pin;
    uint8_t type;

public:
    TemperatureAndHumiditySensor(uint8_t pin, uint8_t type, Sensor* sensor)
        : SensorManager(sensor), dht(pin, type), pin(pin), type(type) {}

    void begin() override {
        dht.begin();
    }
    
    void readSensorData() override;
};

#endif
