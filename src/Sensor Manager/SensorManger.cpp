#include "SensorManger.h"

void SensorManager::readTemAndHum()
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

        if (!isnan(temperature) && !isnan(humidity)) {
            sensor->setTemperature(temperature);
            sensor->setHumidity(humidity);
        }
}