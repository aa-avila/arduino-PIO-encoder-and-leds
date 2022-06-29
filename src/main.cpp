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

// Ajustar curva de luminosidad y valores pwm por pasos
int pwmValues[] = {0, 1, 3, 6, 11, 19, 32, 53, 87, 110, 140, 180, 215, 255};
int pwmValuesLength = 14;
int indexPwm = 0;

int mapPwmIncrease(int val) {
    indexPwm = indexPwm + val;
    if (indexPwm > pwmValuesLength - 1) {
        indexPwm = pwmValuesLength - 1;
    }
    return pwmValues[indexPwm];
}
int mapPwmDecrease(int val) {
    indexPwm = indexPwm - val;
    if (indexPwm < 0) {
        indexPwm = 0;
    }
    return pwmValues[indexPwm];
}

// Interpolado
#include "LightChrono.h"
#define INTERPOLATE_TIME 10
int setPwmVal = 0;
int interPwmVal = 0;
int interpolateValue(int finalValue) {
    if (finalValue < interPwmVal) {
        interPwmVal--;
    } else if (finalValue > interPwmVal) {
        interPwmVal++;
    }
    return interPwmVal;
}

LightChrono interpolateTimer;

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

    if (enc.fullStepDir() == CCW_R) {
        Serial.println("Left - CCW_R");
        led1.on();
        led2.off();
        setPwmVal = mapPwmDecrease(1);
    }
    if (enc.fullStepDir() == CW_R) {
        Serial.println("Right - CW_R");
        led2.on();
        led1.off();
        setPwmVal = mapPwmIncrease(1);
    }

    if (interpolateTimer.hasPassed(INTERPOLATE_TIME, true)) {
        interPwmVal = interpolateValue(setPwmVal);
        led3.setValue(interPwmVal);
    }

    led1.update();
    led2.update();
    led3.update();
}