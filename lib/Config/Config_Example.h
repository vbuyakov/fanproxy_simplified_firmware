#ifndef config_h
#define config_h
// IF True then log to serial 9600
#define _DBG_ true 
// IF True enable WiFi server
#define _USE_WIFI_SRV_ true

#include <WString.h>
#include <Arduino.h>

//Fan Motor
const int fanMotorPin = D5; // D6
// Shutter servo.
const int shuttersPins[] = {D0, D1};
// Temperature sensor pin
const int temperaturePin = D2;

//WiFi server setup
const String  ssid = "***";       // SSID Name
const String  password = "***";       // password
const String  iotServerToken = "***";      // This device access  token
const String  iotServerName = "IOT_Air_System";          // Host name of this Device, can be any
const String  srvIp = "192.168.xx.xx"; // where xx is the desired IP Address
const String  srvGateway = "192.168.0.1"; // set gateway to match your network
const String  srvSubnet ="255.255.255.0"; // set subnet mask to match your network
/**
 * For Servo i use FTP cable where:
 * orane, orange-white  - 5V
 * brown, brown-white,  green-white - GND
 * green - Signal
 * blue, blue-white - NC
 * */
#endif
