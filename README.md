# esp32 WiFi Access Point & control with http requests
This is a boilerplate for controlling a ESP32 thing plus by Sparkfun (or other esp32 with a WIFI antenna) from your mobile.

Access the AP, visit a website, control the ESP32.

## Current functionalities
If you fetch any of these urls, an appropriate handler is called and will do stuff.
```
    /
    /heartbeat
    /led/on
    /led/off
    /setAngle?x=66
    /setAngle?y=270
    /setAngle?y=270&x=66
```

Other paths are treated as files (for isntance, `/style.css` or `script.js`)

## Flash + Upload website:
0. if any scripts running, close all previously running platformio actions
1. platformio plugin > "Upload Filesystem Image" (updates website in `/data`)
2. platformio plugin > "Upload and Monitor" (updates code in `/src` and shows monitoring log)