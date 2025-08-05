#include "./SensorManger.h"

class Temperature : public SensorManager
{
    private:
        DHT dht;
    public:
        Temperature(uint8_t pin, uint8_t type)
        : dht(pin, type){}

        void begin() {
            dht.begin();
        }

        void readTemAndHum();
};

