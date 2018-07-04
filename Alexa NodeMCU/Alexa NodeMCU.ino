/* Home Automation With Alexa and ESP8266 / NodeMCU_CP2102_V2
Created by Exl Lab, 2018/07/04. Version 1.0

Note: Edit lines from  12 to 21 for your config.
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
fauxmoESP fauxmo;

// Wifi: SSID and password
const char* WIFI_SSID = "SSID";
const char* WIFI_PASSWORD = "password"; 

// Device Names:
const char* Device_Name_1 = "Light one";
const char* Device_Name_2 = "Light two";

// select pin on ESP/NodeMCU to control Relay
const byte RelayPin_1 = 14; //D5 - GPIO14
const byte RelayPin_2 = 12; //D6 - GPIO12


void setup() 
{
   Serial.begin(115200);
   //setup and wifi connection
   wifiSetup();
 
   //Set relay pins to outputs
   pinMode(RelayPin_1, OUTPUT);
   pinMode(RelayPin_2, OUTPUT);


   //Set each relay pin to HIGH 
   digitalWrite(RelayPin_1, HIGH);   
   delay(500);
   digitalWrite(RelayPin_2, HIGH);  
   delay(500);
    
   // Device Names for Simulated Wemo switches
   fauxmo.addDevice(Device_Name_1);
   fauxmo.addDevice(Device_Name_2);
   fauxmo.onMessage(callback); 
}

void loop() 
{
  fauxmo.handle();
}

 // Device Callback
void callback(uint8_t device_id, const char * device_name, bool state) 
{
 
  //Switching action on detection of device name
  //RelayPin_1:
  if (String(Device_Name_1).equals(device_name)) {
    if (!state) {
      digitalWrite(RelayPin_1, HIGH);
	    Serial.println(String(Device_Name_1) + " is OFF - line 61");
    } 
    else {
      digitalWrite(RelayPin_1, LOW);
	    Serial.println(String(Device_Name_1) + " is ON - line 65");
    }
  }
  //RelayPin_2:
  if (String(Device_Name_2).equals(device_name)) { 
    if (!state) {
      digitalWrite(RelayPin_2, HIGH);
	    Serial.println(String(Device_Name_2) + " is OFF - line 72");
    } 
    else {
      digitalWrite(RelayPin_2, LOW);
	    Serial.println(String(Device_Name_2) + " is ON - line 76");
    }
  }
}
    
void wifiSetup() 
{
   // Set WIFI module to STA mode
   WiFi.mode(WIFI_STA);

   // Connect
   Serial.println ();
   Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
   Serial.println();
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

   // Wait
   while (WiFi.status() != WL_CONNECTED) 
   {
      Serial.print(".");
      delay(100);
   }
   Serial.print(" ==> Wifi connected!" );
   Serial.println ();
}
