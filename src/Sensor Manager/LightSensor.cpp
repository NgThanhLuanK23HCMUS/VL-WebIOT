#include "LightSensor.h"

void LightSensor::begin()
{
    pinMode(pin, INPUT);
}

void LightSensor::readSensorData()
{
        // float analogValue = analogRead(pin);
        // float lightPercent = map(analogValue, 0, 4095, 0, 100); // 0 là tối, 100 là sáng
        // sensor->setLightLevel(analogValue);

        bool digitalValue = digitalRead(pin);
        sensor->setIsOn(digitalValue);
}