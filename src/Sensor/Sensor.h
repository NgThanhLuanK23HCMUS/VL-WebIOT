#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

class Sensor{
private:
    float temperature;
    float humidity;
    float soilMoisture;
    float lightLevel;

public:
    Sensor(){ 
        temperature = 0.0;
        humidity = 0.0;
        soilMoisture = 0.0;
        lightLevel = 0.0;
    }

    float getTemperature();
    float getHumidity();
    float getSoilMoisture();
    float getLightLevel();
    String getDeviceName();

    void setTemperature(const float& temperature);
    void setHumidity(const float& humidity);
    void setSoilMoisture(const float& soilMoisture);
    void setLightLevel(const float& lightLevel);
    ~Sensor(){}
};



#endif