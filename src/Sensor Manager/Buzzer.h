#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>

// class Buzzer {
// private:
//     bool isBeep;
//     int pin;
//     int channel = 0;  // Dùng channel 0 cho PWM
// public:
//     Buzzer(int pin);
//     void begin();
//     void playTone(int frequency, int duration = 0);
//     void stopTone();
//     bool getIsBeep();
//     void setIsBeep(bool isBeep);
// };


class Buzzer {
private:
    int pin;
    bool isBeep;
    unsigned long startTime;
    int currentDuration;

public:
    Buzzer(int pin) : pin(pin), isBeep(false), startTime(0), currentDuration(0) {}

    void begin();

    void playTone(int frequency, int duration);

    void stopTone();


    bool getIsBeep();

    void setIsBeep(bool isBeep);
};

#endif
