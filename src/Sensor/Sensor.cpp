#include "Sensor.h"

float Sensor::getTemperature()
{
    return this->temperature;
}

float Sensor::getHumidity()
{
    return this->humidity;
}

float Sensor::getSoilMoisture()
{
    return soilMoisture;
}

float Sensor::getLightLevel()
{
    return this->lightLevel;
}

bool Sensor::getIsOn()
{
    return this->isOn;
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

void Sensor::setSoilMoisture(const float &soilMoisture)
{
    this->soilMoisture = soilMoisture;
}

void Sensor::setLightLevel(const float &lightLevel)
{
    this->lightLevel = lightLevel;
}

void Sensor::setIsOn(const bool &isOn)
{
    this->isOn = isOn;
}
