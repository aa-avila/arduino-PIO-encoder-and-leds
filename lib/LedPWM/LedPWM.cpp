#include "LedPWM.h"

#include <Arduino.h>

LedPWM::LedPWM(byte pin, int range) {
    _pin = pin;
    _range = range;
    _pwmValue = 0;
    _state = false;
}

void LedPWM::init() {
    pinMode(_pin, OUTPUT);
    analogWrite(_pin, _pwmValue);
}

void LedPWM::on() {
    _state = true;
}

void LedPWM::off() {
    _state = false;
}

void LedPWM::toggle() {
    _state = !_state;
}

bool LedPWM::getState() {
    return _state;
}

void LedPWM::setValue(int value) {
    if (value < 0) {
        _pwmValue = 0;
    } else if (value > _range) {
        _pwmValue = _range;
    } else {
        _pwmValue = value;
    }
}

int LedPWM::getValue() {
    return _pwmValue;
}

void LedPWM::increase(int amount) {
    int newValue = _pwmValue + amount;
    setValue(newValue);
}

void LedPWM::decrease(int amount) {
    int newValue = _pwmValue - amount;
    setValue(newValue);
}

void LedPWM::maxValue() {
    _pwmValue = _range;
}

void LedPWM::update() {
    if (_state) {
        analogWrite(_pin, _pwmValue);
    } else {
        analogWrite(_pin, 0);
    }
}

void LedPWM::onNow() {
    on();
    update();
}

void LedPWM::offNow() {
    off();
    update();
}

void LedPWM::toggleNow() {
    toggle();
    update();
}

void LedPWM::setValueNow(int value) {
    setValue(value);
    update();
}

void LedPWM::increaseNow(int amount) {
    increase(amount);
    update();
}

void LedPWM::decreaseNow(int amount) {
    decrease(amount);
    update();
}

void LedPWM::maxValueNow() {
    maxValue();
    update();
}