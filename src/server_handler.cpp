// server_handlers.cpp
#include "server_handler.h"
#include "main.h"
#include <Arduino.h>
#include <SPIFFS.h>
#include <map>

const char *ssid = "ESP32-AP";
const char *password = "12345678";  // Please change me

void setupServer()
{
    WiFi.softAP(ssid, password);
    Serial.println("Access Point started");

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    } else {
        Serial.println("SPIFFS Mount Succeeded");
    }

    // Register custom handlers
    server.on("/heartbeat", handleHeartbeat);
    server.on("/led/on", handleLEDOn);
    server.on("/led/off", handleLEDOff);
    server.on("/setAngle", handleAngle);
    server.onNotFound(handleNotFound);

    // Serve static files from SPIFFS
    server.serveStatic("/", SPIFFS, "/");

    server.begin();

    Serial.println("HTTP server started.");
    Serial.println();
    Serial.println("--------------------------------");
    Serial.println("Access with mobile WiFi Hotspot:");
    Serial.println(ssid);
    Serial.println();
    Serial.println("with password:");
    Serial.println(password);
    Serial.println();
    Serial.println("And visit URL:");
    Serial.println(WiFi.softAPIP());
    Serial.println("--------------------------------");
}

void handleHeartbeat()
{
    float value = analogRead(A0);
    server.send(200, "text/plain", "..heartbeat.. analogRead(0)=" + String(value) + ", millis: " + String(millis()));
}

void handleLEDOn()
{
    Serial.println("handleLED: On");
    // digitalWrite(LED_PIN, HIGH);
    setLED(true);
    server.send(200, "text/plain", "true");
}

void handleLEDOff()
{
    Serial.println("handleLED: Off");
    // digitalWrite(LED_PIN, LOW);
    setLED(false);
    server.send(200, "text/plain", "false");
}

void handleAngle()
{
    std::map<String, int> data;
    int params = server.args();
    String json = "{";
    for (int i = 0; i < params; i++)
    {
        String key = server.argName(i);
        int value = server.arg(i).toInt();
        data[key] = value;
        Serial.printf("Param: %s = %d\n", key.c_str(), value);
        json += "\"" + key + "\":" + String(value);
        if (i < params - 1)
            json += ",";
    }
    json += "}";
    // Return OK
    // server.send(200, "text/plain", "OK");
    // Return a JSON
    server.send(200, "application/json", json);
}

void handleNotFound()
{
    String path = server.uri();
    if (path != "/")
    {
        Serial.println("Not found: " + path);
        server.send(404, "text/plain", "Aint found shit");
    }
    else if (path == "/" && SPIFFS.exists("/index.html"))
    {
        Serial.println("Redirect / to /index.html");
        File file = SPIFFS.open("/index.html", "r");
        server.sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
        server.streamFile(file, "text/html");
        file.close();
    }
    else
    {
        Serial.println("data/index.html missing");
        server.send(500, "text/plain", "index.html missing");
    }
}
