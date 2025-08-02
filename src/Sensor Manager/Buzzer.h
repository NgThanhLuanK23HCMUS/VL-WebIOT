#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>

class Buzzer {
private:
    bool isBeep;
    int pin;
    int channel = 0;  // Dùng channel 0 cho PWM
public:
    Buzzer(int pin);
    void begin();
    void playTone(int frequency, int duration = 0);
    void stopTone();
    bool getIsBeep();
    void setIsBeep(bool isBeep);
};

#endif
