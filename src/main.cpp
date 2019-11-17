#include <Arduino.h>
#include <Config.h>
#include <IotServer.h>
#include <FanMotor.h>
#include <Shutter.h>
#include <Temperature.h>


void setup() {
  initFanMotor();
  initShutter();
  initTemperatureSensor();
  #if _DBG_
    Serial.begin(9600);
    Serial.print("Ready for Debug");
  #endif
  #if _USE_WIFI_SRV_
    initIotServer();
  #endif

}

void loop() {
  #if _USE_WIFI_SRV_
  iotHandleCLient();
  #endif
}