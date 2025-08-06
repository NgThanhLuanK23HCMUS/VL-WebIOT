#include "Buzzer.h"
#include <driver/ledc.h>



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


void Buzzer::playTone(int frequency) {
    tone(pin, frequency);

}

void Buzzer::stopTone() {
    noTone(pin);

}

