# Interfacing ESP32 with MQTT

This program is designed for an **ESP32** to send the data to an MQTT server using Pub/Sub methods. The program connects to a Wi-Fi network, subscribes to an MQTT topic, and publishes the measured distance to a specified MQTT topic every 2 seconds.

Note: Here i'm using HCSR-04 just for demonstrate where and how to write the code to get the data from HCSR=04 before the data sent to MQTT. You can modify with any sensor you need.
### Features:
- **Wi-Fi Connectivity**: Connects the ESP32 to a Wi-Fi network.
- **MQTT Communication**: 
  - Publishes data readed from sensor.
  - Subscribes to an MQTT topic and prints received messages to the serial monitor.

### Hardware Required:
- **ESP32**
- **You also need MQTT broker, ex. Raspberry Pi with Mosquitto Installed and Configured**

### Configuration:
Before running the program, configure the following parameters:
- **Wi-Fi Credentials**: Replace `"ssid"` and `"password"` with your Wi-Fi network's credentials.
- **MQTT Server**: Set the IP address of your MQTT broker in the `mqtt_server` variable.
- **MQTT Authentication**: Optionally configure `mqtt_username` and `mqtt_password` if your broker requires authentication.

### Usage:
1. **Clone or copy the code** into your ESP32 development environment.
2. **Install the required libraries**:
   - [WiFi](https://github.com/espressif/arduino-esp32) for ESP32 Wi-Fi.
   - [PubSubClient](https://github.com/knolleary/pubsubclient) for MQTT communication.
3. **Upload the code** to your ESP32.
4. The program will:
   - Connect to the Wi-Fi network.
   - Subscribe to the `test/topic`. You can also change the topic name as you wish
   - Measure distance using the HC-SR04.
   - Publish the distance data to the `sensor/distance` topic every 2 seconds.

### Pub/Sub Overview
This application utilizes a pub/sub architecture to enable real-time communication between different components. By leveraging pub/sub, we achieve:

* **Scalability:** The system can handle a large number of concurrent users and events.
* **Real-time updates:** Users are immediately notified of new data or changes.
* **Flexibility:** Supports various messaging patterns and use cases.
