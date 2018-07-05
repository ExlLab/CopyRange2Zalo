/* Home Automation With Alexa and ESP8266 / NodeMCU_CP2102_V2
Created by Exl Lab, 2018/07/04. Version 1.0

Note: Edit lines from  12 to 21 for your config.
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
fauxmoESP fauxmo;

// Wifi: SSID and password
const char *WIFI_SSID = "SSID";
const char *WIFI_PASSWORD = "password";

// Device Names:
const char *Device_Name_1 = "Light one";
const char *Device_Name_2 = "Light two";

// select pin on ESP/NodeMCU to control Relay
const byte RelayPin_1 = 14;  // D5 - GPIO14
const byte RelayPin_2 = 12;  // D6 - GPIO12

void setup() {
  Serial.begin(115200);
  // setup and wifi connection
  wifiSetup();

  // Register device info
  registerDevice(RelayPin_1, Device_Name_1);
  registerDevice(RelayPin_2, Device_Name_2);
  // Add new device here

  // Set callback function
  fauxmo.onMessage(callback);
}

void loop() {
  fauxmo.handle();  // fauxmo handle
}

// Device Callback
void callback(uint8_t device_id, const char *device_name, bool state) {
  // Switching action on detection of device name
  callbackDevice(Device_Name_1, device_name, RelayPin_1, state);  // RelayPin_1
  callbackDevice(Device_Name_2, device_name, RelayPin_2, state);  // RelayPin_2
  // Add new device here
}

void registerDevice(byte _Relay_Pin, char *_Device_Name) {
  // Set relay pins to outputs
  pinMode(_Relay_Pin, OUTPUT);

  // Set each relay pin to HIGH
  digitalWrite(_Relay_Pin, HIGH);

  // Device Names for Simulated Wemo switches
  fauxmo.addDevice(_Device_Name);
  delay(500);
}; 

void callbackDevice(char *_Device_Name, const char *_device, byte _Relay_Pin, bool _state) {
  if (!String(_Device_Name).equals(_device)) return;

  if (_state) {
    digitalWrite(_Relay_Pin, LOW); 
    Serial.println(String(_Device_Name) + " is ON");
    return;
  }

  digitalWrite(_Relay_Pin, HIGH);
  Serial.println(String(_Device_Name) + " is OFF");
};

void wifiSetup() {
  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.println();
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.print(" ==> Wifi connected!");
  Serial.println();
} 
