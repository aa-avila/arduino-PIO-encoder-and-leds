#ifndef EasyEncoder_h
#define EasyEncoder_h

#include <Arduino.h>

enum DirectionOfRotation {
    NO_R,  // no rotation
    CW_R,  // clockwise rotation
    CCW_R  // counter-clockwise rotation
};

class EasyEncoder {
   public:
    EasyEncoder();
    void init();
    void tick(long newEncPos);
    long absPos();
    long lastAbsPos();
    long fullStepPos();
    long lastFullStepPos();
    bool isFullStep();
    bool isAbsPosChange();
    DirectionOfRotation fullStepDir();
    DirectionOfRotation lastFullStepDir();

   private:
    long _newPosition;
    long _oldPosition;
    long _lastFullStepPos;
    bool _isFullStep;
    bool _isAbsPosChange;
    DirectionOfRotation _fullStepDir;
    DirectionOfRotation _lastFullStepDir;
};

#endif