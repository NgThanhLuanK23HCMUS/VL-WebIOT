#include "Buzzer.h"
#include <driver/ledc.h>

Buzzer::Buzzer(int pin) {
    this->pin = pin;
    this->isBeep = false;
}

void Buzzer::begin() {
    pinMode(pin, OUTPUT);
    ledcSetup(channel, 2000, 8);      // 2kHz, độ phân giải 8-bit
    ledcAttachPin(pin, channel);      // Gán pin vào channel PWM
}

void Buzzer::playTone(int frequency, int duration) {
    Serial.println(">>> playTone()");
    ledcWriteTone(channel, frequency);  // Phát âm ở tần số mong muốn

    if (duration > 0) {
        delay(duration);                // Giữ âm trong duration ms
        stopTone();                     // Tắt sau khi phát xong
    }
}

void Buzzer::stopTone() {
    Serial.println(">>> stopTone()");
    ledcDetachPin(pin);
    pinMode(pin, INPUT);  // Ngắt luôn → không cấp dòng điện nữa
}

bool Buzzer::getIsBeep() {
    return this->isBeep;
}

void Buzzer::setIsBeep(bool isBeep) {
    this->isBeep = isBeep;
}
