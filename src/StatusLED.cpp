#include "StatusLED.h"

StatusLED::StatusLED(uint8_t bluePin, uint8_t redPin)
    : _bluePin(bluePin), _redPin(redPin) {}

void StatusLED::begin() {
    pinMode(_bluePin, OUTPUT);
    pinMode(_redPin, OUTPUT);

    digitalWrite(_bluePin, HIGH);
    digitalWrite(_redPin, HIGH);
}

void StatusLED::setFault(bool state) {
    _fault = state;
}

void StatusLED::update() {

    if (_fault) {
        digitalWrite(_bluePin, HIGH);
        digitalWrite(_redPin, LOW);
        return;
    }

    if (millis() - _timer > 500) {
        _timer = millis();

        _blinkState = !_blinkState;

        digitalWrite(_bluePin, _blinkState);
    }

    digitalWrite(_redPin, HIGH);
}