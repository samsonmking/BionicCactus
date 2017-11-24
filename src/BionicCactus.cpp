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
#include <ArduinoJson.h>

// Constants
const int PIN_LED = 2;
const int WIFI_TRIGGER_PIN = D3;
const char* mqtt_server = "192.168.1.100";
enum States { Looping, Priming };

// Global Variables
States state = Looping;
bool initialWifiConfig = false;
uint32 devIdNum = ESP.getChipId();
char devId[25];
char humTopic[50];
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
  snprintf(devId, 24, "%u", devIdNum);
  snprintf(humTopic, 49, "/%u/DFSoil", devIdNum);
  pinMode(PIN_LED, OUTPUT);
  pinMode(WIFI_TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  connectWifiIfConfigured();
  mqtt.setServer(mqtt_server, 1883);
  mqtt.setCallback(onSubscribed);
  ledLight.setTimeOn("9:00:00");
  ledLight.setTimeOff("17:00:00");
  Serial.println(devId);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
    case Looping:
      if (digitalRead(WIFI_TRIGGER_PIN) == LOW) {
        state = Priming;
        return;
      }
      connectWifiIfConfigured();
      ledLight.loop();
      dfSoil.loop();
      soilRunLoop.loop();
      connectMqtt();
      logVals();
      mqtt.loop();      
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
  StaticJsonBuffer<200> humBuffer;
  JsonObject& humRoot = humBuffer.createObject();
  humRoot["deviceID"] = devIdNum;
  humRoot["value"] = dfSoil.readPercent();
  humRoot["time"] = clock.getCurrentTime();
  char payload[500];
  humRoot.printTo(payload, 500);
  mqtt.publish(humTopic, payload);
  logStart = now;
}

void connectMqtt() {
  while(!mqtt.connected()) {
    Serial.println("connecting mqtt");
    if (!mqtt.connect(devId)) {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void onSubscribed(char* topic, byte* payload, unsigned int length) {

}

void connectWifiIfConfigured() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
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
