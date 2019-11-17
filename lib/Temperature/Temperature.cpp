#include "Temperature.h"
#include <Config.h>
#include <OneWire.h>
#include <DS18B20.h>

OneWire oneWire(temperaturePin);
DS18B20 sensor(&oneWire);

void initTemperatureSensor()
{
    sensor.begin();
}

float getTempature()
{
    float temperature = -100.0;
    sensor.requestTemperatures();
    u_int attempts = 0;
    delay(200);
    while (!sensor.isConversionComplete() && attempts <= 4)
    {
        attempts++;
        delay(750);
        #if _DBG_
            Serial.print("Get temperature attempt:");
            Serial.println(attempts);
        #endif
    }
    if (attempts <= 4)
    {
        temperature = sensor.getTempC();
    }

#if _DBG_
    Serial.print("Current temperature is: ");
    Serial.println(temperature);
#endif
return temperature;
}
