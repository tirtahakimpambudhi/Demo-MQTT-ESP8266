# Demo MQTT ESP8266

This project demonstrates how to integrate the ESP8266 microcontroller with the MQTT protocol using a public broker to control an LED. The implementation utilizes PlatformIO as the development environment.

## Features

- **LED Control via MQTT**: Turn the LED on or off by sending a message to the `mqtt-esp8266/led` topic with a JSON payload `{ "id": int, "status": "ON" | "OFF" }`.
- **Public Broker Usage**: Utilizes a public MQTT broker for communication.
- **Development with PlatformIO**: Employs PlatformIO for project management and programming.

## Requirements

- **Hardware**:
  - ESP8266 NodeMCU
  - LED
  - Resistor (appropriate value for the LED)
  - Breadboard and jumper wires

- **Software**:
  - PlatformIO IDE
  - Internet connection to access the public MQTT broker

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/tirtahakimpambudhi/Demo-MQTT-ESP8266.git
   cd Demo-MQTT-ESP8266
   ```

2. **Open the Project with PlatformIO**:
   - Ensure [PlatformIO IDE](https://platformio.org/install) is installed.
   - Open this project directory with PlatformIO.

3. **Configure PlatformIO**:
   - Verify that the `platformio.ini` file is correctly set up for your ESP8266 board.

4. **Upload Code to ESP8266**:
   - Connect the ESP8266 to your computer.
   - Click the "Upload" icon in PlatformIO to flash the code to the device.

## Usage

1. **Hardware Connection**:
   - Connect the anode (long leg) of the LED to pin D1 (GPIO5) on the ESP8266 through a resistor.
   - Connect the cathode (short leg) of the LED to GND.

2. **Running the Device**:
   - Ensure the ESP8266 is connected to a Wi-Fi network with internet access.
   - Once connected, the ESP8266 will subscribe to the `mqtt-esp8266/led` topic on the public MQTT broker.

3. **Controlling the LED**:
   - Send a message to the `mqtt-esp8266/led` topic with the following JSON payload to turn the LED on:
     ```json
     {
       "id": 1,
       "status": "ON"
     }
     ```
   - To turn the LED off, change the `status` to `"OFF"`.

   You can use various MQTT clients to send these messages, such as [MQTT Explorer](http://mqtt-explorer.com/) , [MQTT.fx](https://mqttfx.jensd.de/) or [MQTT Cool](https://lightstreamer.com/products/mqtt-connector/).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

*Note: Ensure to replace placeholders like `YOUR_WIFI_SSID`, `YOUR_WIFI_PASSWORD`, and `broker_address` with the appropriate information before uploading the code to the device.* 
