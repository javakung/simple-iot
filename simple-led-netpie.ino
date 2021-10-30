#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int led = 13;

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "";
const char* mqtt_username = "";
const char* mqtt_password = "";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      client.subscribe("@msg/homecontrol");
    }
    else {
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  if (message == "open") {
    digitalWrite(led, HIGH);
    delay(2000);
    digitalWrite(led, LOW);
  }

}


void setup() {
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
