#include "Buzzer.h"
#include <driver/ledc.h>

// Buzzer::Buzzer(int pin) {
//     this->pin = pin;
//     this->isBeep = false;
// }

void Buzzer::begin() {
    pinMode(pin, OUTPUT);
    noTone(pin); 
}



bool Buzzer::getIsBeep() {
    return this->isBeep;
}

void Buzzer::setIsBeep(bool isBeep) {
    this->isBeep = isBeep;
}


void Buzzer::playTone(int frequency, int duration) {
    tone(pin, frequency, duration);

}

void Buzzer::stopTone() {
    noTone(pin);
    // isBeep = false;
    // currentDuration = 0;
}

