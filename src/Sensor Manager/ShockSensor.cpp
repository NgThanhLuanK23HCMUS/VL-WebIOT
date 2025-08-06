#include "ShockSensor.h"

void ShockSensor::begin()
{
    pinMode(pin, INPUT);
}

void ShockSensor::readSensorData()
{
    isShock = digitalRead(pin);
}
