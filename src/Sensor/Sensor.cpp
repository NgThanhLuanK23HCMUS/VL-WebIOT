#include "Sensor.h"

float Sensor::getTemperature()
{
    return this->temperature;
}

float Sensor::getHumidity()
{
    return this->humidity;
}

String Sensor::getDeviceName(){
    return this->device_name;
}

void Sensor::setTemperature(const float &temperature)
{
    this->temperature =temperature;
}

void Sensor::setHumidity(const float &humidity)
{
    this->humidity = humidity;
}
