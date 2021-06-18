/*
   ESP8266 + FastLED + IR Remote: https://github.com/NimmLor/esp8266-fastled-iot-webserver
   Copyright (C) 2021 Ricardo Bartels

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// define EEPROM settings
// https://www.kriwanek.de/index.php/de/homeautomation/esp8266/364-eeprom-für-parameter-verwenden

#define CONFIG_SAVE_MAX_DELAY 10            // delay in seconds when the settings are saved after last change occured
#define CONFIG_COMMIT_DELAY   200           // commit delay in ms

typedef struct {
    uint8_t brightness;
    uint8_t currentPatternIndex;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t power;
    uint8_t autoplay;
    uint8_t autoplayDuration;
    uint8_t currentPaletteIndex;
    uint8_t speed;
    char hostname[33];
    uint8_t MQTTEnabled;
    char MQTTHost[65];
    uint16_t MQTTPort;
    char MQTTUser[33];
    char MQTTPass[65];
    char MQTTTopic[65];
    char MQTTSetTopic[65];
    char MQTTDeviceName[33];
} configData_t;

configData_t cfg;
configData_t default_cfg;

// save last "timestamp" the config has been saved
unsigned long last_config_change = 0;

void saveConfig(bool force = false) {

    if (last_config_change == 0 && force == false) {
        return;
    }

    static bool write_config = false;
    static bool write_config_done = false;
    static bool commit_config = false;

    if (force == true) {
        write_config = true;
        commit_config = true;
    }

    if (last_config_change > 0) {

        if (last_config_change + (CONFIG_SAVE_MAX_DELAY * 1000) < millis()) {

            // timer expired and config has not been written
            if (write_config_done == false) {
                write_config = true;

            // config has been written but we should wait 200ms to commit
            } else if (last_config_change + (CONFIG_SAVE_MAX_DELAY * 1000) + CONFIG_COMMIT_DELAY < millis()) {
                commit_config = true;
            }
        }
    }

    // Save configuration from RAM into EEPROM
    if (write_config == true) {
        SERIAL_DEBUG_LN(F("Saving Config"))
        EEPROM.begin(4095);
        EEPROM.put(0, cfg );
        write_config_done = true;
        write_config = false;
    }

    if (commit_config == true) {
        if (force == true) delay(CONFIG_COMMIT_DELAY);
        SERIAL_DEBUG_LN(F("Comitting config"))
        EEPROM.commit();
        EEPROM.end();

        // reset all triggers
        last_config_change = 0;
        write_config = false;
        write_config_done = false;
        commit_config = false;
    }
}

// trigger a config write/commit
void setConfigChanged() {
    // start timer
    last_config_change = millis();
}

// overwrite all config settings with "0"
void resetConfig() {

    // delete EEPROM config
    EEPROM.begin(4095);
    for (unsigned int i = 0 ; i < sizeof(cfg) ; i++) {
        EEPROM.write(i, 0);
    }
    delay(CONFIG_COMMIT_DELAY);
    EEPROM.commit();
    EEPROM.end();

    // set to default config
    cfg = default_cfg;
    saveConfig(true);
}

bool isValidHostname(char *hostname_to_check, long size) {
    for (int i = 0; i < size; i++) {
        if (hostname_to_check[i] == '-' || hostname_to_check[i] == '.')
          continue;
        else if (hostname_to_check[i] >= '0' && hostname_to_check[i] <= '9')
          continue;
        else if (hostname_to_check[i] >= 'A' && hostname_to_check[i] <= 'Z')
          continue;
        else if (hostname_to_check[i] >= 'a' && hostname_to_check[i] <= 'z')
          continue;
        else if (hostname_to_check[i] == 0 && i>0)
          break;

        return false;
    }

    return true;
}

// parse and set a new hostname to config
void setHostname(String new_hostname) {
    int j = 0;
    for (unsigned int i = 0; i < new_hostname.length() && i < sizeof(cfg.hostname); i++) {
        if (new_hostname.charAt(i) == '-' or \
           (new_hostname.charAt(i) >= '0' && new_hostname.charAt(i) <= '9') or \
           (new_hostname.charAt(i) >= 'A' && new_hostname.charAt(i) <= 'Z') or \
           (new_hostname.charAt(i) >= 'a' && new_hostname.charAt(i) <= 'z')) {

            cfg.hostname[j] = new_hostname.charAt(i);
            j++;
        }
    }
    cfg.hostname[j] = '\0';
    setConfigChanged();
}

// we can't assing wifiManager.resetSettings(); to reset, somewhow it gets called straight away.
void setWiFiConf(String ssid, String password) {
#ifdef ESP8266
    struct station_config conf;

    wifi_station_get_config(&conf);

    memset(conf.ssid, 0, sizeof(conf.ssid));
    for (int i = 0; i < ssid.length() && i < sizeof(conf.ssid); i++)
        conf.ssid[i] = ssid.charAt(i);

    memset(conf.password, 0, sizeof(conf.password));
    for (int i = 0; i < password.length() && i < sizeof(conf.password); i++)
        conf.password[i] = password.charAt(i);

    wifi_station_set_config(&conf);

// untested due to lack of ESP32
#elif defined(ESP32)
    if(WiFiGenericClass::getMode() != WIFI_MODE_NULL){

          wifi_config_t conf;
          esp_wifi_get_config(WIFI_IF_STA, &conf);

          memset(conf.sta.ssid, 0, sizeof(conf.sta.ssid));
          for (int i = 0; i < ssid.length() && i < sizeof(conf.sta.ssid); i++)
              conf.sta.ssid[i] = ssid.charAt(i);

          memset(conf.sta.password, 0, sizeof(conf.sta.password));
          for (int i = 0; i < password.length() && i < sizeof(conf.sta.password); i++)
              conf.sta.password[i] = password.charAt(i);

          esp_wifi_set_config(WIFI_IF_STA, &conf);
    }
#endif
}
// EOF
