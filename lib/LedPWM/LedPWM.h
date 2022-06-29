#ifndef LedPWM_h
#define LedPWM_h

#include <Arduino.h>

class LedPWM {
   public:
    LedPWM(byte pin, int range);
    void init();
    void on();
    void off();
    void toggle();
    bool getState();
    void setValue(int value);
    int getValue();
    void increase(int amount);
    void decrease(int amount);
    void maxValue();
    void update();
    void onNow();
    void offNow();
    void toggleNow();
    void setValueNow(int value);
    void increaseNow(int amount);
    void decreaseNow(int amount);
    void maxValueNow();

   private:
    byte _pin;
    int _range;
    int _pwmValue;
    bool _state;
};

#endif