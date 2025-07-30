// GlobalSensorConfig.cpp
#include "globalSensorConfig.h"

Sensor* sensor = new Sensor("ESPPP");
SensorManager* tempAndHumSensor = new TemperatureAndHumiditySensor(DHTPIN, DHTTYPE, sensor);
SensorManager* soilSensor = new SoilMoistureSensor(PIN_SOIL_MOISTURE, sensor);
SensorManager* lightSensor = new LightSensor(PIN_LIGHT_SENSOR, sensor);
TrafficLight* trafficLight = new TrafficLight(RED, YELLOW, GREEN);