// main.cpp
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "server_handlers.h"

WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  setupServer();
}

void loop() {
  server.handleClient();
}
