// GlobalSensorConfig.cpp
#include "globalSensorConfig.h"

// Sensor* sensor = new Sensor("ESP32  ");
// SensorManager* tempAndHumSensor = new TemperatureAndHumiditySensor(DHTPIN, DHTTYPE, sensor);
// SensorManager* soilSensor = new SoilMoistureSensor(PIN_SOIL_MOISTURE, sensor);
// SensorManager* lightSensor = new LightSensor(PIN_LIGHT_SENSOR, sensor);
// TrafficLight* trafficLight = new TrafficLight(RED, YELLOW, GREEN);
// Buzzer* buzzer = new Buzzer(PIN_BUZZER);

Sensor* sensor = nullptr;
SensorManager* tempAndHumSensor = nullptr;
SensorManager* soilSensor = nullptr;
SensorManager* lightSensor = nullptr;
TrafficLight* trafficLight = nullptr;

void initializeGlobalSensorConfig()
{
    sensor = new Sensor("ESP32");
    tempAndHumSensor = new TemperatureAndHumiditySensor(DHTPIN, DHTTYPE, sensor);
    soilSensor = new SoilMoistureSensor(PIN_SOIL_MOISTURE, sensor);
    lightSensor = new LightSensor(PIN_LIGHT_SENSOR, sensor);
    trafficLight = new TrafficLight(RED, YELLOW, GREEN);
}

