#ifndef SHOCK_SENSOR_H
#define SHOCK_SENSOR_H

#include "./SensorManger.h"

class ShockSensor : public SensorManager {
private:
    uint8_t pin;
    int isShock = 0;
public:
    ShockSensor(uint8_t pin, Sensor* sensor)
        : SensorManager(sensor), pin(pin) {}

    void begin() override;
    int getIsShock(){
        return this->isShock;
    }

    void setIsShock(int isShock) {
        this->isShock = isShock;
    }

    void readSensorData() override ;
    int readShockSensor() {
        return digitalRead(pin);
    }
};

#endif
