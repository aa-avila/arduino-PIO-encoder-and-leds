#include <Arduino.h>

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

#include "EasyEncoder.h"
#include "Encoder.h"
#define ENC_PIN_A 2
#define ENC_PIN_B 3
Encoder encoder(ENC_PIN_A, ENC_PIN_B);
EasyEncoder enc;

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
    enc.tick(encoder.read());

    if (enc.isAbsPosChange()) {
        Serial.println("*******");
        Serial.println(enc.absPos());
    }

    if (enc.isFullStep()) {
        if (enc.fullStepDir() == CCW_R) {
            Serial.println("Left - CCW_R");
            led1.on();
            led2.off();
            led3.decrease(stepValuePwm);
        }
        if (enc.fullStepDir() == CW_R) {
            Serial.println("Right - CW_R");
            led2.on();
            led1.off();
            led3.increase(stepValuePwm);
        }
        Serial.println(enc.absPos());
    }

    led1.update();
    led2.update();
    led3.update();
}