#pragma once
#include <WebServer.h>

extern WebServer server;

#define LED_PIN 13

void setupServer();
void handleHeartbeat();
void handleLEDOn();
void handleLEDOff();
void handleAngle();
void handleNotFound();
