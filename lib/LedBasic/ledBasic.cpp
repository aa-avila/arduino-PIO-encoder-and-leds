#include "ledBasic.h"

#include <Arduino.h>

ledBasic::ledBasic(byte pin) {
    _pin = pin;
    _state = false;
}

void ledBasic::init() {
    pinMode(_pin, OUTPUT);
}

void ledBasic::on() {
    _state = true;
}

void ledBasic::off() {
    _state = false;
}

void ledBasic::toggle() {
    _state = !_state;
}

bool ledBasic::getState() {
    return _state;
}

void ledBasic::update() {
    if (_state) {
        digitalWrite(_pin, HIGH);

    } else {
        digitalWrite(_pin, LOW);
    }
}

void ledBasic::onNow() {
    on();
    update();
}

void ledBasic::offNow() {
    off();
    update();
}

void ledBasic::toggleNow() {
    toggle();
    update();
}