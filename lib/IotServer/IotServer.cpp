#include "IotServer.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <Config.h>
#include <FanMotor.h>
#include <Shutter.h>
#include <Temperature.h>

ESP8266WebServer server(80); // Iot web server

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

void handleOn()
{ // Switch ON fan motor
    if (checkAccess())
    {
        turnOnFanMotor();
        server.send(200, "text/plain", "success");
    }
}

void handleOff()
{ // Switch off fan motor
    if (checkAccess())
    {
        turnOffFanMotor();
        server.send(200, "text/plain", "success");
    }
}

void handleShutter()
{
    if (checkAccess())
    {
        const String angleParam = server.arg("angle");
        const int angle = angleParam.toInt();
        if (angle == 0 && angleParam != "0")
        {
            server.send(400, "text/plain", "Wrong value of angle, should be a number");
        }
        else if (angle < 0 || angle > 90)
        {
            server.send(400, "text/plain", "Wrong value of angle, should be more than 0 and less then 90");
        }
        else
        {
            setShutterPosition(angle);
            server.send(200, "text/plain", "success");
        }
    }
}

void iotHandleCLient()
{ //handleClient wrapper for root sketch
    server.handleClient();
}

void initIotServer()
{ //Init server
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

    // Set up routes
    server.on("/", handleRoot);
    server.on("/on", HTTP_GET, handleOn);
    server.on("/off", HTTP_GET, handleOff);
    server.on("/shutter", HTTP_GET, handleShutter); // Params angle - 0 -closed, 80 -opened
    server.on("/temperature", HTTP_GET, handleTemperature);
    server.onNotFound(handleNotFound);
    //Start server
    server.begin();
}
