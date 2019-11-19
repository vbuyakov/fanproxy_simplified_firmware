#include <Arduino.h>
#include <Config.h>
#include <IotServer.h>
#include <FanMotor.h>
#include <Shutter.h>
#include <Temperature.h>


void setup() {
  initFanMotor();
  initTemperatureSensor();
  #if _DBG_
    Serial.begin(9600);
    Serial.print("Ready for Debug");
  #endif
  
  initIotServer();

}

void loop() {
  #if _USE_WIFI_SRV_
  iotHandleCLient();
  #endif
}