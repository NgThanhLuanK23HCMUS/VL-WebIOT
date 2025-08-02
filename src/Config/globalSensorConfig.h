// GlobalSensorConfig.h
#ifndef GLOBAL_SENSOR_CONFIG_H
#define GLOBAL_SENSOR_CONFIG_H

#include "../Sensor/Sensor.h"
#include "../Sensor Manager/SensorManger.h"
#include "../Sensor Manager/TemperatureAndHumiditySensor.h"
#include "../Sensor Manager/SoilMoistureSensor.h"
#include "../Sensor Manager/LightSensor.h"
#include "../Sensor Manager/TrafficLight.h"
// #include "../Sensor Manager/Buzzer.h"

#define DHTPIN 14
#define DHTTYPE DHT11
#define PIN_SOIL_MOISTURE 32
#define PIN_LIGHT_SENSOR 35
#define PIN_BUZZER 33
#define RED 5
#define YELLOW 18
#define GREEN 19

extern Sensor* sensor;
extern SensorManager* tempAndHumSensor;
extern SensorManager* soilSensor;
extern SensorManager* lightSensor;
extern TrafficLight* trafficLight;

void initializeGlobalSensorConfig();
// extern Buzzer* buzzer;
#endif
