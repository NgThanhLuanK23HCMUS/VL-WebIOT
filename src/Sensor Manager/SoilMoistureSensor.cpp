#include "./SoilMoistureSensor.h"

void SoilMoistureSensor::readSensorData()
{
        int analogValue = analogRead(pin);
        float moisture = map(analogValue, 0, 4095, 100, 0); 
        sensor->setSoilMoisture(moisture);  
}