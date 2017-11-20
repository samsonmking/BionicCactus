#ifndef UNIT_TEST

#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//Needed for WifiManager
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/kentaylor/WiFiManager
#include <PubSubClient.h>
#include <Clock.hpp>
#include <NTP.hpp>
#include <LEDLight.hpp>
#include <PeriPump.hpp>
#include <mock/MockSoilSensor.hpp>
#include <DFSoil.hpp>
#include <SoilRunLoop.hpp>

// Constants
const int PIN_LED = 2;
const int WIFI_TRIGGER_PIN = D3;
const char* mqtt_server = "192.168.1.100";
enum States { Looping, Priming };

// Global Variables
States state = Looping;
bool initialWifiConfig = false;
int chipId = ESP.getChipId();
unsigned long logStart;
unsigned long logTime = 1000;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

NTP* ntp = NTP::getInstance();
Clock clock(ntp, -5);
PeriPump pump(clock, D7, D6, D8);
LEDLight ledLight(clock, D1);
DFSoil dfSoil(A0);
//MockSoilSensor dfSoil(85);
SoilRunLoop soilRunLoop(&pump, &dfSoil, clock);

// Function Prototypes
void connectWifiIfConfigured();
void configureWifi();
void onSubscribed(char* topic, byte* payload, unsigned int length);
void connectMqtt();
void logVals();

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(WIFI_TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  connectWifiIfConfigured();
  mqtt.setServer(mqtt_server, 1883);
  mqtt.setCallback(onSubscribed);
  ledLight.setTimeOn("9:00:00");
  ledLight.setTimeOff("17:00:00");

}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
    case Looping:
      if (digitalRead(WIFI_TRIGGER_PIN) == LOW) {
        state = Priming;
        return;
      }
      if (WiFi.status()!=WL_CONNECTED) {
        connectWifiIfConfigured();
      }
      connectMqtt();
      ledLight.loop();
      dfSoil.loop();
      soilRunLoop.loop();
      logVals();
      break;
    case Priming:
      pump.prime();
      if (digitalRead(WIFI_TRIGGER_PIN) == HIGH) {
        pump.stop();
        state = Looping;
      }
      break;
  }
}

void logVals() {
  unsigned long now = clock.getMillis();
  if ((now - logStart) < logTime) {
    return;
  }
  float hum = dfSoil.readPercent();
  char humStr[5];
  dtostrf(hum,3,0, humStr);
  mqtt.publish("Soil", humStr);
  Serial.println(humStr);
  logStart = now;
}

void connectMqtt() {
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

#endif
