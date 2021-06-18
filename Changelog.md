# Changelog

## 4.5 - 14.02.2021, Config web page, ESP32 support, Homey integration

### Features:
- adds settings page to remove secrets.h and configure Wifi, hostname and MQTT settings #94
- Homey integration #117
- calculate delay per frame dynamically to keep frame rate steady #125
- adds Serial DEBUG mode and improves DEBUG information #124
- disable certain web interface controls if not available/used by pattern #92
- adds ESP32 support (experimental) #77
- adds more controls (speed/pattern/twinkle density) to more patterns #112
- UI / CSS Rework changes the sliders #132

### Bugfixes:
- fix compile errors when MQTT support was enabled #109
- fixes problem with UDP visualization not working #103
- fixes issue with unsaved config LEDs were power off #127
- fixes duplicate open SSID after wifiManager connected #135
- fixes random 4 seconds freezes #114
- fixes an compile error if LED_DEVICE_TYPE 5 was selected #73
- fixes Wifi setup if `LED_DEVICE_TYPE 2` was selected #100
- fixes HomeAssistant not recognizing separate esp boards #148
- Improve javascript console error logging #150

### House keeping:
- remove half integrated simple page #128
- remove unused "webSockets" support #130
- improves handling of config data written to EEPROM #121
- general code cleanup #129

### Documentation
- adds documentation of MQTT payload options #126, #137
- adds documentation of all URL endpoints and their options #147
- improves the list of dependencies and library versions #145

## 07.05.2020, Major Code rewrite and merge of projects, audio visualization

- **Audio Visualization with a Windows Desktop Application (C#, WPF)** [here](https://github.com/NimmLor/IoT-Audio-Visualization-Center)
- multicast DNS by @WarDrake
- OTA Support
- MQTT/Homeassistant integration by @WarDrake
- Serial Ambilight for usage behind a TV
- Support of Desk Lamp, 7-Segment Clock, Animated RGB Logos, Generic LED-Strip
- WebUI fits now on 1MB devices (esp-01)
- Dark mode for WebUI

## 01.02.2020, Native Alexa Update

- **NodeRED** part is now **DEPRECATED**
- The Nanoleaf Replica allows now for **NATIVE** Alexa support without the need of an extra Raspberry Pi. When added to the Smart Home devices in the Alexa app, the nanoleafs will appear as Phillips Hue devices.
- Added Strobe Pattern
- Added Sound Reactive support
- Some code cleanup and new parameters to configure
- New step by step installation instructions ([Software_Installation.md](Software_Installation.md))

## 24.02.2019, NodeRED Update (Deprecated)

- Node-RED integration was added
- Alexa support via NodeRED
