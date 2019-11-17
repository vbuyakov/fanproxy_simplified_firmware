#include "FanMotor.h"
#include <Config.h>

void initFanMotor() {
    pinMode(fanMotorPin, OUTPUT);
}

void turnOnFanMotor() {
    digitalWrite(fanMotorPin, HIGH);
    #if _DBG_
        Serial.println("ON / HIGH");
    #endif
}

void turnOffFanMotor() {
    digitalWrite(fanMotorPin, LOW);
    #if _DBG_
        Serial.println("OFF / LOW");
    #endif
}