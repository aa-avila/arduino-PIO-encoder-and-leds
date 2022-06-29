#ifndef LedBasic_h
#define LedBasic_h

#include <Arduino.h>

class LedBasic {
   public:
    LedBasic(byte pin);
    void init();
    void on();
    void off();
    void toggle();
    bool getState();
    void update();
    void onNow();
    void offNow();
    void toggleNow();

   private:
    byte _pin;
    bool _state;
};

#endif