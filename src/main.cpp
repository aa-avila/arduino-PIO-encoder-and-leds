#include <Arduino.h>
#include <Encoder.h>
Encoder encod(2, 3);
long newPosition = 0;
long oldPosition = 0;
long lastFullStepPos = 0;
bool fullStep = false;
enum Rotation {
    NONE,  // no rotation
    CWR,   // clockwise rotation
    CCWR   // counter-clockwise rotation
};
Rotation fullStepRot = NONE;
Rotation lastFullStepRot = NONE;

#include "ledBasic.h"
#define LED1_PIN 4
#define LED2_PIN 5
ledBasic led1(LED1_PIN);
ledBasic led2(LED2_PIN);

#include "ledPWM.h"
#define LED3_PIN 6
#define PWM_RANGE 255
ledPWM led3(LED3_PIN, PWM_RANGE);
int stepValuePwm = 1;

void setup() {
    Serial.begin(9600);
    Serial.println("Basic Encoder Test:");
    led1.init();
    led2.init();
    led3.init();
    led3.onNow();
}

void loop() {
    oldPosition = newPosition;
    fullStep = false;
    fullStepRot = NONE;
    newPosition = encod.read();
    if (newPosition != oldPosition) {
        Serial.println("****");
        Serial.println(newPosition);
        if (newPosition % 4 == 0) {
            if (newPosition != lastFullStepPos) {
                fullStep = true;
                lastFullStepPos = newPosition;
                if (newPosition < oldPosition) {
                    fullStepRot = CCWR;
                }
                if (newPosition > oldPosition) {
                    fullStepRot = CWR;
                }
                lastFullStepRot = fullStepRot;
            }
        }
    }

    if (fullStep) {
        // Serial.println("-----------");
        if (fullStepRot == CCWR) {
            Serial.println("Left - CCWR");
            led1.on();
            led2.off();
            led3.decrease(stepValuePwm);
        }
        if (fullStepRot == CWR) {
            Serial.println("Right - CWR");
            led2.on();
            led1.off();
            led3.increase(stepValuePwm);
        }
        Serial.println(newPosition);
        // Serial.println(led3.getValue());
        // Serial.println("-----------");
        // fullStep = false;
    }

    led1.update();
    led2.update();
    led3.update();
}