#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

class Sensor{
private:
    String device_name;
    float temperature;
    float humidity;
public:
    // Sensor(float temperature, float humidity) : temperature(temperature), humidity(humidity){ }
    Sensor(const String& device_name){this->device_name = device_name;}

    float getTemperature();
    float getHumidity();
    String getDeviceName();

    void setTemperature(const float& temperature);
    void setHumidity(const float& humidity);

    ~Sensor(){}
};



#endif