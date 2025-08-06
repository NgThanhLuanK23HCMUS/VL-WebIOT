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
    bool isPlayingTone;

public:
    Buzzer(int pin) : pin(pin), isBeep(false), isPlayingTone(false)  {}

    void begin();

    void playTone(int frequency);

    void stopTone();


    bool getIsBeep();

    void setIsBeep(bool isBeep);

    bool getIsPlayingTone() {
        return isPlayingTone;
    }

    void setIsPlayingTone(bool val) {
        isPlayingTone = val;
    }
};

#endif
