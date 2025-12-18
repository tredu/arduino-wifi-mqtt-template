#include "R4WiFi_secrets.h"
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

const int trigPin = 3;    
const int echoPin = 2;
const int SOUND_SPEED_MS = 343; 

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long dur = pulseIn(echoPin, HIGH);
  return dur * SOUND_SPEED_MS/10000/ 2;
}

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttServer = "test.mosquitto.org"; // MQTT broker address
const int mqttPort = 1883; // Default MQTT port
const char* topic = "testiaa/aihebb";
const long interval = 8000;
unsigned long previousMillis = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
  while (!Serial);

  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Connect to MQTT broker
  Serial.print("Connecting to MQTT broker...");
  if (!mqttClient.connect(mqttServer, mqttPort)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1); // Stop execution if connection fails
  }
  Serial.println("Connected to MQTT broker!");
}

void loop() {
  int distance = getDistance();

  mqttClient.poll(); // Keep the connection alive

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Construct the JSON message
    String message = "{\"distance\":" + String(distance) + ",\"mac\":\"GG:HH:II:JJ:KK:LL\"}";

    // Publish the message to the topic
    mqttClient.beginMessage(topic);
    mqttClient.print(message);
    mqttClient.endMessage();

    Serial.println("Message published successfully: " + message);
  }
}