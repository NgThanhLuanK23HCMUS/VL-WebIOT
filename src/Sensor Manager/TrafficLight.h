#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <Arduino.h>

class TrafficLight {
private:
    int redPin;
    int yellowPin;
    int greenPin;

public:
    TrafficLight(int redPin, int yellowPin, int greenPin);

    void begin();  // thiết lập chế độ OUTPUT
    void turnRed();
    void turnYellow();
    void turnGreen();
    void turnOffAll();  // tắt tất cả
    void turnOnfAll();  // tắt tất cả

    ~TrafficLight() {}
};

#endif
