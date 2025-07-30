#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

class Sensor{
private:
    String device_name;
    float temperature;
    float humidity;
    float soilMoisture;
    float lightLevel;
    bool isOn = false;

public:
    Sensor(const String& device_name){this->device_name = device_name;}

    float getTemperature();
    float getHumidity();
    float getSoilMoisture();
    float getLightLevel();
    bool getIsOn();
    String getDeviceName();

    void setTemperature(const float& temperature);
    void setHumidity(const float& humidity);
    void setSoilMoisture(const float& soilMoisture);
    void setLightLevel(const float& lightLevel);
    void setIsOn(const bool& isOn);
    ~Sensor(){}
};



#endif