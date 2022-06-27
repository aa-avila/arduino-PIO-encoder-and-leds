#ifndef ledBasic_h
#define ledBasic_h

#include <Arduino.h>

class ledBasic {
   public:
    ledBasic(byte pin);
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