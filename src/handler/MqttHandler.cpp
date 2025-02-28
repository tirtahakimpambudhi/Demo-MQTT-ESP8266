#include "handler/MqttHandler.h"
#include <chrono>

void MqttHandler::setCallback()
{
    client.setCallback(std::bind(&MqttHandler::messageHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
};

void MqttHandler::messageHandler(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message received [");
    Serial.print(topic);
    Serial.print("] ");

    String message = "";
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.println(message);

    if (String(topic) == this->topicLed)
    {
        DeserializationError error = deserializeJson(document, message);

        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        };
        if (document.is<JsonArray>())
        {
            Serial.println("Payload JSON Is Array");
            JsonArray array = document.as<JsonArray>();
            for (JsonObject object : array)
            {
                handleLampObj(object);
            };
            return;
        };

        if (document.is<JsonObject>())
        {
            Serial.println("Payload JSON Is Object");
            JsonObject object = document.as<JsonObject>();
            handleLampObj(object);
            return;
        }
    }
}

// Connect to MQTT broker
void MqttHandler::connectToBroker(const String &username, const String &password)
{
    const String clientId = "ESP8266Client-"+std::chrono::high_resolution_clock::now();
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT broker...");
        bool isConnected = client.connect(clientId.c_str(), username.c_str(), password.c_str());

        if (isConnected)
        {
            Serial.println("connected!");
            client.subscribe(topicLed.c_str());
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void MqttHandler::connectToBroker()
{
    const String clientId = "ESP8266Client-"+std::chrono::high_resolution_clock::now();
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT broker...");
        bool isConnected = client.connect(clientId.c_str());

        if (isConnected)
        {
            Serial.println("connected!");
            client.subscribe(topicLed.c_str());
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

// Handle MQTT client loop
void MqttHandler::loop()
{
    if (!client.connected())
    {
        reconnect("ESP8266Client-"+std::chrono::high_resolution_clock::now());
    }
    client.loop();
}

// Deserialization Lamp Object JSON
void MqttHandler::handleLampObj(JsonObject object)
{
    if (!object.containsKey("id") || !object.containsKey("status"))
    {
        Serial.println("Invalid JSON payload: Missing 'id' or 'status'");
        return;
    }

    int id = object["id"];
    String newStatus = object["status"].as<String>();

    auto it = this->Lamps.find(String(id));
    if (it == this->Lamps.end())
    {
        Serial.printf("Lamp ID %d not found.\n", id);
        return;
    }

    if (newStatus == "ON")
    {
        it->second.setValue(HIGH);
        Serial.printf("Lamp %d: ON\n", id);
    }
    else if (newStatus == "OFF")
    {
        it->second.setValue(LOW);
        Serial.printf("Lamp %d: OFF\n", id);
    }
    else
    {
        Serial.println("Unknown status received.");
    }
};

// Reconnect to MQTT broker if disconnected
void MqttHandler::reconnect(const String &clientId)
{
    Serial.println("Attempting MQTT reconnection...");
    while (!client.connected())
    {
        if (client.connect(clientId.c_str()))
        {
            Serial.println("Reconnected successfully");
            client.subscribe(topicLed.c_str());
        }
        else
        {
            Serial.print("Reconnection failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds...");
            delay(5000);
        }
    }
}