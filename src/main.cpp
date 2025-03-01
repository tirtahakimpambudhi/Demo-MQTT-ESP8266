#include "components/Lamp.h"
#include "components/WifiUtils.h"
#include "handler/MqttHandler.h"

MqttHandler mqtthandler;

void setup() {
    Serial.begin(9600);

    connectWifi("Testing","12345678");
    WiFiClient espClient;
    mqtthandler = MqttHandler::Builder()
    .setEspClient(espClient)
    .setHost("broker.mqtt.cool")
    .setTopicLed("mqtt-esp8266/led")
    .setLamps(std::map<String,Lamp>{
        { "1", Lamp(D1,LOW) },
        { "2", Lamp(D2,LOW) },
        { "3", Lamp(D3,LOW) },
        { "4", Lamp(D4,LOW) }
    })
    .setPort(1883)
    .build();

    mqtthandler.setCallback();
    mqtthandler.connectToBroker();
}


void loop() {
    mqtthandler.loop();
}