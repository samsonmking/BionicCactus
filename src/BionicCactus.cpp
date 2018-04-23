#ifndef UNIT_TEST

#include <Arduino.h>

#include "time/Clock.hpp"
#include "time/NTP.hpp"

#include "sensors/light/LEDLight.hpp"
#include "sensors/pump/PeriPump.hpp"
#include "sensors/soil/DFSoil.hpp"
#include <SoilRunLoop.hpp>

#include "persistance/PersistanceContainer.hpp"
#include "persistance/FileHandler.hpp"
#include "persistance/LightFileHandler.hpp"
#include "persistance/PeriPumpFileHandler.hpp"
#include "persistance/DFSoilFileHandler.hpp"
#include "persistance/RunLoopFileHandler.hpp"
#include "persistance/WifiFileHandler.hpp"

#include "wifi/WifiController.hpp"

#include "web/BCWebServer.hpp"
#include "web/GetRequestHandler.hpp"
#include "web/index/IndexConnectedGetRequestHandler.hpp"
#include "web/ConfigPageGetRequestHandler.hpp"
#include "web/SettingsFormTemplate.hpp"
#include "web/light/LightFormTemplate.hpp"
#include "web/PostRequestHandler.hpp"
#include "web/light/LightPostRequestHandler.hpp"
#include "web/pump/PeriPumpFormTemplate.hpp"
#include "web/pump/PeriPumpPostRequestHandler.hpp"
#include "web/soil/DFSoilFormTemplate.hpp"
#include "web/soil/DFSoilPostRequestHandler.hpp"
#include "web/runloop/RunLoopFormTemplate.hpp"
#include "web/runloop/RunLoopPostRequestHandler.hpp"
#include "web/wifi/WifiFormTemplate.hpp"
#include "web/wifi/WifiPostRequestHandler.hpp"

using namespace Time;
using namespace Sensors::Light;
using namespace Sensors::Pump;
using namespace Sensors::Soil;
using namespace Persistance;
using namespace Wireless;
using namespace Web;

// Constants
const int PIN_LED = 2;
const int WIFI_TRIGGER_PIN = D3;
enum States { Looping, Priming };

// Global Variables
States state = Looping;

// Time Initialization
NTP* ntp = NTP::getInstance();
Clock clock(ntp, -5);

// Sensors Initialization
PeriPump pump(clock, D7, D6, D8);
LEDLight ledLight(clock, D1);
Light *light = &ledLight;
DFSoil dfSoil(A0);

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
WifiFileHandler wifiSettings;
FileHandler *wifiPersistance = &wifiSettings;

const int numHandlers = 5;
FileHandler *handlers[numHandlers] = {
  lightPersistance, 
  pumpPersistance,
  soilPersistance,
  runLoopPersistance,
  wifiPersistance};
PersistanceContainer container(handlers, numHandlers);

// Wifi Initialization
WifiController wifiController(wifiSettings, clock);

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

WifiPostRequestHandler aWifiPostRequest("/config/wifi/submit", wifiSettings);
PostRequestHandler *wifiPostRequest = &aWifiPostRequest;
WifiFormTemplate aWifiFormTemplate(wifiPostRequest->getURI(), wifiSettings);
SettingsFormTemplate *wifiForm = &aWifiFormTemplate;
ConfigPageGetRequestHandler getWifiSettings("/config/wifi", "WiFi Configuration", header, wifiForm);
GetRequestHandler *wifiGetRequest = &getWifiSettings;

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
runLoopGetRequest,
wifiPostRequest,
wifiGetRequest,
wifiSettings);

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(WIFI_TRIGGER_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  webServer.setupServer();
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
  wifiController.loop();
  webServer.loop();
}

#endif
