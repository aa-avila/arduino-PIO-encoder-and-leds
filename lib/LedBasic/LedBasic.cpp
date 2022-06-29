#include "LedBasic.h"

#include <Arduino.h>

LedBasic::LedBasic(byte pin) {
    _pin = pin;
    _state = false;
}

void LedBasic::init() {
    pinMode(_pin, OUTPUT);
}

void LedBasic::on() {
    _state = true;
}

void LedBasic::off() {
    _state = false;
}

void LedBasic::toggle() {
    _state = !_state;
}

bool LedBasic::getState() {
    return _state;
}

void LedBasic::update() {
    if (_state) {
        digitalWrite(_pin, HIGH);

    } else {
        digitalWrite(_pin, LOW);
    }
}

void LedBasic::onNow() {
    on();
    update();
}

void LedBasic::offNow() {
    off();
    update();
}

void LedBasic::toggleNow() {
    toggle();
    update();
}