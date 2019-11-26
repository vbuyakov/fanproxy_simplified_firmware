#include "IotServer.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Config.h>
#include <Shutter.h>
#include <Relay.h>
#include <Temperature.h>

ESP8266WebServer server(80); // Iot web server
Shutters shutters;
Relays relays;

void initIotHardware() {
    shutters.init(shuttersPins);
    relays.init(relaysPins);
}

void handleRoot()
{ // empty request, for debug
    server.send(200, "text/plain", "Hello! I am " + iotServerName);
}

void handleNotFound()
{ // unknown requests
    server.send(404, "text/plain", "not found");
}

bool checkAccess()
{ // check  acess token
    String token = server.arg("token");
    if (iotServerToken != token)
    {
        server.send(401, "text/plain", "access denied");
        return false;
    }
    return true;
}

void handleTemperature()
{ // Get temperature
    if (checkAccess())
    {
        float temperature = getTempature();
        if (temperature > -100)
        {
            String temperatureStr = String(temperature, 2);
            server.send(200, "text/plain", temperatureStr);
        }
        else
        {
            server.send(500, "text/plain", "Temperature sensor timeout error");
        }
    }
}


void handleRelayRequest(uint8_t state) 
{
    uint8_t relayNumb = server.arg("relay").toInt();
    String errorMsg = "";
    if(relayNumb == 0) {
        relayNumb = 1;
    }

    if(errorMsg.length() == 0) {
        uint8_t res = relays.setStateOf(relayNumb, state);
        if(res == 0) {
            server.send(200, "text/plain", "success");
            return;
        } else {
            errorMsg += relays.getLastError();
        }
    }
    server.send(400, "text/plain", errorMsg);
}

void handleOn()
{ // Switch ON fan motor
    if (checkAccess())
    {
        handleRelayRequest(1);
    }
}

void handleOff()
{ // Switch off fan motor
    if (checkAccess())
    {
        handleRelayRequest(0);
    }
}

void handleShutter()
{
    if (checkAccess())
    {
        const String angleParam = server.arg("angle");
        const int angle = angleParam.toInt();

        const int shutterNumb = server.arg("shutter").toInt();

        String errorMsg = "";
        if (angle == 0 && angleParam != "0") {
            errorMsg += "Wrong value of angle, should be a number\n";
        }
        if(shutterNumb == 0) {
            errorMsg += "Wrong value of shuter, should be a number starting from 1\n";
        }

        if(errorMsg.length() == 0) {
            int res = shutters.setPostionOf(shutterNumb, angle);
            if(res == 0) {
                server.send(200, "text/plain", "success");
                return;
            } else {
                errorMsg += shutters.getLastError();
            }
        }
        server.send(400, "text/plain", errorMsg);
    }
}

void iotHandleCLient()
{ //handleClient wrapper for root sketch
    server.handleClient();
}

void initIotServer()
{ //Init server
    WiFi.mode(WIFI_STA);
    IPAddress ip;
    ip.fromString(srvIp);
    IPAddress gateway;
    gateway.fromString(srvGateway);
    IPAddress subnet;
    subnet.fromString(srvSubnet);
    WiFi.config(ip, gateway, subnet);
    WiFi.hostname(iotServerName);
    WiFi.begin(ssid.c_str(), password.c_str());

#if _DBG_
    Serial.printf("Connecting to %s ", ssid.c_str());
#endif
    // Wait  WiFi connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
#if _DBG_
        Serial.print(".");
#endif
    }
#if _DBG_
    Serial.println("Connected with IP address: ");
    Serial.println(WiFi.localIP());
#endif
    // Init hardware
    initIotHardware();

    // Set up routes
    server.on("/", handleRoot);
    /**
     * relay - number of relay, if not set number=1
     **/
    server.on("/on", HTTP_GET, handleOn);
    server.on("/off", HTTP_GET, handleOff);
    /**
     * angle - 0 -closed, 80 -opened
     * shutter - number of shutter
     **/
    server.on("/shutter", HTTP_GET, handleShutter);
    server.on("/temperature", HTTP_GET, handleTemperature);
    server.onNotFound(handleNotFound);
    //Start server
    server.begin();
}
