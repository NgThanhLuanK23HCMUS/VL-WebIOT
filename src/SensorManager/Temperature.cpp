#include "Temperature.h"

void Temperature::readTemAndHum()
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
        sensor->setTemperature(temperature);
        sensor->setHumidity(humidity);
    }
}