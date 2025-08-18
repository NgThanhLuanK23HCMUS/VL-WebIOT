// GlobalSensorConfig.cpp
#include "globalSensorConfig.h"



Sensor* sensor = nullptr;
Device* device = nullptr;
SensorManager* tempAndHumSensor = nullptr;
SensorManager* soilSensor = nullptr;
SensorManager* lightSensor = nullptr;
TrafficLight* trafficLight = nullptr;
Relay* relay = nullptr;
ShockSensor* shockSensor = nullptr;
Buzzer* buzzer = nullptr;

void initializeGlobalSensorConfig()
{
    sensor = new Sensor();
    device = new Device("1", "", "ESP32");
    soilSensor = new SoilMoistureSensor(PIN_SOIL_MOISTURE, sensor);
    tempAndHumSensor = new TemperatureAndHumiditySensor(DHTPIN, DHTTYPE, sensor);
    trafficLight = new TrafficLight(RED, YELLOW, GREEN);
    lightSensor = new LightSensor(PIN_LIGHT_SENSOR, sensor);
    relay = new Relay(PIN_RELAY);
    shockSensor = new ShockSensor(PIN_SHOCK_SENSOR, sensor);
    buzzer = new Buzzer(PIN_BUZZER);
}

