#ifndef temperature_h
#define temperature_h

#include <Config.h>
#include <OneWire.h>
#include <DS18B20.h>


void initTemperatureSensor();
float getTempature();
#endif
