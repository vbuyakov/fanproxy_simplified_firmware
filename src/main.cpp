#include <Arduino.h>
#include <IotServer.h>
#include <Temperature.h>

void setup() {
  initTemperatureSensor();
  #if _DBG_
    Serial.begin(9600);
    Serial.print("Ready for Debug");
  #endif
  delay(1000);
  initIotServer();

}

void loop() {
  iotHandleCLient();
}