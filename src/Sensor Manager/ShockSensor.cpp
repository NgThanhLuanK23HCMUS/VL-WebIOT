#include "ShockSensor.h"

void ShockSensor::begin()
{
    pinMode(pin, INPUT);
}

int ShockSensor::getIsShock()
{
    return this->isShock;
}

void ShockSensor::setIsShock(int isShock)
{
    this->isShock = isShock;
}

void ShockSensor::readSensorData()
{
    isShock = digitalRead(pin);
}
