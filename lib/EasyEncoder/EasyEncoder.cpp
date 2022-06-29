#include "EasyEncoder.h"

#include <Arduino.h>

EasyEncoder::EasyEncoder() {
    long _newPosition = 0;
    long _oldPosition = 0;
    long _lastFullStepPos = 0;
    bool _isFullStep = false;
    bool _isAbsPosChange = false;
    DirectionOfRotation _fullStepDir = NO_R;
    DirectionOfRotation _lastFullStepDir = NO_R;
}

void EasyEncoder::tick(long newEncPos) {
    _oldPosition = _newPosition;
    _newPosition = newEncPos;
    _isFullStep = false;
    _fullStepDir = NO_R;
    _isAbsPosChange = false;

    if (_newPosition != _oldPosition) {
        _isAbsPosChange = true;
    }
    if (_isAbsPosChange && _newPosition % 4 == 0) {
        if (_newPosition != _lastFullStepPos) {
            if (_newPosition < _oldPosition) {
                _fullStepDir = CCW_R;
            }
            if (_newPosition > _oldPosition) {
                _fullStepDir = CW_R;
            }
            _isFullStep = true;
            _lastFullStepPos = _newPosition;
            _lastFullStepDir = _fullStepDir;
        }
    }
}
long EasyEncoder::absPos() {
    return _newPosition;
}
long EasyEncoder::lastAbsPos() {
    return _oldPosition;
}
long EasyEncoder::fullStepPos() {
    return _fullStepDir;
}
long EasyEncoder::lastFullStepPos() {
    return _lastFullStepPos;
}
bool EasyEncoder::isFullStep() {
    return _isFullStep;
}
bool EasyEncoder::isAbsPosChange() {
    return _isAbsPosChange;
}
DirectionOfRotation EasyEncoder::fullStepDir() {
    return _fullStepDir;
}
DirectionOfRotation EasyEncoder::lastFullStepDir() {
    return _lastFullStepDir;
}