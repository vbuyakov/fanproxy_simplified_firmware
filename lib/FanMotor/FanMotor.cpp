#include "FanMotor.h"
#include <Config.h>

void initFanMotor() {
    pinMode(fanMotorPin, OUTPUT);
    digitalWrite(fanMotorPin, HIGH);
}

void turnOnFanMotor() {
    digitalWrite(fanMotorPin, LOW);
    #if _DBG_
        Serial.println("ON / LOW");
    #endif
}

void turnOffFanMotor() {
    digitalWrite(fanMotorPin, HIGH);
    #if _DBG_
        Serial.println("OFF / HIGH");
    #endif
}