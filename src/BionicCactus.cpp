#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//Needed for WifiManager
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/kentaylor/WiFiManager
#include <PubSubClient.h>
#include <Soil.h>

// Constants
const int PIN_LED = 2;
const int WIFI_TRIGGER_PIN = 0;
const char* mqtt_server = "192.168.0.102";

// Global Variables
bool initialWifiConfig = false;
int chipId = ESP.getChipId();
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
Soil soil(chipId, 2000, A0, D0, mqtt);

// Function Prototypes
void connectWifiIfConfigured();
void configureWifi();
void onSubscribed(char* topic, byte* payload, unsigned int length);
void reconnect();

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(WIFI_TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  connectWifiIfConfigured();
  Serial.println();
  mqtt.setServer(mqtt_server, 1883);
  mqtt.setCallback(onSubscribed);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((digitalRead(WIFI_TRIGGER_PIN) == LOW) || (initialWifiConfig)) {
    configureWifi();
  }
  if (!mqtt.connected()) {
    reconnect();
  }
  mqtt.loop();
  soil.loop();
}

void reconnect() {
  while(!mqtt.connected()) {
    Serial.println("connecting mqtt");
    char idChr[9];

    if (mqtt.connect(idChr)) {
      Serial.println("connected");
    }
  }
}

void onSubscribed(char* topic, byte* payload, unsigned int length) {

}

void connectWifiIfConfigured() {
  if (WiFi.SSID() == "")
  {
    initialWifiConfig = true;
    return;
  }
  WiFi.mode(WIFI_STA);
  WiFi.waitForConnectResult();
  if (WiFi.status()!=WL_CONNECTED){
    Serial.println("failed to connect, finishing setup anyway");
  } else{
    digitalWrite(PIN_LED, HIGH);
    Serial.print("local ip: ");
    Serial.println(WiFi.localIP());
  }
}

void configureWifi() {
  digitalWrite(PIN_LED, LOW);
  WiFiManager wifiManager;
  wifiManager.startConfigPortal("BionicCactus");
  digitalWrite(PIN_LED, HIGH);
  ESP.reset();
  delay(5000);
}
