#include "TemperatureAndHumiditySensor.h"


void TemperatureAndHumiditySensor::readSensorData()
{
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!isnan(temp) && !isnan(hum)) {
        sensor->setTemperature(temp);
        sensor->setHumidity(hum);
    } else {
        Serial.println("Failed to read from DHT sensor!");
    }
}
