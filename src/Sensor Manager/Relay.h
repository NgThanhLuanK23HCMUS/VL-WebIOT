#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
class Relay {       
private:
    int pin;  
    bool isOn; 
public:
    Relay(int pin) : pin(pin), isOn(false) {

    }

    void turnOn() {
        digitalWrite(pin, HIGH);
    }

    void begin() {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW); // Bắt đầu với trạng thái tắt
    }
    void turnOff() {
        digitalWrite(pin, LOW);
    }

    bool getIsOn() const {
        return isOn;
    }

    void setIsOn(bool state) {
       this->isOn = state;
    }
};

#endif