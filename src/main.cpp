#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <map>

const char* ssid = "ESP32-AP";
const char* password = "12345678";

WebServer server(80);
const int LED_PIN = 13;

// 404; with default fallback from / to /index.html
void handleNotFound() {
  String path = server.uri();
  // File doesn't exist
  if (path != "/") {
    Serial.println("Not found: " + path);
    server.send(404, "text/plain", "Aint found shit");
  } else if (path == "/" && SPIFFS.exists("/index.html")) {
    // If URL is "/", serve index.html as fallback (like for /some/frontend/route)
    Serial.println("Redirect / to /index.html");
    File file = SPIFFS.open("/index.html", "r");
    server.sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
    server.streamFile(file, "text/html");
    file.close();
  } else {
    Serial.println("data/index.html missing");
    server.send(500, "text/plain", "index.html missing");
  }
}

void handleHeartbeat() {
  float value = analogRead(A0);
  // Serial.println("Request heartbeat");
  // Send some test data
  server.send(200, "text/plain", "..heartbeat.. analogRead(0)="+String(value)+", millis: "+millis());
}

void handleLEDOn() {
  Serial.println("handleLED: On");
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain", "true");
}

void handleLEDOff() {
  Serial.println("handleLED: Off");
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "false");
}

void handleAngle() {
  std::map<String, int> data;

  if (server.hasArg("plain")) {
    Serial.println("Plain body: " + server.arg("plain"));
  }

  // Loop through all URL query parameters
  int params = server.args();
  String json = "{";
  for (int i = 0; i < params; i++) {
    String key = server.argName(i);
    // String value = server.arg(i);
    int value = server.arg(i).toInt();
    data[key] = value;
    Serial.printf("Param: %s = %d\n", key.c_str(), value);
    // Build JSON manually
    json += "\"" + key + "\":" + String(value);
    if (i < params - 1) json += ",";
  }
  json += "}";

  // Return OK
  // server.send(200, "text/plain", "OK");

  // Return a JSON
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  // Serial.println(WiFi.softAPIP());

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  } else {
    Serial.println("SPIFFS Mount Succeeded");
  }

  // Custom endpoints
  server.on("/heartbeat", handleHeartbeat);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);
  server.on("/setAngle", handleAngle);  // with URL params /setAngle?x=66&y=1&n=..
  server.onNotFound(handleNotFound);

  // Serve the rest as static files from SPIFFS automatically
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

void loop() {
  server.handleClient();
}
