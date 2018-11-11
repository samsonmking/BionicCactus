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

void contributeWebComponents();

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
PeriPumpFormTemplate aPumpFormTemplate(aPumpPostRequest.getURI(), pump);
ConfigPageGetRequestHandler getPumpConfig("/config/pump", "Pump Configuration", header, &aPumpFormTemplate);

// Light Initialization
Sensors::Light::LEDLight ledLight(clock, D7);
Sensors::Light::Light *light = &ledLight;
LightFileHandler alightPersistance(light);
FileHandler *lightPersistance = &alightPersistance;
LightPostRequestHandler lightPostHandler("/config/light/submit", light, lightPersistance);
LightFormTemplate lightFormTemplate(lightPostHandler.getURI(), light);
ConfigPageGetRequestHandler getLightConfig("/config/light", "Light Configuration", header, &lightFormTemplate);

// Soil Initialization
#if SIMULATED
  Sensors::Soil::MockSoilSensor dfSoil(90);
#else
  Sensors::Soil::DFSoil dfSoil(A0, arduinoMillis);
#endif
DFSoilFileHandler aSoilPersistance(dfSoil);
FileHandler *soilPersistance = &aSoilPersistance;
DFSoilPostRequestHandler aSoilPostRequest("/config/soil/submit", dfSoil, soilPersistance);
DFSoilFormTemplate aSoilFormTemplate(aSoilPostRequest.getURI(), dfSoil);
ConfigPageGetRequestHandler getSoilConfig("/config/soil", "Soil Configuration", header, &aSoilFormTemplate);
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
EmailFormTemplate anEmailForm(anEmailPostRequest.getURI(), emailSettings.getConfig());
ConfigPageGetRequestHandler getEmailSettings("/config/email", "Email Notification Configuration", header, &anEmailForm);

// Runloop Initialization
SoilRunLoop soilRunLoop(&pump, dfSoil, arduinoMillis);
RunLoopFileHandler aRunLoopPersistance(soilRunLoop);
FileHandler *runLoopPersistance = &aRunLoopPersistance;
RunLoopPostRequestHandler aRunLoopPostRequest("/config/runloop/submit", soilRunLoop, runLoopPersistance);
RunLoopFormTemplate aRunLoopForm(aRunLoopPostRequest.getURI(), soilRunLoop);
ConfigPageGetRequestHandler getRunLoopConfig("/config/runloop", "Run Loop Configuration", header, &aRunLoopForm);

// Wifi Initialization
WifiFileHandler wifiSettings;
FileHandler *wifiPersistance = &wifiSettings;
WifiController wifiController(D3, wifiSettings, arduinoMillis);
WifiPostRequestHandler aWifiPostRequest("/config/wifi/submit", wifiSettings);
WifiFormTemplate aWifiFormTemplate(aWifiPostRequest.getURI(), wifiSettings);
ConfigPageGetRequestHandler getWifiSettings("/config/wifi", "WiFi Configuration", header, &aWifiFormTemplate);

// File Persistance Initialization
FileHandler *handlers[] = {
  lightPersistance, 
  pumpPersistance,
  soilPersistance,
  runLoopPersistance,
  wifiPersistance,
  emailPersistance
};
PersistanceContainer container(handlers, sizeof(handlers) / sizeof(FileHandler *));


// Web Server Initialization
ESP8266WebServer engine(80);

ValuesDashboardTemplate *dashboards[] = {
   &soilDashboard,
   &bottleDashboard
};
 
IndexDashboard indexDashboard(dashboards, sizeof(dashboards) / sizeof(ValuesDashboardTemplate *));

IndexConnectedGetRequestHandler aGetIndexConnected(
  header, 
  getLightConfig.getURI(), 
  getPumpConfig.getURI(), 
  getSoilConfig.getURI(),
  aRunLoopPostRequest.getURI(),
  getEmailSettings.getURI(),
  indexDashboard);

BCWebServer webServer(
  &engine, 
  aGetIndexConnected, 
  aWifiPostRequest,
  getWifiSettings,
  wifiController);

void contributeWebComponents() {
  webServer.contributeGetRequest(getRunLoopConfig);
  webServer.contributePostRequest(aRunLoopPostRequest, getRunLoopConfig.getURI());
  webServer.contributeGetRequest(getSoilConfig);
  webServer.contributePostRequest(aSoilPostRequest, getSoilConfig.getURI());
  webServer.contributeGetRequest(getPumpConfig);
  webServer.contributePostRequest(aPumpPostRequest, getPumpConfig.getURI());
  webServer.contributeGetRequest(getLightConfig);
  webServer.contributePostRequest(lightPostHandler, getLightConfig.getURI());
  webServer.contributeGetRequest(getEmailSettings);
  webServer.contributePostRequest(anEmailPostRequest, getEmailSettings.getURI());
}

void setup() {
  Serial.begin(115200);
  contributeWebComponents();
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
