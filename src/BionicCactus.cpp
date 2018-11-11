#ifndef UNIT_TEST

#define SIMULATED false

#include <Arduino.h>

#include "time/Clock.hpp"
#include "time/MockTimeProvider.hpp"
#include <WiFiUdp.h>
#include "time/NTPTimeProvider.hpp"
#include "time/ArduinoMillisProvider.hpp"

#include "sensors/light/LEDLight.hpp"
#include "sensors/pump/PeriPump.hpp"
#include "sensors/soil/DFSoil.hpp"
#include "sensors/soil/MockSoilSensor.hpp"
#include "sensors/scale_bottle/ScaleBottle.hpp"
#include "sensors/scale_bottle/MockBottle.hpp"
#include "SoilRunLoop.hpp"

#include "persistance/PersistanceContainer.hpp"
#include "persistance/FileHandler.hpp"
#include "persistance/LightFileHandler.hpp"
#include "persistance/PeriPumpFileHandler.hpp"
#include "persistance/DFSoilFileHandler.hpp"
#include "persistance/RunLoopFileHandler.hpp"
#include "persistance/WifiFileHandler.hpp"
#include "persistance/EmailFileHandler.hpp"

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
#include "web/email/EmailFormTemplate.hpp"
#include "web/email/EmailPostRequestHandler.hpp"
#include "web/bottle/BottleDashboardTemplate.hpp"

#include "email/EmailClient.hpp"
#include "email/BottleEmailNotifier.hpp"

using namespace Time;
using namespace Sensors::Light;
using namespace Sensors::Pump;
using namespace Sensors::Soil;
using namespace Persistance;
using namespace Wireless;
using namespace Web;
using namespace Email;

// Time Initialization
WiFiUDP ntpUDP;
NTPTimeProvider ntpTime(ntpUDP);
Clock clock(ntpTime, -4);
ArduinoMillisProvider arduinoMillis;

// Web Dependencies
Header header;

// Pump Initialization
Sensors::Pump::PeriPump pump(arduinoMillis, D5, D0, D6, D8);
PeriPumpFileHandler aPumpPersistance(pump);
FileHandler *pumpPersistance = &aPumpPersistance;
PeriPumpPostRequestHandler aPumpPostRequest("/config/pump/submit", pump, pumpPersistance);
PostRequestHandler *pumpPostRequest = &aPumpPostRequest;
PeriPumpFormTemplate aPumpFormTemplate(pumpPostRequest->getURI(), pump);
SettingsFormTemplate *pumpForm = &aPumpFormTemplate;
ConfigPageGetRequestHandler getPumpConfig("/config/pump", "Pump Configuration", header, pumpForm);
GetRequestHandler *pumpGetRequest = &getPumpConfig;

// Light Initialization
Sensors::Light::LEDLight ledLight(clock, D7);
Sensors::Light::Light *light = &ledLight;
LightFileHandler alightPersistance(light);
FileHandler *lightPersistance = &alightPersistance;
LightPostRequestHandler lightPostHandler("/config/light/submit", light, lightPersistance);
PostRequestHandler *lightPostRequest = &lightPostHandler;
LightFormTemplate lightFormTemplate(lightPostRequest->getURI(), light);
SettingsFormTemplate *lightForm = &lightFormTemplate;
ConfigPageGetRequestHandler getLightConfig("/config/light", "Light Configuration", header, lightForm);
GetRequestHandler *lightGetRequest = &getLightConfig;

// Soil Initialization
#if SIMULATED
  Sensors::Soil::MockSoilSensor dfSoil(90);
#else
  Sensors::Soil::DFSoil dfSoil(A0, arduinoMillis);
#endif
DFSoilFileHandler aSoilPersistance(dfSoil);
FileHandler *soilPersistance = &aSoilPersistance;
DFSoilPostRequestHandler aSoilPostRequest("/config/soil/submit", dfSoil, soilPersistance);
PostRequestHandler *soilPostRequest = &aSoilPostRequest;
DFSoilFormTemplate aSoilFormTemplate(soilPostRequest->getURI(), dfSoil);
SettingsFormTemplate *soilForm = &aSoilFormTemplate;
ConfigPageGetRequestHandler getSoilConfig("/config/soil", "Soil Configuration", header, soilForm);
GetRequestHandler *soilGetRequest = &getSoilConfig;
SoilDashboardTemplate soilDashboard(dfSoil);
  
// Bottle Initialization
#if SIMULATED
  Sensors::Bottle::MockBottle bottle;
#else
  Sensors::Bottle::ScaleBottle bottle(D2, D1);
#endif
BottleDashboardTemplate bottleDashboard(bottle);
EmailFileHandler emailSettings;
FileHandler *emailPersistance = &emailSettings;
BottleEmailNotifier bottleEmail(arduinoMillis, bottle, emailSettings.getConfig());
EmailPostRequestHandler anEmailPostRequest("/config/email/submit", emailSettings);
PostRequestHandler* emailPostRequest = &anEmailPostRequest;
EmailFormTemplate anEmailForm(emailPostRequest->getURI(), emailSettings.getConfig());
SettingsFormTemplate* emailForm = &anEmailForm;
ConfigPageGetRequestHandler getEmailSettings("/config/email", "Email Notification Configuration", header, emailForm);
GetRequestHandler *emailGetRequest = &getEmailSettings;

// Runloop Initialization
SoilRunLoop soilRunLoop(&pump, dfSoil, arduinoMillis);
RunLoopFileHandler aRunLoopPersistance(soilRunLoop);
FileHandler *runLoopPersistance = &aRunLoopPersistance;
RunLoopPostRequestHandler aRunLoopPostRequest("/config/runloop/submit", soilRunLoop, runLoopPersistance);
PostRequestHandler *runLoopPostRequest = &aRunLoopPostRequest;
RunLoopFormTemplate aRunLoopForm(runLoopPostRequest->getURI(), soilRunLoop);
SettingsFormTemplate *runLoopForm = &aRunLoopForm;
ConfigPageGetRequestHandler getRunLoopConfig("/config/runloop", "Run Loop Configuration", header, runLoopForm);
GetRequestHandler *runLoopGetRequest = &getRunLoopConfig;

// Wifi Initialization
WifiFileHandler wifiSettings;
FileHandler *wifiPersistance = &wifiSettings;
WifiController wifiController(wifiSettings, arduinoMillis);
WifiPostRequestHandler aWifiPostRequest("/config/wifi/submit", wifiSettings);
PostRequestHandler *wifiPostRequest = &aWifiPostRequest;
WifiFormTemplate aWifiFormTemplate(wifiPostRequest->getURI(), wifiSettings);
SettingsFormTemplate *wifiForm = &aWifiFormTemplate;
ConfigPageGetRequestHandler getWifiSettings("/config/wifi", "WiFi Configuration", header, wifiForm);
GetRequestHandler *wifiGetRequest = &getWifiSettings;

// File Persistance Initialization
const int numHandlers = 6;
FileHandler *handlers[numHandlers] = {
  lightPersistance, 
  pumpPersistance,
  soilPersistance,
  runLoopPersistance,
  wifiPersistance,
  emailPersistance
};
PersistanceContainer container(handlers, numHandlers);


// Web Server Initialization
ESP8266WebServer engine(80);

static const int numDashboards = 2;
ValuesDashboardTemplate *dashboards[numDashboards] = {
   &soilDashboard,
   &bottleDashboard
};
 
IndexDashboard indexDashboard(dashboards, numDashboards);

IndexConnectedGetRequestHandler aGetIndexConnected(
  header, 
  lightGetRequest->getURI(), 
  pumpGetRequest->getURI(), 
  soilGetRequest->getURI(),
  runLoopGetRequest->getURI(),
  emailGetRequest->getURI(),
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
  wifiSettings,
  emailPostRequest,
  emailGetRequest);

void setup() {
  Serial.begin(115200);
  webServer.setupServer();
}

void loop() {
  wifiController.loop();
  if (wifiController.isConnected() || wifiController.isAccessPoint()) {
    webServer.loop();
  }

  if (wifiController.isConnected()) {
    ntpTime.update();
    bottleEmail.loop();
  }

  ledLight.loop();
  pump.loop();
  dfSoil.loop();
  soilRunLoop.loop();
}

#endif
