
// define EEPROM settings
//  https://www.kriwanek.de/index.php/de/homeautomation/esp8266/364-eeprom-für-parameter-verwenden

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
  char MQTTDeviceName[33];
} configData_t;


configData_t cfg;
configData_t default_cfg;

// set to true if config has changed
bool save_config = false;


void saveConfig(bool save) {
    // Save configuration from RAM into EEPROM
    if (save == true) {
        EEPROM.begin(4095);
        EEPROM.put(0, cfg );
        delay(200);
        EEPROM.commit();
        EEPROM.end();

        save_config = false;
    }
}

void resetConfig() {

        // delete EEPROM config
        EEPROM.begin(4095);
        for (int i = 0 ; i < sizeof(cfg) ; i++) {
            EEPROM.write(i, 0);
        }
        delay(200);
        EEPROM.commit();
        EEPROM.end();

        // set to default config
        cfg = default_cfg;
        saveConfig(true);  
}

void setHostname(String new_hostname)
{
    int j = 0;
    for (int i = 0; i < new_hostname.length() && i < sizeof(cfg.hostname); i++) {
        if (new_hostname.charAt(i) == '-' or \
           (new_hostname.charAt(i) >= '0' && new_hostname.charAt(i) <= '9') or \
           (new_hostname.charAt(i) >= 'A' && new_hostname.charAt(i) <= 'Z') or \
           (new_hostname.charAt(i) >= 'a' && new_hostname.charAt(i) <= 'z')) {

            cfg.hostname[j] = new_hostname.charAt(i);
            j++;
        }
    }
    cfg.hostname[j] = '\0';
    save_config = true;
}
// EOF
