#include <Arduino.h>
#pragma once
#include <WebServer.h>

extern WebServer server;


void setupServer();
void handleHeartbeat();
void handleLEDOn();
void handleLEDOff();
void handleAngle();
void handleNotFound();
