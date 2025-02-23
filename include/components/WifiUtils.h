
#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <ESP8266WiFi.h>
#include <Arduino.h>

void connectWifi(const char* ssid,const char* password) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ");
    Serial.print(ssid);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

#endif // WIFI_UTILS_H