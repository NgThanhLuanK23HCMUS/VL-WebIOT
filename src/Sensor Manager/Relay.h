#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
class Relay {       
private:
    int pin;  
    bool isOn; 
public:
    void turnOff() {
        digitalWrite(pin, LOW);
    }

    Relay(int pin) : pin(pin), isOn(false) {

    }

    bool getIsOn() const {
        return isOn;
    }

    void turnOn() {
        digitalWrite(pin, HIGH);
    }

    void setIsOn(bool state) {
       this->isOn = state;
    }

    void begin() {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW); // Bắt đầu với trạng thái tắt
    }
};

#endif