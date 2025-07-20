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

Other paths are treated as files (for instance, `/style.css` or `script.js`)

Every static file is set to be non-caching for like less headache.

## Flash + Upload website:
0. if any platformio scripts are running, kill all of them
1. platformio plugin > "Upload Filesystem Image" (updates website in `/data`)
2. platformio plugin > "Upload and Monitor" (updates code in `/src` and shows monitoring log)

For debugging the website part, open `/data` in a new IDE window and start a development server there. Otherwise the absolute paths won't work while developing.
