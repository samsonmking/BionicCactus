#ifndef UNIT_TEST

#include <Arduino.h>

#include "time/Clock.hpp"
#include "time/MockTimeProvider.hpp"
#include <WiFiUdp.h>
#include "time/NTPTimeProvider.hpp"

#include "sensors/light/LEDLight.hpp"
#include "sensors/pump/PeriPump.hpp"
#include "sensors/soil/DFSoil.hpp"
#include "SoilRunLoop.hpp"

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
#include "web/soil/SoilDashboardTemplate.hpp"
#include "web/runloop/RunLoopFormTemplate.hpp"
#include "web/runloop/RunLoopPostRequestHandler.hpp"
#include "web/wifi/WifiFormTemplate.hpp"
#include "web/wifi/WifiPostRequestHandler.hpp"
#include "web/index/IndexDashboard.hpp"

using namespace Time;
using namespace Sensors::Light;
using namespace Sensors::Pump;
using namespace Sensors::Soil;
using namespace Persistance;
using namespace Wireless;
using namespace Web;

// Time Initialization
WiFiUDP ntpUDP;
NTPTimeProvider ntpTime(ntpUDP);
// MockTime mockTime(1000);
Clock clock(ntpTime, -4);

// Sensors Initialization
Sensors::Pump::PeriPump pump(clock, D7, D6, D8);
Sensors::Light::LEDLight ledLight(clock, D0);
Sensors::Light::Light *light = &ledLight;
Sensors::Soil::DFSoil dfSoil(A0, clock);

SoilRunLoop soilRunLoop(&pump, dfSoil, clock);

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

SoilDashboardTemplate soilDashboard(dfSoil);

static const int numDashboards = 1;
ValuesDashboardTemplate *dashboards[numDashboards] = {
  &soilDashboard
};

IndexDashboard indexDashboard(dashboards, numDashboards);

IndexConnectedGetRequestHandler aGetIndexConnected(
header, 
lightGetRequest->getURI(), 
pumpGetRequest->getURI(), 
soilGetRequest->getURI(),
runLoopGetRequest->getURI(),
indexDashboard);
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
  Serial.begin(115200);
  webServer.setupServer();
}

void loop() {
  wifiController.loop();

  if (wifiController.isConnected()) {
    ntpTime.update();
    webServer.loop();
  }

  ledLight.loop();
  pump.loop();
  dfSoil.loop();
  soilRunLoop.loop();
  
}

#endif
