#include "TemperatureAndHumiditySensor.h"



void TemperatureAndHumiditySensor::readSensorData()
{   
    //đọc dữ liệu từ cảm biến
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    if (!isnan(temperature) && !isnan(humidity)) {
        sensor->setHumidity(humidity);
        sensor->setTemperature(temperature);
    } else {
        Serial.println("Failed to read from DHT sensor!!!");
    }
}
