#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <map>
#include "components/Lamp.h"


class MqttHandler {
    private:
        String host,topicLed;
        uint16_t port;
        PubSubClient client;
        DynamicJsonDocument document = DynamicJsonDocument(512);
        std::map<String,Lamp> Lamps;
        void reconnect(const String &clientId);
        void handleLampObj(JsonObject object);
        void messageHandler(char *topic, byte *payload, unsigned int length);

    public:
        MqttHandler(const String host,uint16_t port,WiFiClient espClient,const String topicLed,std::map<String,Lamp> Lamps) :host{host.c_str()},port{port},client{espClient},topicLed{topicLed},Lamps{Lamps} { 
            client.setServer(this->host.c_str(),this->port); 
        };
        // Delete default constructor
        MqttHandler() = delete;

        // Builder class
        class Builder {
            private:
                String host;
                String topicLed;
                uint16_t port;
                WiFiClient* espClient = nullptr;
                std::map<String, Lamp> Lamps;

            public:
                // Setter for host
                Builder& setHost(const String& h) {
                    host = h;
                    return *this;
                }

                // Setter for port
                Builder& setPort(uint16_t p) {
                    port = p;
                    return *this;
                }

                // Setter for WiFiClient
                Builder& setEspClient(WiFiClient& client) {
                    espClient = &client;
                    return *this;
                }

                // Setter for topicLed
                Builder& setTopicLed(const String& t) {
                    topicLed = t;
                    return *this;
                }

                // Setter for Lamps
                Builder& setLamps(const std::map<String, Lamp>& lamps) {
                    Lamps = lamps;
                    return *this;
                }

                MqttHandler build() {
                    if (host.length() == 0 || port == 0 || espClient == nullptr || topicLed.length() == 0 || Lamps.empty()) {
                        Serial.println("Error: Missing parameters for MqttHandler.");
                        throw std::runtime_error("Error: Missing parameters for MqttHandler.");
                    }
                    return MqttHandler(host, port, *espClient, topicLed, Lamps);
                }
        };
        void setCallback();
        void connectToBroker();
        void connectToBroker(const String &username, const String &password);
        void loop();
};

#endif // MQTT_HANDLER_H