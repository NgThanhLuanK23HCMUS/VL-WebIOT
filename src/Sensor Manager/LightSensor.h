#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "./SensorManger.h"

class LightSensor : public SensorManager {
private:
    uint8_t pin;
    
public:
    LightSensor(uint8_t pin, Sensor* sensor)
        : SensorManager(sensor), pin(pin) {}

    void begin() override;

    void readSensorData() override ;
};

#endif
