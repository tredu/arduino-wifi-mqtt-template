# Arduino UNO R4 WIFI MQTT template 2025
- Connects to WiFi hotspot
- Reads distance (cm) from HC-SR04
- Sends distance as MQTT message

## Connect HC-SR04 Ultrasonic sensor
- Connect sensor Gnd to Arduino ground pin
- Connect sensor Vcc to Arduino 5V
- Connect Trig and Echo to Arduino Digial pins
 - See main.cpp code pin config e.g.
   - const int trigPin = 3;    
   - const int echoPin = 2;

## Configure MQTT settings in main.cpp
- mqttServer e.g. "test.mosquitto.org"
- topic e.g. "test/topic";

## Installation and Compiling
- Copy/paste main.cpp to Arduino IDE
- copy/rename R4WiFi_secrets-example.h to R4WiFi_secrets.h
  - fill correct wifi hotspot details
- Add R4WiFi_secrets.h to Arduino IDE:
  - Sketch -> Add File...
- Add libraries to Arduino IDE:  
  - Tools -> Manage Libraries...
  - ArduinoMqttClient
  - r4httpclient 
- Plug Physical Arduino Device to USB
- Click Upload to send code to device
- Open Serial Monitor with 115200 baund

