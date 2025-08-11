#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>




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
