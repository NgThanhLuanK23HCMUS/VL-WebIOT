#ifndef SOIL_MOISTURE_Sensor_H
#define SOIL_MOISTURE_Sensor_H


#include "./SensorManger.h"

class SoilMoistureSensor : public SensorManager {
private:
    uint8_t pin;

public:
    SoilMoistureSensor(uint8_t pin, Sensor* sensor)
        : SensorManager(sensor), pin(pin) {}

    void begin() override {
        pinMode(pin, INPUT);
    }

    void readSensorData() override ;
};

#endif
