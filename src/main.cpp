// main.cpp
#include <WiFi.h>
#include <Arduino.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "server_handler.h"

WebServer server(80);

#define LED_PIN 13

void setLED(boolean status) {
  digitalWrite(LED_PIN, status);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  setupServer();
  setLED(true);
}

void loop() {
  server.handleClient();
}
