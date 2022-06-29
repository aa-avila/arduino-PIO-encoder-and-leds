#include <Arduino.h>
#include <Encoder.h>
Encoder encoder(2, 3);
long newPosition = 0;
long oldPosition = 0;
long lastFullStepPos = 0;
bool fullStep = false;
enum DirectionOfRotation {
    NO_R,  // no rotation
    CW_R,  // clockwise rotation
    CCW_R  // counter-clockwise rotation
};
DirectionOfRotation fullStepRot = NO_R;
DirectionOfRotation lastFullStepRot = NO_R;

#include "LedBasic.h"
#define LED1_PIN 4
#define LED2_PIN 5
LedBasic led1(LED1_PIN);
LedBasic led2(LED2_PIN);

#include "LedPWM.h"
#define LED3_PIN 6
#define PWM_RANGE 255
LedPWM led3(LED3_PIN, PWM_RANGE);
int stepValuePwm = 1;

void setup() {
    Serial.begin(9600);
    Serial.println("---------------------");
    Serial.println("Basic Encoder Test:");
    led1.init();
    led2.init();
    led3.init();
    led3.onNow();
}

void loop() {
    oldPosition = newPosition;
    fullStep = false;
    fullStepRot = NO_R;
    newPosition = encoder.read();
    if (newPosition != oldPosition) {
        Serial.println("****");
        Serial.println(newPosition);
        if (newPosition % 4 == 0) {
            if (newPosition != lastFullStepPos) {
                if (newPosition < oldPosition) {
                    fullStepRot = CCW_R;
                }
                if (newPosition > oldPosition) {
                    fullStepRot = CW_R;
                }
                fullStep = true;
                lastFullStepPos = newPosition;
                lastFullStepRot = fullStepRot;
            }
        }
    }

    if (fullStep) {
        if (fullStepRot == CCW_R) {
            Serial.println("Left - CCW_R");
            led1.on();
            led2.off();
            led3.decrease(stepValuePwm);
        }
        if (fullStepRot == CW_R) {
            Serial.println("Right - CW_R");
            led2.on();
            led1.off();
            led3.increase(stepValuePwm);
        }
        Serial.println(newPosition);
    }

    led1.update();
    led2.update();
    led3.update();
}