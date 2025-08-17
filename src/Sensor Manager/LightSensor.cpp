#include "LightSensor.h"
#include "../handler/handle.h"
void LightSensor::begin()
{
    pinMode(pin, INPUT);
}

void LightSensor::readSensorData()
{

        bool digitalValue = digitalRead(pin);
        trafficLight->setIsOpen(digitalValue);
}