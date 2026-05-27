#pragma once

#include <Arduino.h>

class StatusLED {
public:
    StatusLED(uint8_t bluePin, uint8_t redPin);

    void begin();

    void setFault(bool state);

    void update();

private:
    uint8_t _bluePin;
    uint8_t _redPin;

    bool _fault = false;

    unsigned long _timer = 0;
    bool _blinkState = false;
};