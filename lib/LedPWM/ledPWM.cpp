#include "ledPWM.h"

#include <Arduino.h>

ledPWM::ledPWM(byte pin, int range) {
    _pin = pin;
    _range = range;
    _pwmValue = 0;
    _state = false;
}

void ledPWM::init() {
    pinMode(_pin, OUTPUT);
    analogWrite(_pin, _pwmValue);
}

void ledPWM::on() {
    _state = true;
}

void ledPWM::off() {
    _state = false;
}

void ledPWM::toggle() {
    _state = !_state;
}

bool ledPWM::getState() {
    return _state;
}

void ledPWM::setValue(int value) {
    if (value < 0) {
        _pwmValue = 0;
    } else if (value > _range) {
        _pwmValue = _range;
    } else {
        _pwmValue = value;
    }
}

int ledPWM::getValue() {
    return _pwmValue;
}

void ledPWM::increase(int amount) {
    int newValue = _pwmValue + amount;
    setValue(newValue);
}

void ledPWM::decrease(int amount) {
    int newValue = _pwmValue - amount;
    setValue(newValue);
}

void ledPWM::maxValue() {
    _pwmValue = _range;
}

void ledPWM::update() {
    if (_state) {
        analogWrite(_pin, _pwmValue);
    } else {
        analogWrite(_pin, 0);
    }
}

void ledPWM::onNow() {
    on();
    update();
}

void ledPWM::offNow() {
    off();
    update();
}

void ledPWM::toggleNow() {
    toggle();
    update();
}

void ledPWM::setValueNow(int value) {
    setValue(value);
    update();
}

void ledPWM::increaseNow(int amount) {
    increase(amount);
    update();
}

void ledPWM::decreaseNow(int amount) {
    decrease(amount);
    update();
}

void ledPWM::maxValueNow() {
    maxValue();
    update();
}