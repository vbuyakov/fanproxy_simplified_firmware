#include "Shutter.h"
#include <Config.h>
#include <Servo.h>

Servo servo;

void initShutter() {
    servo.attach(shutterServoPin);
}
void setShutterPosition(int pos){
    servo.write(pos);
    #if _DBG_
        Serial.print("Set shutter posintion to: ");
        Serial.println(pos);
    #endif
}