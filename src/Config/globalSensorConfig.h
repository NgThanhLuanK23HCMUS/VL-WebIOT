// GlobalSensorConfig.h
#ifndef GLOBAL_SENSOR_CONFIG_H
#define GLOBAL_SENSOR_CONFIG_H

#include "../Sensor/Sensor.h"
#include "../Sensor/Device.h"
#include "../Sensor Manager/SensorManger.h"
#include "../Sensor Manager/TemperatureAndHumiditySensor.h"
#include "../Sensor Manager/SoilMoistureSensor.h"
#include "../Sensor Manager/LightSensor.h"
#include "../Sensor Manager/TrafficLight.h"
#include "../Sensor Manager/Relay.h"
#include "../Sensor Manager/Buzzer.h"
#include "../Sensor Manager/ShockSensor.h"

#define DHTPIN 14
#define DHTTYPE DHT11
#define PIN_SOIL_MOISTURE 32
#define PIN_LIGHT_SENSOR 35
#define PIN_SHOCK_SENSOR 26
#define PIN_RELAY 33
#define PIN_BUZZER 27

#define RED 19
#define YELLOW 18
#define GREEN 5

extern Sensor* sensor;
extern Device* device;
extern SensorManager* tempAndHumSensor;
extern SensorManager* soilSensor;
extern SensorManager* lightSensor;
extern TrafficLight* trafficLight;
extern Relay* relay;
extern ShockSensor* shockSensor;
extern Buzzer* buzzer;

void initializeGlobalSensorConfig();
#endif
