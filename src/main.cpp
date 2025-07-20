// main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "server_handlers.h"

WebServer server(80);

#define LED_PIN 13

void setLED(boolean status) {
  digitalWrite(LED_PIN, status);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  setLED(true);
  setupServer();
}

void loop() {
  server.handleClient();
}
