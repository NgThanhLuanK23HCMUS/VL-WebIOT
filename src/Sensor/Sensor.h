#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

class Sensor{
private:
    float temperature;
    float humidity;
    float soilMoisture;
    float lightLevel;

    float temperatureThreshold;
    float humidityThreshold;
    float soilThreshold;

public:
    Sensor(){ 
        temperature = 0.0;
        humidity = 0.0;
        soilMoisture = 0.0;
        lightLevel = 0.0;
        temperatureThreshold = 30.0; // Default threshold values
        humidityThreshold = 70.0;
        soilThreshold = 30.0;
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


    void setTemperatureThreshold(const float& threshold) {
        temperatureThreshold = threshold;
    }
    void setHumidityThreshold(const float& threshold) {
        humidityThreshold = threshold;
    }
    void setSoilThreshold(const float& threshold) {
        soilThreshold = threshold;
    }

    float getTemperatureThreshold() const {
        return temperatureThreshold;
    }

    float getHumidityThreshold() const {
        return humidityThreshold;
    }
    float getSoilThreshold() const {
        return soilThreshold;
    }
    ~Sensor(){}
};



#endif