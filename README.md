# ESP8266 FastLED IoT Webserver

<a href="https://github.com/NimmLor/esp8266-fastled-iot-webserver/graphs/contributors" alt="Contributors"><img src="https://img.shields.io/github/contributors/NimmLor/esp8266-fastled-iot-webserver" /></a> <a href="https://github.com/NimmLor/esp8266-fastled-iot-webserver/releases" alt="Downloads"><img src="https://img.shields.io/github/downloads/NimmLor/esp8266-fastled-iot-webserver/total"/></a> <a href="https://github.com/NimmLor/esp8266-fastled-iot-webserver/commits/master" alt="Downloads"><img src="https://img.shields.io/github/commits-since/NimmLor/esp8266-fastled-iot-webserver/latest?include_prereleases" /></a> <a href="https://github.com/NimmLor/esp8266-fastled-iot-webserver/releases" alt="Downloads"><img src="https://img.shields.io/github/downloads-pre/NimmLor/esp8266-fastled-iot-webserver/latest/total?color=%09%23228B22&label=download%40latest-version" /></a>


This is a fork of [jasoncoon's esp8266 fastled webserver](https://github.com/jasoncoon/esp8266-fastled-webserver) that was adapted to control the colors of my  [LED-Projects](https://www.thingiverse.com/Surrbradl08/designs).

![Webinterface](web_ui.jpg?raw=true)

The web app is stored in SPIFFS (on-board flash memory) and has around 400kb. All stylsheets/js used are also stored in the spiffs, so no internet connection is required to view the webpage correctly.

**New:** Windows application to sync the LED devices with music. Completely optional but it's awesome. But it's just the first prototype and very experimental. Software and docs still work in progress.

https://github.com/NimmLor/IoT-Audio-Visualization-Center 

Can be downloaded [here](https://github.com/NimmLor/IoT-Audio-Visualization-Center/releases).

![screenshot_alpha](screenshot_alpha.jpg?raw=true)

https://github.com/NimmLor/IoT-Audio-Visualization-Center



## What happened here?

All of my recent project were merged into one including most of the features. A new and optional Windows application allows to sync the LEDs to a Windows audio source of your choice.



### Supported Devices

**Generic LED-Strip**, just a regular LED-Strip without special hardware

  * Easiest: 5V WS2812B LED-Strip:		https://s.click.aliexpress.com/e/_dZ1hCJ7
  * (Long Ranges) 12V WS2811 LED-Strip:	https://s.click.aliexpress.com/e/_d7Ehe3L
  * (High-Speed) 5V SK9822 LED-Strip:		https://s.click.aliexpress.com/e/_d8pzc89
  * (Expensive) 5V APA102 LED-Strip:		https://s.click.aliexpress.com/e/_Bf9wVZUD
  * (Flexible) 5V WS2812 S LED-Strip:		https://s.click.aliexpress.com/e/_d6XxPOH
  * Wemos D1 Mini:						https://s.click.aliexpress.com/e/_dTVGMGl
  * 5V Power Supply:						https://s.click.aliexpress.com/e/_dY5zCWt
  * Solderless LED-Connector:				https://s.click.aliexpress.com/e/_dV4rsjF
  * 3D-Printed Wemos-D1 case:				https://www.thingiverse.com/thing:3544576

**LED-Matrix**, with a flexible LED-Matrix you can display the audio like a Audio Visualizer
* Flexible WS2812 Matrix:				https://s.click.aliexpress.com/e/_d84R5kp
	
* Wemos D1 Mini:						https://s.click.aliexpress.com/e/_dTVGMGl
* 5V Power Supply:						https://s.click.aliexpress.com/e/_dY5zCWt
	

**3D-Printed 7-Segment Clock**, display the time, syncs with a ntp server of your choice

* unfortunately the "thing's" description isn't updated yet to the new standalone system
	
* Project link, small version:			https://www.thingiverse.com/thing:3117494
* Project link, large version:			https://www.thingiverse.com/thing:2968056

**3D-Printed Desk Lamp**, a lamp that reacts to sound for your desk

* Project link, twisted version:		https://www.thingiverse.com/thing:4129249
* Project link, round version:			https://www.thingiverse.com/thing:3676533

**3D-Printed Nanoleafs**, a Nanoleaf clone that can be made for cheap

* Project link:													https://www.thingiverse.com/thing:3354082
	

**3D-Printed Animated RGB Logos**, a small 3D-Printed logo that lights up with style

* Project link, Twenty-One-Pilots Logo:		https://www.thingiverse.com/thing:3523487
* Project link, Thingiverse Logo:			https://www.thingiverse.com/thing:3531086

**(soon) 3D-Printed Infinity Mirror**, a DIY infinity mirror inspired by Adafruit

* Project link, Sound Reactive Infinity Mirror:		https://www.thingiverse.com/thing:4461070

**3D-Printed IoT Bottle Lighting Pad**, a simple but smart lighting for any bottle you want.

* Project link, IoT Bottle Lighting Pad:		https://www.thingiverse.com/thing:4461313


Installation
--------
**FOR INSTALLATION REFER TO THE [Software_Installation.md](Software_Installation.md)**



Features
--------
* Turn the LEDs on and off
* Appear as an **ALEXA SMART HOME DEVICE**
* **Sound Reactive Mode**
* Adjust the brightness, color and patterns
* Play over 30+ patterns in Autoplay
* ESP32 support (experimental)



## Technical

Patterns are requested by the app from the ESP8266, so as new patterns are added, they're automatically listed in the app.

The web app is stored in SPIFFS (on-board flash memory).

The web app is a single page app that uses [jQuery](https://jquery.com) and [Bootstrap](http://getbootstrap.com).  It has buttons for On/Off, a slider for brightness, a pattern selector, and a color picker (using [jQuery MiniColors](http://labs.abeautifulsite.net/jquery-minicolors)).  Event handlers for the controls are wired up, so you don't have to click a 'Send' button after making changes.  The brightness slider and the color picker use a delayed event handler, to prevent from flooding the ESP8266 web server with too many requests too quickly.

The only drawback to SPIFFS that I've found so far is uploading the files can be extremely slow, requiring several minutes, sometimes regardless of how large the files are.  It can be so slow that I've been just developing the web app and debugging locally on my desktop (with a hard-coded IP for the ESP8266), before uploading to SPIFFS and testing on the ESP8266.



### Alexa

The code has an optional feature to be able to control the lamp via Alexa on any Amazon Echo device. For setup instructions refer to [Software_Installation.md](Software_Installation.md) document.



### Compression

The web app files can be gzip compressed before uploading to SPIFFS by running the following command:

`gzip -r data/`

The ESP8266WebServer will automatically serve any .gz file.  The file index.htm.gz will get served as index.htm, with the content-encoding header set to gzip, so the browser knows to decompress it.  The ESP8266WebServer doesn't seem to like the Glyphicon fonts gzipped, though, so I decompress them with this command:

`gunzip -r data/fonts/`

### REST Web services

The firmware implements basic [RESTful web services](https://en.wikipedia.org/wiki/Representational_state_transfer) using the ESP8266WebServer library.  Current values are requested with HTTP GETs, and values are set with POSTs using query string parameters.

#### URL Endpoints
|Endpoint|Method|Keys|Attribute|Description|
|--------|------|---|---------|-----------|
/config.json|GET|N/A|N/A|returns device config in JSON format
/reboot|GET/POST|N/A|N/A|reboots the device
/power|GET/POST|value|on, 1, 0, off, toggle|switch state of LEDs
/speed|GET/POST|value|0-255|set speed of pattern/effect
/brightness|GET/POST|value|0-255|set LED brightness
/solidColor|GET/POST|r,g,b|0-255 each|set RGB values for solid color
/hue|GET/POST|value|0-255|set hue: [FastLED HUE](https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors)
/saturation|GET/POST|value|0-255|set saturation
/patternName|GET/POST|value|pattern name|define a certain pattern, pattern names can be retreived via `/config.json` endpoint
/paletteName|GET/POST|value|palette name|defien a certain palette which is used by some effects, palette names can be retreived via `/config.json` endpoint
/autoplay|GET/POST|value|on, 1, 0, off, toggle|switch autoplay LED patterns on or off
/autoplayDuration|GET/POST|value|1-255|set time in seconds each pattern should be autoplayed
/twinkleDensity|GET/POST|value|0-255|set density of some twinkle effects
/cooling|GET/POST|value|0-255|set sparking intensity for `Fire` and `Water` pattern
/sparking|GET/POST|value|0-255|set cooling intensity for `Fire` and `Water` pattern
/reset|POST|type|wifi, all|wipe config just for `wifi` or `all` settings incl. wifi
/settings|POST|ssid|WiFi SSID|set a new WiFi SSID
/settings|POST|password|WiFi password|set a new WiFi password
/settings|POST|hostname|device hostname|set a new device hostname
/settings|POST|mqtt-enabled\*|1, 0|enable/disable MQTT support
/settings|POST|mqtt-hostname\*|hostname|set the hostname of the MQTT server to connect to
/settings|POST|mqtt-port\*|1-65535|set the MQTT port to connect to
/settings|POST|mqtt-user\*|a username|set the MQTT username to be used during MQTT connection
/settings|POST|mqtt-password\*|a password|set the MQTT password to be used during MQTT connection
/settings|POST|mqtt-topic\*|a topic|set the MQTT topic to be used during MQTT connection
/settings|POST|mqtt-device-name\*|device hostname|set the MQTT topic to be used during MQTT connection

>\* MQTT support has to be enabled during firmware build (disabled by default). All MQTT settings (except mqtt-enable) trigger a reboot

### MQTT Syntax

The MQTT integration by default sets up a light domain autodiscovery for home assistant, should you want to send MQTT commands from a different system or manually the syntax is as follows

**Topic :** MQTT_TOPIC / MQTT_TOPIC_SET  
example : "homeassistant/light/nanoleafs/set" in the case of the nanoleafs if you use default values, adjust for any changes you make to the previous two configuration variables  

**payload :** this is a json formatted string with parameters, you can send one or multiple parameters, please note that to change most of them the light must be on, so sending an on command on every request other than off is a good idea.  

**commands :**
|Key         |Value            |
|------------|-----------------|
|state       |on, off, toggle
|brightness  |1 to 255
|autoplay    |on, off, toggle
|speed       |1 to 255
|effect      |Pattern name as a quoted string.
|color       |[1..255,1..255,1..255]
|hue         |1 to 255
|saturation  |1 to 255

**command examples :**
|example                   |JSON payload|
|--------------------------|------------|
|turn lights on            |`{"state": "ON"}`
|turn lights off           |`{"state": "OFF"}`
|Set brightness to 50%     |`{"state": "ON", "brightness": 127}`
|Set animation speed to 16 |`{"speed": "16"}`
|Set animation autoplay on |`{"autoplay": "ON"}`
|Set animation pattern     |`{"state": "ON", "effect": "Sinelon"}`
|Set a solid color         |`{"state": "ON", "color": {"r": 72, "g": 255, "b": 163}}`

**You can combine multiple commands in a single payload, for example:**

Set lights on, with a brightness of 50%, animation speed of 25, animation autplay off and the pride pattern.
```json
{"state": "ON", "brightness": 127, "speed": "25", "autoplay": "OFF", "effect": "Pride"}
```