# ESP8266-FastLED-IoT-Webserver

This document describes the necessary steps from setting up the development environment to uploading the compiled software to the esp8266.

ESP32 currently got experimental support.

## Dependencies
* esp8266 and esp32 libs have to be installed via board manager
* alle other libs need to be installed via library manager

|Name|Version|Type|Comment|
|----|-------|----|-------|
esp8266|2.7.4|required|esp8266 Core Library if ESP8266 board is used
esp32|1.0.4|required|esp32 Core Library if ESP32 board is used
FastLED|3.4.0|required|LED animation library
WiFiManager|2.0.3-alpha|required|easy WiFi setup integration
Espalexa|2.5.0|optional|library for Alexa integration
PubSubClient|2.8.0|optional|for MQTT/Homeassistant support
ArduinoJson|6.17.2|optional|for MQTT/Homeassistant support
ArduinoOTA|1.0.5|optional|library and Python 2.7 for wireless firmware updating
Homeyduino|1.0.2|optional|for Homey Integration support

#### Sketch-Data-Uploader
* ESP8266-FS: [0.5.0+](https://github.com/esp8266/arduino-esp8266fs-plugin/releases)
* ESP32-FS: [1.0+](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)

Recommended if desired\
[IoT-Audio-Visualization-Center](https://github.com/NimmLor/IoT-Audio-Visualization-Center), Windows Application to sync the LEDs with music

**The software can be found on [GitHub](https://github.com/NimmLor/esp8266-fastled-iot-webserver).**

For beginners I would recommend watching this setup tutorial below.

The video wasn't updated for the new update, so the library versions are incorrect and the config area looks different.

[![](http://img.youtube.com/vi/d-uNkFHoMHc/0.jpg)](http://www.youtube.com/watch?v=d-uNkFHoMHc "Setup Tutorial")

## 1. Development environment

1. The code requires a recent version of the **Arduino IDE**, which can be downloaded [here]( https://www.arduino.cc/en/Main/Software ).

2. The ESP8266 / ESP32 boards need to be added to the Arduino IDE:\
   Click on *File >> Preferences* and paste the following URL into the **Additional Boards Manager URLs** field: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`\
   In case you you want to use a ESP32 base board you need to add following URL as well (comma separated) `https://dl.espressif.com/dl/package_esp32_index.json`
   
   ![](software_screenshots/board_manager_urls.png?raw=true)

3. Install the CH340/341 USB Driver (only needed if your computer doesn't recognize your board by default)
   
   - Download and install the driver from e.g. [Arduined]( https://www.arduined.eu/ch340-windows-8-driver-download/ )

4. The Boards need be installed in the Arduino IDE\
   Click on *Tools >> Board >> Boards Manager* and install **esp8266** or **esp32** for ESP32 boards
   
   ![](software_screenshots/board_manager.png?raw=true)

5. The LED Library **FastLED** is also required\
   Click on *Sketch >> Include Library >> Manage Libraries* and install **FastLED**
   
   ![](software_screenshots/FastLED.png?raw=true)
   
6. Install the **WiFiManager by tzapu**
   Click on *Sketch >> Include Library >> Manage Libraries* and install **WiFiManager by tzapu**
   
   ![](software_screenshots/wifi-manager.jpg?raw=true)

7. Install the  *ESP8266FS* or *ESP32* **Sketch Data Upload Tool**: 

   > - Download the tool:
   >   * ESP8266: https://github.com/esp8266/arduino-esp8266fs-plugin/releases.
   >   * ESP32: https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/
   >
   > - In your Arduino sketchbook directory, create `tools` directory if it doesn't exist yet
   >
   > - Unpack the tool into `tools` directory (the path will look like `/Arduino/tools/ESP8266FS/tool/esp8266fs.jar` or `/Arduino/tools/ESP32FS/tool/esp32fs.jar`)
   >
   > - Restart Arduino IDE


8. *(Optional)* Install *Espalexa* for Amazon Alexa Support
   Click on *Sketch >> Include Library >> Manage Libraries* and install **Espalexa**
   
   ![](software_screenshots/espalexa.png?raw=true)

9. *(Optional)* Install ArduinoOTA for flashing the ESP8266 via WiFi (requires Python 2.7)
   Click on *Sketch >> Include Library >> Manage Libraries* and install **ArduinoOTA**

   ![](software_screenshots/ota.png?raw=true)
   
10. (Optional) Install Python for OTA and add it to Path, afterwards restart your PC

![](https://cdn.shopify.com/s/files/1/1509/1638/files/install_python_for_windows_customize_add_to_path.png?88791)

11. *(Optional)* Install PubSubClient and ArduinoJson for MQTT/Homeassistant support\
    Click on *Sketch >> Include Library >> Manage Libraries* and install *PubSubClient* and *ArduinoJson*

   ![](software_screenshots/mqtt.png?raw=true)
 
   ![](software_screenshots/arduinoJson.png?raw=true)



## 2. Software setup

### 2.1 General configuration

1. Download the Project from the [Releases on Github]( https://github.com/NimmLor/esp8266-fastled-iot-webserver/releases ) and extract the archive

2. Open the **.ino** file inside the folder in the Arduino IDE

3. **Secrets.h was replaced by WiFiManager**

4. Configure the main parameters
   In the esp8266-fastled-iot-webserver.ino file there are many parameters to change and tweak the essential settings are:
- `LED_TYPE`: The type of LED strip that is used (WS2812B, APA102, ...)
- `DATA_PIN`: The pin where the LED-Strip is connected
- `CLK_PIN`:  Additional clock pin when using LED-Strips with 4 pins.
  *Note: If you are using another controller such as a clone or a NodeMCU board, you may need to configure the pin assignment for FastLED, See also [this entry in the FastLED Wiki](https://github.com/FastLED/FastLED/wiki/ESP8266-notes))*
- `CORRECTION`: Affects color calibration, if colors appear weird, you might want to use `TypicalLEDStrip`
- `COLOR_ORDER`:  Ordering of the colors sent, **depends on the LED-Strip**, if colors are swapped, then swap the Letters (RGB, RBG, GRB, GBR, BRG, BGR)
- `MILLI_AMPS`: How much current your power supply can handle in mA
- `VOLTS`: How much voltage your power supply delivers in Volts
- **Important**: `LED_DEVICE_TYPE` defines what device you are using, see the list below the code and choose the number

![](software_screenshots/config.png?raw=true)



### 2.2 Device configuration

#### 2.2.1 [0] Generic LED-Strip

Use this type when it is used as a regular LED strip, or if it used as an DIY-Ambilight.

Parameters:

- `NUM_LEDS`: The amount of LEDs on the LED-Strip
- `BAND_GROUPING`: The size of an LED group that received a packet, 
  - **The number of LEDs must be divisible by the specified value without remainder!**
  - Choose a value that results in a group size between 15 and 40
  - Use this when using 50 LEDs+
  - Example: *120 LEDs / 6 Grouping = 20*

#### 2.2.2 [1] LED-Matrix

This type is created for LED-matrices that have LEDs arranged in alternating directions after every column.

Parameters:

- `LENGTH`: Amount of columns
- `HEIGHT`: Amount of rows
- `AddLogoVisualizers`: Adds special patterns with the [HBz](https://www.youtube.com/channel/UCj6ljqIWs4Sfk3TBIn1xP6Q) Logo

#### 2.2.3 [2] 7-Segment Clock

This type is used for the [small](https://www.thingiverse.com/thing:3117494) or [large](https://www.thingiverse.com/thing:2968056) 7-segment clock. It uses an additional NTP time server to get an accurate time.

Parameters:

- `NTP_REFRESH_INTERVAL_SECONDS`: Interval for re-syncing the time with the NTP server
- `ntpServerName`: Address of the NTP-Server
- `t_offset`: additional offset that is added to the time
- `NUM_LEDS`: The total amount of LEDs used
- `DigitX:` Starting position of each segment

#### 2.2.4 [3] Desk Lamp

This type is used for the [twisted](https://www.thingiverse.com/thing:4129249) or [round](https://www.thingiverse.com/thing:3676533) desk lamp. The animation were adapted to appear correct on the lamp due to the alternating directions.

Parameters:

- `LINE_COUNT`: Amount of the LED strip lines, (with the provided cores it's 8)
- `LEDS_PER_LINE`: Amount of the LEDs inside one triangle

#### 2.2.4 [4] Nanoleaf Replica

This type is used for the [3D-Printed Nanoleafs](https://www.thingiverse.com/thing:3354082). The animation were adapted to appear correct on the triangles.

Parameters:

- `LEAFCOUNT`: Amount of the LED strip lines, (with the provided cores it's 8)
- `PIXELS_PER_LEAF`: Amount of the LEDs per strip

#### 2.2.5 [5] Animated RGB-Logos

This type is used for the [Twenty-One-Pilots](https://www.thingiverse.com/thing:3523487) or the [Thingiverse](https://www.thingiverse.com/thing:3531086) animated RGB-Logo.

Remove the "//" in front of the defines to choose the logo. 

Look for *ANIMATED RGB LOGO CONFIG* further down the code for configuration.

### 2.3 Feature configuration

#### 2.3.1 Overview

- **ENABLE_OTA_SUPPORT**: Enables the user to update the firmware wireless
- **ENABLE_MULTICAST_DNS**: allows to access the UI via "http://<HOSTNAME>.local/"
- **RANDOM_AUTOPLAY_PATTERN**: plays patterns at random in autoplay mode
- **AUTOPLAY_IGNORE_UDP_PATTERNS**: removes patterns that rely on incoming data
- **ENABLE_ALEXA_SUPPORT**: Allows to control the LEDs via Amazon Alexa
- **SOUND_SENSOR_SUPPORT**: (LEGACY!) Allows to control the LEDs via a physical sound sensor
- **ENABLE_SERIAL_AMBILIGHT**: Allows to be connected to a [Lightpack](https://github.com/psieg/Lightpack) (Windows, free) or  [Ambient light Application for Android](https://play.google.com/store/apps/details?id=com.sevson.androidambiapp&hl=de_AT) (Android Smart TVs, 2,79€)
- **ENABLE_MQTT_SUPPORT**: allows integration in homeassistant, requires MQTT server
- **ENABLE_UDP_VISUALIZATION**: Enables patters used for visualization via [IoT-Audio-Visualization-Center](https://github.com/NimmLor/IoT-Audio-Visualization-Center)
- **ENABLE_HOMEY_SUPPORT**: enables support for integration with a Homey hub


#### 2.3.2 OTA support

- Requires the ArduinoOTA library and a Python 2.7 installation
- Read [this](https://randomnerdtutorials.com/esp8266-ota-updates-with-arduino-ide-over-the-air/) article for further information
- When the OTA button on the UI or the desktop app is clicked it should show up in the ports menu

![](software_Screenshots/ota.png?raw=true)


#### 2.3.3 Alexa integration

6. Requires the **Espalexa** library

- Configuration of addition Devices

  - In order to control more parameters, the code allows to create additional devices that control, for instance a specific pattern or the autoplay functionality
  - The specific pattern refers to the zero-based index of the patterns array, just count up to your desired pattern, ignore patterns that are commented out or aren't affected by the `LED_DEVICE_TYPE`
  - To make use of these features remove the `//` in front of the `#define ...` 

![](software_screenshots/alexa_config.png?raw=true)


#### 2.3.4 MQTT integration

- Installation of "PubSubClient" and "ArduinoJson" libraries required
- Requires `ENABLE_MQTT_SUPPORT`
- It's preconfigured for Home Assistant Mosquitto MQTT service
- Enables sync with home assistant and from there to Google Assistant

#### 2.3.5 Homey integration

- Installation of "Homeyduino" library required
- Requires `ENABLE_HOMEY_SUPPORT`
- Enables integration with homey pod

## 3. Upload

### 3.1 Software upload

1. Configure the upload settings in **Tools** menu, there are **3 essential settings**
   - **Board: LOLIN(WEMOS) D1 R2 & mini**: when using the recommended Wemos D1 Mini
   - **Flash Size: "4MB (FS:1MB OTA:~1019KB)"**
   - **Port:** COMxx, if there are multiple ports, then replug your esp8266 to find the correct port. (*Note:* COM1 is usually your PCs internal parallel port and not the esp8266)

![](software_screenshots/upload_settings.png?raw=true)

2. Hit the **Upload** button to upload the code

![upload_button](software_screenshots/upload_button.png?raw=true)



### 3.2 Sketch-Data upload

This step is essential, it uploads the files for the UI (Html, JS, CSS, Icons), if it is skipped the server will just show "not found :/"
Click on *Tools >> ESP8266 Sketch Data Upload*

![](software_screenshots/data_upload.png?raw=true)



### 3.3 Connecting to the esp8266

1. The ESP should open an access point with the hostname, connect to it

2. Open **192.168.4.1** in your browser of choice

3. Connect to your WiFi

![ESP8266 WiFi Captive Portal Homepage](http://i.imgur.com/YPvW9eql.png) ![ESP8266 WiFi Captive Portal Configuration](http://i.imgur.com/oicWJ4gl.png)

4. Connect to the UI in your selected network by opening `http://<IP-ADDRESS>/` in your browser of choice. If mDNS was enabled, you should be able to access the UI via `http://<Hostname>.local/`



## 4. Alexa configuration

The connect your esp8266, the "Pairing-Mode" mode must be activated to add it to your Smart-Home devices in the alexa app.

Open http://ip_of_the_esp8266/alexa in your browser, the window should tell you that it is ready to be discovered by your alexa device.

**Important**: The esp8266 and you Amazon Echo device **must** be in the same network.

Just say to your echo, "Alexa, discover devices". This phrase can be spoken out in English on any echo device independent of the device's language.

After around 30 seconds, Alexa should respond with the devices that were found. These should show up in the Alexa app.


![](software_screenshots/app.png?raw=true)
