#ifndef UNIT_TEST

#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <Clock.hpp>
#include <NTP.hpp>
#include <LEDLight.hpp>
#include <PeriPump.hpp>
#include <mock/MockSoilSensor.hpp>
#include <DFSoil.hpp>
#include <SoilRunLoop.hpp>

#include <FS.h>
#include <persistance/FileHandler.hpp>
#include <persistance/LightFileHandler.hpp>
#include <persistance/PeriPumpFileHandler.hpp>
#include <persistance/DFSoilFileHandler.hpp>
#include <persistance/RunLoopFileHandler.hpp>

#include <web/BCWebServer.hpp>
#include <web/GetRequestHandler.hpp>
#include <web/index/IndexConnectedGetRequestHandler.hpp>
#include <web/ConfigPageGetRequestHandler.hpp>
#include <web/SettingsFormTemplate.hpp>
#include <web/light/LightFormTemplate.hpp>
#include <web/PostRequestHandler.hpp>
#include <web/light/LightPostRequestHandler.hpp>
#include <web/pump/PeriPumpFormTemplate.hpp>
#include <web/pump/PeriPumpPostRequestHandler.hpp>
#include <web/soil/DFSoilFormTemplate.hpp>
#include <web/soil/DFSoilPostRequestHandler.hpp>
#include <web/runloop/RunLoopFormTemplate.hpp>
#include <web/runloop/RunLoopPostRequestHandler.hpp>

using namespace Persistance;
using namespace Web;

// Constants
const int PIN_LED = 2;
const int WIFI_TRIGGER_PIN = D3;
enum States { Looping, Priming };

// Global Variables
States state = Looping;
bool initialWifiConfig = false;
uint32 devIdNum = ESP.getChipId();
unsigned long logStart;
unsigned long logTime = 1000;

WiFiClient wifiClient;

NTP* ntp = NTP::getInstance();
Clock clock(ntp, -5);
PeriPump pump(clock, D7, D6, D8);
LEDLight ledLight(clock, D1);
Light *light = &ledLight;
DFSoil dfSoil(A0);
//MockSoilSensor dfSoil(85);
SoilRunLoop soilRunLoop(&pump, &dfSoil, clock);

// File Persistance Initialization
LightFileHandler alightPersistance(light);
FileHandler *lightPersistance = &alightPersistance;
PeriPumpFileHandler aPumpPersistance(pump);
FileHandler *pumpPersistance = &aPumpPersistance;
DFSoilFileHandler aSoilPersistance(dfSoil);
FileHandler *soilPersistance = &aSoilPersistance;
RunLoopFileHandler aRunLoopPersistance(soilRunLoop);
FileHandler *runLoopPersistance = &aRunLoopPersistance;

// Web Server Initialization
ESP8266WebServer engine(80);
Header header;

LightPostRequestHandler lightPostHandler("/config/light/submit", light, lightPersistance);
PostRequestHandler *lightPostRequest = &lightPostHandler;
LightFormTemplate lightFormTemplate(lightPostRequest->getURI(), light);
SettingsFormTemplate *lightForm = &lightFormTemplate;
ConfigPageGetRequestHandler getLightConfig("/config/light", "Light Configuration", header, lightForm);
GetRequestHandler *lightGetRequest = &getLightConfig;

PeriPumpPostRequestHandler aPumpPostRequest("/config/pump/submit", pump, pumpPersistance);
PostRequestHandler *pumpPostRequest = &aPumpPostRequest;
PeriPumpFormTemplate aPumpFormTemplate(pumpPostRequest->getURI(), pump);
SettingsFormTemplate *pumpForm = &aPumpFormTemplate;
ConfigPageGetRequestHandler getPumpConfig("/config/pump", "Pump Configuration", header, pumpForm);
GetRequestHandler *pumpGetRequest = &getPumpConfig;

DFSoilPostRequestHandler aSoilPostRequest("/config/soil/submit", dfSoil, soilPersistance);
PostRequestHandler *soilPostRequest = &aSoilPostRequest;
DFSoilFormTemplate aSoilFormTemplate(soilPostRequest->getURI(), dfSoil);
SettingsFormTemplate *soilForm = &aSoilFormTemplate;
ConfigPageGetRequestHandler getSoilConfig("/config/soil", "Soil Configuration", header, soilForm);
GetRequestHandler *soilGetRequest = &getSoilConfig;

RunLoopPostRequestHandler aRunLoopPostRequest("/config/runloop/submit", soilRunLoop, runLoopPersistance);
PostRequestHandler *runLoopPostRequest = &aRunLoopPostRequest;
RunLoopFormTemplate aRunLoopForm(runLoopPostRequest->getURI(), soilRunLoop);
SettingsFormTemplate *runLoopForm = &aRunLoopForm;
ConfigPageGetRequestHandler getRunLoopConfig("/config/runloop", "Run Loop Configuration", header, runLoopForm);
GetRequestHandler *runLoopGetRequest = &getRunLoopConfig;

IndexConnectedGetRequestHandler aGetIndexConnected(
header, 
lightGetRequest->getURI(), 
pumpGetRequest->getURI(), 
soilGetRequest->getURI(),
runLoopGetRequest->getURI());
GetRequestHandler *getIndexConnected = &aGetIndexConnected;

BCWebServer webServer(
&engine, 
getIndexConnected, 
lightPostRequest, 
lightGetRequest, 
pumpPostRequest, 
pumpGetRequest, 
soilPostRequest, 
soilGetRequest,
runLoopPostRequest,
runLoopGetRequest);

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(WIFI_TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  WiFi.softAP("DevAP", "password");

  webServer.setupServer();

  SPIFFS.begin();
  lightPersistance->load();
  pumpPersistance->load();
  soilPersistance->load();
  runLoopPersistance->load();
}

void loop() {
  // put your main code here, to run repeatedly:
  // switch (state) {
  //   case Looping:
  //     if (digitalRead(WIFI_TRIGGER_PIN) == LOW) {
  //       state = Priming;
  //       return;
  //     }
  //     ledLight.loop();
  //     dfSoil.loop();
  //     pump.loop();
  //     soilRunLoop.loop();
  //     connectWifiIfConfigured();      
  //     break;
  //   case Priming:
  //     pump.prime();
  //     if (digitalRead(WIFI_TRIGGER_PIN) == HIGH) {
  //       pump.stop();
  //       state = Looping;
  //     }
  //     break;
  // }
  webServer.loop();
}



#endif
