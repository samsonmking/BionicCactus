#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//Needed for WifiManager
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/kentaylor/WiFiManager

// Constants
const int PIN_LED = 2;
const int WIFI_TRIGGER_PIN = 0;

// Global Variables
bool initialWifiConfig = false;

// Function Prototypes
void connectWifiIfConfigured();
void configureWifi();

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(WIFI_TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  connectWifiIfConfigured();
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((digitalRead(WIFI_TRIGGER_PIN) == LOW) || (initialWifiConfig)) {
    configureWifi();
  }
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
  wifiManager.startConfigPortal();
  digitalWrite(PIN_LED, HIGH);
  ESP.reset();
  delay(5000);
}

