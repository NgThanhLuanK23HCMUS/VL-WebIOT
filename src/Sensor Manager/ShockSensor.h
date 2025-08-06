#ifndef SHOCK_SENSOR_H
#define SHOCK_SENSOR_H

#include "./SensorManger.h"

class ShockSensor : public SensorManager {
private:
    uint8_t pin;
    bool isShock = false;
public:
    ShockSensor(uint8_t pin, Sensor* sensor)
        : SensorManager(sensor), pin(pin) {}

    void begin() override;
    bool getIsShock(){
        return this->isShock;
    }


    void readSensorData() override ;
};

#endif
